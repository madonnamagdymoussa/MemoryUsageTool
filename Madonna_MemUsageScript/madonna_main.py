import json
import re
import csv
import subprocess


# Load configuration from JSON file
def load_config(file_path):
    with open(file_path, 'r') as file:
        return json.load(file)


# Load the configuration
config = load_config('config.json')

# Extract configurations from the loaded JSON
sections_list = config['sections']  # Ensure this key exists in your JSON
file_paths_Dict = config['file_paths']  # Update to the new key name if changed
NM_flags_Dict = config['NM_flags']  # Updated key name for NM flags
csv_files_Dict = config['csv_file_paths']  # Changed to reflect the updated key name
memory_sizes_Dict = config['memory_configuration']  # Changed to reflect the updated key name
Regex_templates_Dict = config['regex_templates']  # Load regex templates
# Extract the NM command template
commands_Dict = config['commands']  # Load all commands from JSON
nm_command_template = commands_Dict['nm_command']  # NM command template


# Function to dynamically create regex patterns based on the sections and templates
def create_regex_patterns(sections, templates):
    suffix_pattern = r'\S+'  # Matches any non-whitespace characters
    section_pattern = r'\.(' + '|'.join(sections) + r')\.(' + suffix_pattern + r')'
    return {key: template.format(section_pattern=section_pattern) for key, template in templates.items()}


# Compile patterns for use in the project
def compile_patterns(regex_dict):
    return {key: re.compile(pattern) for key, pattern in regex_dict.items()}


# Create regex patterns based on the section list and pattern templates
Regex_patterns_Dict = create_regex_patterns(sections_list, Regex_templates_Dict)

# Example usage
Compiled_Regex_Patterns_Dict = compile_patterns(Regex_patterns_Dict)


def format_size(hex_size):
    size_decimal = int(hex_size, 16)
    return f"{size_decimal} (0x{hex_size})"


#r'\.(text|data|bss|rodata)\.(\S+)\s+0x[0-9a-f]+\s+0x([0-9a-f]+)\s+(.*)'
# Handle a full entry line using a dictionary
def process_entry_data(line, compiled_regex_patterns, entries):
    record = compiled_regex_patterns['entry_regex'].search(line)
    if record:
        symbol_info = {
            'Section': f".{record.group(1)}",
            'SymbolName': record.group(2),
            'Size': format_size(record.group(3)),
            'MemLocation': record.group(4).strip()
        }
        entries.append(symbol_info)  # Append the dictionary to the entries list
        return True
    return False


def process_multi_line_and_continued(line, compiled_regex_patterns, current_info, entries):
    """Process multi-line names and continued lines from the map file."""

    # Check for multi-line names
    multi_line_match = compiled_regex_patterns['multi_line_name_regex'].search(line)
    if multi_line_match:
        # Extract section and symbol name
        current_info['Section'] = f".{multi_line_match.group(1)}"
        current_info['SymbolName'] = multi_line_match.group(2)
        current_info['multi_line_entry'] = True  # Mark that we're in a multi-line entry
        return True  # Exit the function after processing multi-line name

    # Check for continued line if a multi-line entry is ongoing
    if current_info.get('multi_line_entry'):
        continued_line_match = compiled_regex_patterns['continued_line_regex'].search(line)
        if continued_line_match and current_info.get('SymbolName'):
            # Extract size and location
            size = continued_line_match.group(1)
            location = continued_line_match.group(2).strip()

            # Create a dictionary for the entry
            symbol_info = {
                'Section': current_info['Section'],
                'SymbolName': current_info['SymbolName'],
                'Size': format_size(size),
                'MemLocation': location
            }
            entries.append(symbol_info)  # Append to the entries list

            # Clear current info for the next entry
            current_info.clear()
            return True  # Exit after processing the continued line

    return False  # If no conditions matched, return False

# Function to write entries to a CSV file
def write_entries_to_csv(entries, csv_file_path):
    """Write the parsed entries to a CSV file."""
    with open(csv_file_path, 'w', newline='') as f:
        writer = csv.writer(f)
        writer.writerow(['Name', 'Type', 'Size', 'Location'])  # Headers
        for entry in entries:
            writer.writerow([entry['SymbolName'], entry['Section'], entry['Size'], entry['MemLocation']])

    print(f"Mapfile parsed successfully and saved to {csv_file_path}")



# New function to parse the map file
def parse_map_file(map_file_path, compiled_regex_patterns):
    """Parse the map file using the provided regex patterns and return the parsed entries."""
    entries = []  # Store the entries here
    current_info = {'multi_line_entry': False}  # To store ongoing multi-line entries

    with open(map_file_path, 'r') as f:
        for line in f:
            if process_entry_data(line, compiled_regex_patterns, entries):
                continue
            if process_multi_line_and_continued(line, compiled_regex_patterns, current_info, entries):
                continue

    return entries


def run_nm_command(specific_flag_key=None):
    # Build the NM command dynamically using the template from the config
    nm_command_template = config['commands']['nm_command']

    # If a specific flag key is provided, handle multiple flags
    if specific_flag_key:
        # Split the input string by comma and remove any leading/trailing spaces
        flag_keys = [key.strip() for key in specific_flag_key.split(',')]

        # Fetch the corresponding flags from NM_flags_Dict and join them with a space
        nm_flags = " ".join(NM_flags_Dict.get(key, '') for key in flag_keys if key in NM_flags_Dict)
    else:
        # Default to all flags if no specific flag is provided
        nm_flags = " ".join(NM_flags_Dict.values())

    # Format the command by replacing placeholders with values from the dictionaries
    nm_command = nm_command_template.format(
        nm_path=file_paths_Dict['nm_path'],  # Path to the 'nm' tool
        nm_flags=nm_flags,  # Use specific flags or all flags
        elf_file_path=file_paths_Dict['elf_path'],  # Path to the ELF file
        nm_objects_txt=file_paths_Dict['nm_objects_txt']  # Output file for nm command
    )

    # Now execute the constructed nm command using subprocess
    try:
        result = subprocess.run(nm_command, shell=True, check=True, capture_output=True, text=True)
        print("NM command ran successfully!")
    except subprocess.CalledProcessError as e:
        print(f"Command failed with return code {e.returncode}")
        print(f"Error output: {e.stderr}")

# Get the map file path and output CSV file path from the JSON config
map_file_path = file_paths_Dict['map_path']
parsed_mapfile_csv = csv_files_Dict['map_file_parsing_csv']

# Parse the map file
entries = parse_map_file(map_file_path, Compiled_Regex_Patterns_Dict)

# Write the parsed entries to a CSV file
write_entries_to_csv(entries, parsed_mapfile_csv)

#run_nm_command(specific_flag_key='defined_only, print_size')
#print(entries)