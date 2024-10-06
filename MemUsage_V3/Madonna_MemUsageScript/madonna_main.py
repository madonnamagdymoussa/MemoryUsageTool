import json
import re
import csv
import subprocess
import os

'''
# Load configuration from JSON file
def load_config(file_path):
    with open(file_path, 'r') as file:
        return json.load(file)
'''


def load_config(file_path):
    """Load configuration from a JSON file."""
    if not os.path.exists(file_path):
        raise FileNotFoundError(f"Configuration file not found: {file_path}")

    with open(file_path, 'r') as file:
        return json.load(file)


# Load the configuration
config = load_config('config.json')

# Extract configurations from the loaded JSON
sections_list = config['sections']  # Ensure this key exists in your JSON
file_paths_Dict = config['file_paths']  # Update to the new key name if changed
NM_flags_Dict = config['NM_flags']  # Updated key name for NM flags
ObjDump_flags_Dict = config['ObjDump_flags']
csv_files_Dict = config['csv_file_paths']  # Changed to reflect the updated key name
memory_sizes_Dict = config['memory_configuration']  # Changed to reflect the updated key name
Regex_templates_Dict = config['regex_templates']  # Load regex templates
# Extract the NM command template
commands_Dict = config['commands']  # Load all commands from JSON
nm_command_template = commands_Dict['nm_command_out']  # NM command template


#sections_list = config.get('sections', {})  # Default to an empty dict if 'sections' is not found


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
    binary_file_path = file_paths_Dict['binary_file_path']
    supported_extensions = config.get('supported_extensions', ['.elf', '.out'])

    file_extension = os.path.splitext(binary_file_path)[-1].lower()

    if file_extension not in supported_extensions:
        raise ValueError(f"Unsupported binary file extension {file_extension}. Supported types: {supported_extensions}")

    if file_extension == '.elf':
        nm_command_template = config['commands']['nm_command_elf']
        file_path_key = 'elf_file_path'
    elif file_extension == '.out':
        nm_command_template = config['commands']['nm_command_out']
        file_path_key = 'out_file_path'
    else:
        raise ValueError(f"Unsupported binary file extension {file_extension}. Please provide a valid binary file.")

    if specific_flag_key:
        flag_keys = [key.strip() for key in specific_flag_key.split(',')]
        nm_flags = " ".join(NM_flags_Dict.get(key, '') for key in flag_keys if key in NM_flags_Dict)
    else:
        nm_flags = " ".join(NM_flags_Dict.values())

    nm_command = nm_command_template.format(
        nm_path=file_paths_Dict['nm_path'],
        nm_flags=nm_flags,
        **{file_path_key: binary_file_path},
        nm_objects_txt=csv_files_Dict['nm_objects_file']
    )

    print("Constructed NM Command:", nm_command)  # Debug: Show the command being run

    try:
        result = subprocess.run(nm_command, shell=True, check=True, capture_output=True, text=True)
        print("NM command ran successfully!")
        print("Raw output:", result.stdout)  # Debug: Print raw output
        return result.stdout.strip()
    except subprocess.CalledProcessError as e:
        print(f"Command failed with return code {e.returncode}")
        print(f"Error output: {e.stderr}")
        return None


def parse_nm_output(nm_objects_txt, elf_objects_csv):
    # Debug print to check the file paths
    print(f"Reading from: {nm_objects_txt}")
    print(f"Writing to: {elf_objects_csv}")

    try:

        with open(nm_objects_txt, 'r') as infile, open(elf_objects_csv, 'w', newline='') as csvfile:
            csv_writer = csv.writer(csvfile)
            csv_writer.writerow(['Physical_Address', 'Size', 'Type', 'Object_Name'])  # Write header
            for line in infile:
                # Assuming nm output format is: <address> <size> <symbol> <object file>
                # Example: 0x08000000 0x00000400 my_function.o
                parts = line.split()

                if len(parts) < 4:
                    continue  # Skip lines that don't have enough parts

                physical_address = parts[0]  # Address
                size = parts[1]  # Size
                object_name = parts[2]  # Symbol
                object_file = parts[3]  # Object File

                # Write to CSV
                #csv_writer.writerow([physical_address, size, 'N/A', object_name])  # Placeholder for Type as 'N/A'
                csv_writer.writerow([physical_address, size, object_name, object_file])  # Placeholder for Type as 'N/A'
                print(physical_address, size, object_name, object_file)
            print("NM output processed and saved to CSV successfully.")

    except PermissionError as e:
        print(f"Permission error: {e}")
    except FileNotFoundError as e:
        print(f"File not found: {e}")
    except Exception as e:
        print(f"An error occurred: {e}")


def load_csv_data(file_location, required_headers):
    """Loads a CSV file and returns a list of dictionaries if headers match the requirements."""
    try:
        with open(file_location, 'r') as file:
            csv_reader = csv.DictReader(file)
            available_headers = csv_reader.fieldnames

            # Check for any missing required headers
            missing_required = [header for header in required_headers if header not in available_headers]
            if missing_required:
                raise KeyError(f"Missing headers: {', '.join(missing_required)}")

            # Return the data as a list of dictionaries
            return list(csv_reader)

    except FileNotFoundError:
        print(f"Error: File '{file_location}' not found.")
        return []

    except KeyError as e:
        print(f"Error: {e}")
        return []


