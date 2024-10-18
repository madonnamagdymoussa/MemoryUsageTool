###########################################################################################################
#                                         Imports                                                         #
###########################################################################################################
import json
import re
import csv
import subprocess
import os


############################## Functions for Json file #########################################
def load_config(file_path):
    """Load configuration from a JSON file."""
    if not os.path.exists(file_path):
        raise FileNotFoundError(f"Configuration file not found: {file_path}")

    with open(file_path, 'r') as file:
        return json.load(file)

# Save the updated JSON data back to the file
def save_json(file_path, data):
    with open(file_path, 'w') as file:
        json.dump(data, file, indent=4)


# Load the configuration
config = load_config('config.json')

###########################################################################################################
#                                    HighTech Configurations                                              #
###########################################################################################################
HighTech_file_paths_Dict = config['HighTech_file_paths']  # Update to the new key name if changed
HighTech_csv_files_Dict = config['HighTech_csv_file_paths']
HighTech_ObjDump_flags_Dict = config['HighTech_ObjDump_flags']  # Updated key name for NM flags
HighTech_Object_file_paths_Dict = config['HighTech_Object_file_paths']
HighTech_NM_flags_Dict = config['HighTech_NM_flags']  # Updated key name for NM flags
HighTech_Size_flags_Dict = config['HighTech_Size_flags']
HighTech_Strip_flags_Dict = config['HighTech_Strip_flags']
HighTech_addr2line_flags_Dict = config['HighTech_addr2line_flags']


###########################################################################################################
#                                    HighTech Commands                                                    #
###########################################################################################################
# 1- Obj dump Command
# 2- NM Command
# 3- Size Command
# 4- Strip Command
# 5- addr2line Command


