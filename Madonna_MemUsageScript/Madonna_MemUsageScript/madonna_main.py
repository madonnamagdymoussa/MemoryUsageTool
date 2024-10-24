import json
import re
import csv
import subprocess
import os

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
nm_command_template = commands_Dict['nm_command_out']  # NM command template


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


def get_binary_file_extension():
    binary_file_path = file_paths_Dict['binary_file_path']
    file_ext = os.path.splitext(binary_file_path)[-1].lower()
    '''
    os.path.splitext(path)
    Split the pathname path into a pair (root, ext) such that root + ext == path, 
    and the extension, ext, is empty or begins with a period and contains at most one period.
    
    splitext('foo.bar.exe')
    ('foo.bar', '.exe')
    splitext('/foo/bar.exe')
    ('/foo/bar', '.exe')
     '''
    # Retrieve supported extensions from the configuration
    supported_extensions = config['supported_extensions']

    if file_ext in supported_extensions:
        return binary_file_path
    else:
        raise ValueError(f"Unsupported binary file type. Please provide one of {supported_extensions}.")


def run_nm_command(specific_flag_key=None):
    # Retrieve the binary file path and supported extensions from the configuration
    binary_file_path = file_paths_Dict['binary_file_path']  # Use 'binary_file_path' instead of 'elf_path'
    supported_extensions = config.get('supported_extensions', ['.elf', '.out'])  # This is a list

    # Get the actual file extension from the binary file path
    file_extension = os.path.splitext(binary_file_path)[-1].lower()

    # Check if the file's extension is in the supported extensions list
    if file_extension not in supported_extensions:
        raise ValueError(f"Unsupported binary file extension {file_extension}. Supported types: {supported_extensions}")

    # Select the appropriate command template based on the file extension
    if file_extension == '.elf':
        nm_command_template = config['commands']['nm_command_elf']
        file_path_key = 'elf_file_path'
    elif file_extension == '.out':
        nm_command_template = config['commands']['nm_command_out']
        file_path_key = 'out_file_path'
    else:
        raise ValueError(f"Unsupported binary file extension {file_extension}. Please provide a valid binary file.")

    # If a specific flag key is provided, handle multiple flags
    if specific_flag_key:
        flag_keys = [key.strip() for key in specific_flag_key.split(',')]
        nm_flags = " ".join(NM_flags_Dict.get(key, '') for key in flag_keys if key in NM_flags_Dict)
    else:
        nm_flags = " ".join(NM_flags_Dict.values())

    # Format the command by replacing placeholders with values from the dictionaries
    nm_command = nm_command_template.format(
        nm_path=file_paths_Dict['nm_path'],
        nm_flags=nm_flags,
        **{file_path_key: binary_file_path},  # Use either 'elf_file_path' or 'out_file_path'
        nm_objects_txt=csv_files_Dict['nm_objects_file']
    )

    # Execute the constructed nm command using subprocess
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

run_nm_command(specific_flag_key='defined_only, print_size')
#print(entries)