def save_data_to_csv(output_path, headers, data_rows):
    """Saves data to a CSV file with specified headers."""
    try:
        with open(output_path, 'w', newline='') as output_file:
            csv_writer = csv.DictWriter(output_file, fieldnames=headers)
            csv_writer.writeheader()
            csv_writer.writerows(data_rows)

        print(f"Data successfully saved to {output_path}.")

    except Exception as e:
        print(f"An error occurred while writing to the CSV file: {e}")


def link_memory_and_identify_mismatches():
    # File paths
    elf_objects_csv_path = csv_files_Dict['elf_objects_file']
    parsed_mapfile_csv_path = csv_files_Dict['map_file_parsing_csv']
    linked_memory_csv_path = csv_files_Dict['linked_memory_file']
    mismatch_memory_csv_path = csv_files_Dict['mismatch_memory_file']

    # Read data from CSV files
    elf_objects_data = load_csv_data(elf_objects_csv_path, ['Physical_Address', 'Size', 'Type', 'Object_Name'])
    parsed_mapfile_data = load_csv_data(parsed_mapfile_csv_path, ['Name', 'Type', 'Size', 'Location'])

    if not elf_objects_data or not parsed_mapfile_data:
        print("Something went wrong")
        return  # Exit if any file could not be read

    # Initialize lists for linked memory and mismatches
    linked_memory_entries = []
    mismatch_entries = []

    # Process the parsed mapfile entries
    for mapfile_entry in parsed_mapfile_data:
        mapfile_name = mapfile_entry['Name'].strip()
        matched = False

        # Debug: Show the current mapfile entry being processed
        print(f"Checking mapfile entry: {mapfile_name}")

        # Process the ELF objects
        for elf_entry in elf_objects_data:
            object_name = elf_entry['Object_Name'].strip()
            # Check for match
            if mapfile_name == object_name:
                linked_memory_entries.append({
                    'Name': object_name,
                    'Type': mapfile_entry['Type'],
                    'Size': mapfile_entry['Size'],
                    'Location': mapfile_entry['Location']
                })
                matched = True
                break  # Exit the loop once a match is found

        # Debug: Check if a match was found
        if matched:
            print(f"Matched: {mapfile_name}")
        else:
            print(f"No match found for: {mapfile_name}")
            # Append mismatches based on the mapfile entry
            mismatch_entries.append({
                'Name': mapfile_name,
                'Type': mapfile_entry['Type'],
                'Size': mapfile_entry['Size'],
                'Location': mapfile_entry['Location']
            })

    # Write linked memory entries to CSV
    save_data_to_csv(linked_memory_csv_path, ['Name', 'Type', 'Size', 'Location'], linked_memory_entries)
    # Write mismatches to CSV
    save_data_to_csv(mismatch_memory_csv_path, ['Name', 'Type', 'Size', 'Location'], mismatch_entries)

    # Debug: Show the final counts of matches and mismatches
    print(f"Total matched entries: {len(linked_memory_entries)}")
    print(f"Total mismatched entries: {len(mismatch_entries)}")


def count_type_sizes(csv_file, sections_list):
    """Count the total sizes for each type based on the configuration."""
    # Initialize section sizes based on provided sections list
    section_sizes = {section: 0 for section in sections_list}
    print("Initial section sizes:", section_sizes)

    try:
        with open(csv_file, mode='r', newline='') as file:
            reader = csv.reader(file, delimiter=',')  # Adjust delimiter if needed
            headers = next(reader, None)  # Skip header

            for row in reader:
                if len(row) < 4:
                    print("Skipping malformed row:", row)  # Debugging line
                    continue  # Skip malformed rows

                item_type = row[1].strip()  # Strip whitespace
                size_string = row[2].strip()  # Accessing size string by index (third column)

                # Debugging output for item_type
                print(f"Item type found: {repr(item_type)}")  # Print with representation

                # Remove leading dot from item_type if it exists
                item_type = item_type.lstrip('.')

                try:
                    # Convert size directly (assuming size_string is formatted correctly)
                    size = int(size_string.split()[0])  # Get the first part as size
                    print(f"Size extracted: {size}")  # Debugging output for size

                    # Add size to the corresponding type if it exists
                    if item_type in section_sizes:
                        section_sizes[item_type] += size
                    else:
                        print(f"Unknown type: {item_type}")  # Handle unknown types

                except ValueError:
                    print(f"Invalid size format: {size_string}")  # Debugging line for size conversion

    except FileNotFoundError:
        print(f"File not found: {csv_file}")
    except Exception as e:
        print(f"An error occurred: {e}")

    return section_sizes