############################# 1- Obj dump Command #############################
def HighTech_Run_Objdump_Command(specific_flag_key=None, binary_file_path=None):
    binary_file_path = binary_file_path or HighTech_file_paths_Dict['binary_file_path']
    supported_extensions = config.get('HighTech_supported_extensions', ['.elf', '.out', '.o'])

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
    elif file_extension == '.o':
        file_path_key = 'binary_file_path'
    else:
        raise ValueError(f"Unsupported binary file extension {file_extension}. Please provide a valid binary file.")

    # Handle specific flags if provided
    if specific_flag_key:
        flag_keys = [key.strip() for key in specific_flag_key.split(',')]
        objdump_flags = " ".join(
            HighTech_ObjDump_flags_Dict.get(key, '') for key in flag_keys if key in HighTech_ObjDump_flags_Dict)
    else:
        objdump_flags = config.get('HighTech_ObjDump_flags_Dict', '-S')  # Default flag if none provided

    # Construct the objdump command using the template
    objdump_command = objdump_command_template.format(
        objdump_path=HighTech_file_paths_Dict['objdump_path'],
        objdump_flags=objdump_flags,
        binary_file_path=binary_file_path,
        Assembly_txt=HighTech_csv_files_Dict['assembly_file']
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


############################# 2- NM Command #############################
def HighTech_run_nm_command(specific_flag_key=None):
    binary_file_path = HighTech_file_paths_Dict['binary_file_path']
    supported_extensions = config.get('HighTech_supported_extensions', ['.elf', '.out'])

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
        nm_flags = " ".join(HighTech_NM_flags_Dict.get(key, '') for key in flag_keys if key in HighTech_NM_flags_Dict)
    else:
        nm_flags = " ".join(HighTech_NM_flags_Dict.values())

    nm_command = nm_command_template.format(
        nm_path=HighTech_file_paths_Dict['nm_path'],
        nm_flags=nm_flags,
        **{file_path_key: binary_file_path},
        nm_objects_txt=HighTech_csv_files_Dict['nm_objects_file']
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


############################# 3- Size Command #############################
def HighTech_run_Size_command(specific_flag_key=None):
    binary_file_path = HighTech_file_paths_Dict['binary_file_path']
    supported_extensions = config.get('HighTech_supported_extensions', ['.elf', '.out'])

    file_extension = os.path.splitext(binary_file_path)[-1].lower()

    if file_extension not in supported_extensions:
        raise ValueError(f"Unsupported binary file extension {file_extension}. Supported types: {supported_extensions}")

    if file_extension == '.elf':
        size_command_template = config['commands']['size_command']
        file_path_key = 'elf_file_path'
    elif file_extension == '.out':
        size_command_template = config['commands']['size_command']
        file_path_key = 'out_file_path'
    else:
        raise ValueError(f"Unsupported binary file extension {file_extension}. Please provide a valid binary file.")

    if specific_flag_key:
        flag_keys = [key.strip() for key in specific_flag_key.split(',')]
        size_flags = " ".join(
            HighTech_Size_flags_Dict.get(key, '') for key in flag_keys if key in HighTech_Size_flags_Dict)
    else:
        size_flags = " ".join(HighTech_Size_flags_Dict.values())

    size_command = size_command_template.format(
        size_path=HighTech_file_paths_Dict['size_utility_path'],
        size_flags=size_flags,
        binary_file_path=binary_file_path,
        SizeFile_txt=HighTech_csv_files_Dict['size_output_file']
    )

    print("Constructed Size Command:", size_command)  # Debug: Show the command being run

    try:
        result = subprocess.run(size_command, shell=True, check=True, capture_output=True, text=True)
        print("Size command ran successfully!")
        print("Raw output:", result.stdout)  # Debug: Print raw output
        return result.stdout.strip()
    except subprocess.CalledProcessError as e:
        print(f"Command failed with return code {e.returncode}")
        print(f"Error output: {e.stderr}")
        return None


############################# 4- Strip Command #############################
def HighTech_run_Strip_command(specific_flag_key=None):
    binary_file_path = HighTech_file_paths_Dict['binary_file_path']
    supported_extensions = config.get('HighTech_supported_extensions', ['.elf', '.out'])

    file_extension = os.path.splitext(binary_file_path)[-1].lower()

    if file_extension not in supported_extensions:
        raise ValueError(f"Unsupported binary file extension {file_extension}. Supported types: {supported_extensions}")

    if file_extension == '.elf':
        size_command_template = config['commands']['strip_command']
        file_path_key = 'elf_file_path'
    elif file_extension == '.out':
        size_command_template = config['commands']['strip_command']
        file_path_key = 'out_file_path'
    else:
        raise ValueError(f"Unsupported binary file extension {file_extension}. Please provide a valid binary file.")

    if specific_flag_key:
        flag_keys = [key.strip() for key in specific_flag_key.split(',')]
        strip_flags = " ".join(
            HighTech_Strip_flags_Dict.get(key, '') for key in flag_keys if key in HighTech_Strip_flags_Dict)
    else:
        strip_flags = " ".join(HighTech_Strip_flags_Dict.values())

    strip_command = size_command_template.format(
        strip_path=HighTech_file_paths_Dict['strip_utility_path'],
        strip_flags=strip_flags,
        binary_file_path=binary_file_path,
        strip_output_flag=HighTech_Strip_flags_Dict['OutputFile'],
        stripped_elf=HighTech_csv_files_Dict['stripped_output_elf_file']
    )

    print("Constructed Strip Command:", strip_command)  # Debug: Show the command being run

    try:
        result = subprocess.run(strip_command, shell=True, check=True, capture_output=True, text=True)
        print("Strip command ran successfully!")
        print("Raw output:", result.stdout)  # Debug: Print raw output
        return result.stdout.strip()
    except subprocess.CalledProcessError as e:
        print(f"Command failed with return code {e.returncode}")
        print(f"Error output: {e.stderr}")
        return None


############################# 5- addr2line Command #############################
def HighTech_run_addr2line_path_command(specific_flag_key=None, Address=None):
    binary_file_path = HighTech_file_paths_Dict['binary_file_path']
    supported_extensions = config.get('HighTech_supported_extensions', ['.elf', '.out'])

    file_extension = os.path.splitext(binary_file_path)[-1].lower()

    if file_extension not in supported_extensions:
        raise ValueError(f"Unsupported binary file extension {file_extension}. Supported types: {supported_extensions}")

    if file_extension == '.elf':
        addr2line_command = config['commands']['addr2line_command']
        file_path_key = 'elf_file_path'
    elif file_extension == '.out':
        addr2line_command = config['commands']['addr2line_command']
        file_path_key = 'out_file_path'
    else:
        raise ValueError(f"Unsupported binary file extension {file_extension}. Please provide a valid binary file.")

    if specific_flag_key:
        flag_keys = [key.strip() for key in specific_flag_key.split(',')]
        strip_flags = " ".join(
            HighTech_addr2line_flags_Dict.get(key, '') for key in flag_keys if key in HighTech_addr2line_flags_Dict)
    else:
        strip_flags = " ".join(HighTech_addr2line_flags_Dict.values())

    addr2line_command = addr2line_command.format(
        addr2line_Path=HighTech_file_paths_Dict['addr2line_path'],
        ExecutableName_flag=HighTech_addr2line_flags_Dict['ExecutableName'],
        binary_file_path=binary_file_path.strip(),
        flags=strip_flags,
        HexadecimalAddress=Address,
        addr2line_Output_txt=HighTech_csv_files_Dict['addr2line_output_file']
    )

    print("Constructed addr2line Command:", addr2line_command)  # Debug: Show the command being run

    try:
        result = subprocess.run(addr2line_command, shell=True, check=True, capture_output=True, text=True)
        print("Strip command ran successfully!")
        print("Raw output:", result.stdout)  # Debug: Print raw output
        return result.stdout.strip()
    except subprocess.CalledProcessError as e:
        print(f"Command failed with return code {e.returncode}")
        print(f"Error output: {e.stderr}")
        return None


###########################################################################################################
#                    Functions For calculating memory usage for each section                              #
###########################################################################################################

def extract_memory_block(file_path):
    # Read the linker script file
    with open(file_path, 'r') as file:
        content = file.read()

    # Define the regular expression to match the MEMORY block
    memory_block_pattern = re.compile(
        r'MEMORY\s*\{(.*?)\}',  # Allow any whitespace/newlines between MEMORY and {
        re.MULTILINE | re.DOTALL
    )

    # Extract the MEMORY block content
    memory_block_match = memory_block_pattern.search(content)
    if memory_block_match:
        return memory_block_match.group(1)
    else:
        return None


def parse_memory_regions(memory_block):
    # Define the regex to match individual memory regions within the MEMORY block
    memory_pattern = re.compile(
        r'(\w+)\s*\(([^)]+)\):\s*org\s*=\s*([0xA-Fa-f0-9]+),\s*len\s*=\s*([\dKMG]+)',
        re.MULTILINE
    )

    # Extract memory regions
    memory_regions = []
    for match in memory_pattern.finditer(memory_block):
        name = match.group(1)
        attributes = match.group(2).strip()
        origin = match.group(3)
        length = match.group(4)

        # Store each memory region as a dictionary
        memory_region = {
            "name": name,
            "attributes": attributes,
            "origin": origin,
            "length": length
        }
        memory_regions.append(memory_region)

    return memory_regions


def convert_length_to_bytes(length):
    """Converts a memory length string (like '2M', '32K') to bytes."""
    if 'K' in length:
        return int(length.replace('K', '')) * 1024
    elif 'M' in length:
        return int(length.replace('M', '')) * 1024 ** 2
    elif 'G' in length:
        return int(length.replace('G', '')) * 1024 ** 3
    else:
        return int(length)


def print_memory_regions_as_json(memory_regions, file_path):
    """Prints memory regions as JSON, appending to existing data."""
    processed_regions = []

    for region in memory_regions:
        origin = int(region['origin'], 16)  # Convert origin from hex to int
        length_bytes = convert_length_to_bytes(region['length'])  # Convert length to bytes

        end_address = origin + length_bytes  # Calculate end address

        # Prepare the new dictionary with the required transformations
        processed_region = {
            "name": region['name'],
            "attributes": region['attributes'],
            "origin": region['origin'],
            "length_hexa_bytes": hex(length_bytes),  # Convert length to hexadecimal
            "length_decimal_bytes": length_bytes,  # Convert length to hexadecimal
            "end_address": hex(end_address)  # Store end address in hexadecimal
        }

        processed_regions.append(processed_region)

    # Check if the file exists and load existing data
    output_data = {}
    if os.path.exists(file_path):
        with open(file_path, 'r') as json_file:
            try:
                output_data = json.load(json_file)
            except json.JSONDecodeError:
                print(f"Error decoding JSON from {file_path}. Starting with an empty structure.")

    # Update the existing dictionary with new memory regions
    output_data["HighTechMemoryRegions"] = processed_regions

    # Dump to JSON file
    with open(file_path, 'w') as json_file:
        json.dump(output_data, json_file, indent=4)


def HighTech_Parse_and_Save_Size_Output(size_output_file, output_json_file):
    # Regular expression to match the section entries
    section_pattern = re.compile(r"^(\S+)\s+([0-9a-fx]+)\s+([0-9a-fx]+)$", re.IGNORECASE)
    total_pattern = re.compile(r"^Total\s+([0-9a-fx]+)$", re.IGNORECASE)

    sections = []
    total_size_decimal = None
    total_size_hexa = None

    try:
        with open(size_output_file, 'r') as file:
            lines = file.readlines()

            for line in lines:
                # Check for a section line using regex
                match = section_pattern.match(line.strip())
                if match:
                    section_name = match.group(1)
                    section_size_decimal = int(match.group(2), 16)  # Convert hex size to integer
                    section_size_hexa = match.group(2)  # Keep hex size as string
                    section_addr = match.group(3)

                    sections.append({
                        "SectionName": section_name,
                        "SectionSize_Decimal_Bytes": section_size_decimal,
                        "SectionSize_Hexa_Bytes": section_size_hexa,
                        "SectionAddress": section_addr,

                    })

                # Check for the total size line
                total_match = total_pattern.match(line.strip())
                if total_match:
                    total_size_decimal = int(total_match.group(1), 16)  # Convert hex total to integer
                    total_size_hexa = total_match.group(1)

        # Prepare parsed data
        parsed_output = {
            "HighTechSections": sections,
            "total_size_decimal_Bytes": total_size_decimal,
            "total_size_hexa_Bytes": total_size_hexa
        }

        # Load existing data from the output JSON file if it exists
        try:
            with open(output_json_file, "r") as json_file:
                existing_data = json.load(json_file)
        except (FileNotFoundError, json.JSONDecodeError):
            existing_data = {}

        # Update the existing data with parsed output
        existing_data.update(parsed_output)

        # Save the updated data back to the JSON file
        with open(output_json_file, "w") as json_file:
            json.dump(existing_data, json_file, indent=4)

        print(f"Parsed sections added to {output_json_file}")
        return existing_data

    except FileNotFoundError:
        print(f"Error: File {size_output_file} not found.")
        return None
    except Exception as e:
        print(f"An error occurred: {e}")
        return None


def add_memory_type_to_sections(high_tech_sections, high_tech_memory_regions):
    # Iterate over each section in the high_tech_sections list
    for section in high_tech_sections:
        try:
            # Convert SectionAddress from hex string to integer for comparison
            section_address = int(section.get("SectionAddress", "0"), 16)

            # Flag to indicate if a matching memory region is found
            memory_type_found = False

            # Loop through memory regions to find the matching range
            for region in high_tech_memory_regions:
                origin = int(region.get("origin", "0"), 16)
                end_address = int(region.get("end_address", "0"), 16)

                # Check if the section address is within the range of the memory region
                if origin <= section_address <= end_address:
                    # Add the memory type to the section dictionary
                    section["MemoryType"] = region.get("name", "Unknown")
                    memory_type_found = True
                    break  # Stop searching once a match is found

            # If no matching region is found, set MemoryType to None
            if not memory_type_found:
                section["MemoryType"] = "None"

        except ValueError as e:
            print(f"Error processing section {section.get('SectionName', 'Unknown')}: {e}")
            section["MemoryType"] = "Error"

    return high_tech_sections


def add_consumed_percentage_to_sections(high_tech_sections, high_tech_memory_regions):
    # Create a mapping of memory region names to their total sizes
    memory_region_sizes = {region["name"]: region["length_decimal_bytes"] for region in high_tech_memory_regions}

    # Iterate over each section to calculate and add the consumed percentage
    for section in high_tech_sections:
        memory_type = section.get("MemoryType")

        # Check if the section has a valid memory type and corresponding memory region size
        if memory_type in memory_region_sizes:
            # Get the section size in bytes
            section_size = section.get("SectionSize_Decimal_Bytes", 0)

            # Get the total memory size of the corresponding memory type
            total_memory_size = memory_region_sizes[memory_type]

            # Calculate the consumed percentage
            consumed_percentage = (section_size / total_memory_size) * 100

            # Add the calculated percentage to the section dictionary
            section["consumed_percentage_MemType"] = round(consumed_percentage,
                                                           4)  # Round to 4 decimal places for clarity
        else:
            # If no matching memory type is found, set the percentage to None or an appropriate value
            section["consumed_percentage_MemType"] = None

    return high_tech_sections


# Main program execution
if __name__ == "__main__":
    try:

        Config_file_path = "config.json"
        HighTech_Run_Objdump_Command(specific_flag_key='Disassemble', binary_file_path=None)
        HighTech_run_nm_command(specific_flag_key='defined_only, print_size')
        HighTech_run_Size_command(specific_flag_key='format, SizeDecimal')
        HighTech_run_Strip_command(specific_flag_key='RemoveDebugging')
        HighTech_run_addr2line_path_command(specific_flag_key='DisplayFunctionName', Address='800020fa')

        ########################################## Calculate Memory Usage ###########################################
        linker_script_path = HighTech_file_paths_Dict[
            'linkerScript_path']  # Replace with the path to your linker script

        # Step 1: Extract MEMORY block
        memory_block_content = extract_memory_block(linker_script_path)

        if memory_block_content:
            # Step 2: Parse the extracted MEMORY block
            parsed_memory = parse_memory_regions(memory_block_content)

            print_memory_regions_as_json(parsed_memory, Config_file_path)
            # Print the parsed memory regions
            for region in parsed_memory:
                print(f"Name: {region['name']}, Attributes: {region['attributes']}, "
                      f"Origin: {region['origin']}, Length: {region['length']}")
        else:
            print("No MEMORY block found in the linker script.")

        size_output_file = HighTech_csv_files_Dict['size_output_file']
        parsed_data = HighTech_Parse_and_Save_Size_Output(size_output_file, Config_file_path)

        high_tech_sections = config.get("HighTechSections")
        high_tech_memory_regions = config.get("HighTechMemoryRegions")
        # Call the function to add MemoryType to each section
        updated_sections = add_memory_type_to_sections(high_tech_sections, high_tech_memory_regions)

        # Print the updated sections
        print(updated_sections)

        config["HighTechSections"] = updated_sections
        save_json(Config_file_path, config)

        print("JSON file updated successfully!")

        # Add consumed percentage
        updated_sections = add_consumed_percentage_to_sections(high_tech_sections, high_tech_memory_regions)
        config["HighTechSections"] = updated_sections
        save_json(Config_file_path, config)

    except Exception as e:
        print(f"An error occurred during execution: {e}")