def generate_memory_consumption_csv(file_path, sizes):
    # Calculate total ROM and RAM sizes
    rom_total = sizes['text'] + sizes['rodata']
    ram_total = sizes['bss'] + sizes['data']

    # Convert sizes to KB
    rom_kb = rom_total / 1024  # Total ROM size in KB
    ram_kb = ram_total / 1024  # Total RAM size in KB

    # Calculate percentages for ROM and RAM
    total_memory = rom_kb + ram_kb
    rom_percent = (rom_kb / total_memory * 100) if total_memory > 0 else 0
    ram_percent = (ram_kb / total_memory * 100) if total_memory > 0 else 0

    # Write results to a CSV file
    with open(file_path, 'w', newline='') as csvfile:
        writer = csv.writer(csvfile)

        # Write header
        writer.writerow(['Subject', 'Info'])

        # Write memory section sizes
        writer.writerow(['.text', sizes['text']])
        writer.writerow(['.data', sizes['data']])
        writer.writerow(['.rodata', sizes['rodata']])
        writer.writerow(['.bss', sizes['bss']])

        # Write total sizes
        writer.writerow(['ROM (total)', f"{rom_kb:.2f} KB"])
        writer.writerow(['RAM (total)', f"{ram_kb:.2f} KB"])

        # Write percentages
        writer.writerow(['ROM (%)', f"{rom_percent:.2f}% ({rom_kb:.2f} KB)"])
        writer.writerow(['RAM (%)', f"{ram_percent:.2f}% ({ram_kb:.2f} KB)"])
    # Further logic for processing sizes (like totaling them) would go here


def run_objdump_command(specific_flag_key=None):
    # Retrieve binary file path and supported extensions from the configuration
    binary_file_path = file_paths_Dict['binary_file_path']
    supported_extensions = config.get('supported_extensions', ['.elf', '.out'])

    # Get the file extension of the binary file
    file_extension = os.path.splitext(binary_file_path)[-1].lower()

    # Check if the file extension is supported
    if file_extension not in supported_extensions:
        raise ValueError(f"Unsupported binary file extension {file_extension}. Supported types: {supported_extensions}")

    # Fetch the objdump command template from the configuration
    objdump_command_template = config['commands']['objdump_command']

    # Choose file_path_key based on the file extension (both use the same binary path)
    if file_extension == '.elf':
        file_path_key = 'elf_file_path'
    elif file_extension == '.out':
        file_path_key = 'binary_file_path'
    else:
        raise ValueError(f"Unsupported binary file extension {file_extension}. Please provide a valid binary file.")

    # Handle specific flags if provided
    if specific_flag_key:
        flag_keys = [key.strip() for key in specific_flag_key.split(',')]
        objdump_flags = " ".join(ObjDump_flags_Dict.get(key, '') for key in flag_keys if key in ObjDump_flags_Dict)
    else:
        objdump_flags = config.get('objdump_flags', '-d')  # Default flag if none provided

    # Construct the objdump command using the template
    objdump_command = objdump_command_template.format(
        objdump_path=file_paths_Dict['objdump_path'],
        objdump_flags=objdump_flags,
        binary_file_path=binary_file_path,
        Assembly_txt=csv_files_Dict['assembly_file']
    )

    print("Constructed Objdump Command:", objdump_command)  # Debug: Show the command being run

    try:
        # Run the constructed command
        result = subprocess.run(objdump_command, shell=True, check=True, capture_output=True, text=True)
        print("Objdump command ran successfully!")
        print("Raw output:", result.stdout)  # Debug: Print raw output
        return result.stdout.strip()  # Return the stdout output
    except subprocess.CalledProcessError as e:
        print(f"Command failed with return code {e.returncode}")
        print(f"Error output: {e.stderr}")
        return None


# Main program execution
if __name__ == "__main__":
    try:

        # Get the map file path and output CSV file path from the JSON config
        map_file_path = file_paths_Dict['map_path']
        parsed_mapfile_csv = csv_files_Dict['map_file_parsing_csv']

        # Parse the map file
        entries = parse_map_file(map_file_path, Compiled_Regex_Patterns_Dict)

        # Write the parsed entries to a CSV file
        write_entries_to_csv(entries, parsed_mapfile_csv)

        # Run the NM command with or without specific flags
        run_nm_command(specific_flag_key='defined_only, print_size')  # Adjust flag key as necessary

        # Parse the map file
        #parsed_entries = parse_map_file(file_paths_Dict['map_file_path'], Compiled_Regex_Patterns_Dict)

        # Write parsed entries to CSV
        #write_entries_to_csv(parsed_entries, csv_files_Dict['map_file_parsing_csv'])

        # Process NM output and create the CSV
        parse_nm_output(csv_files_Dict['nm_objects_file'], csv_files_Dict['elf_objects_file'])

        # Link memory and identify mismatches
        link_memory_and_identify_mismatches()

        #csv_files_Dict
        #sections_list = ['text', 'data', 'bss', 'rodata']  # Define your sections list
        sizes = count_type_sizes(csv_files_Dict['linked_memory_file'], sections_list)
        generate_memory_consumption_csv(csv_files_Dict['memory_usage_file'], sizes)
        #print("******************SIZES************************")
        #print(sizes)

        run_objdump_command(specific_flag_key='disassemble_all')

    except Exception as e:
        print(f"An error occurred during execution: {e}")
