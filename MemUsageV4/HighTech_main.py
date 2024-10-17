###########################################################################################################
#                                         Imports                                                         #
###########################################################################################################
import json
import re
import csv
import subprocess
import os


############################## Load Configurations From Json file #########################################
def load_config(file_path):
    """Load configuration from a JSON file."""
    if not os.path.exists(file_path):
        raise FileNotFoundError(f"Configuration file not found: {file_path}")

    with open(file_path, 'r') as file:
        return json.load(file)


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
            "length": hex(length_bytes),  # Convert length to hexadecimal
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


# Main program execution
if __name__ == "__main__":
    try:

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
            output_file_path = "config.json"
            print_memory_regions_as_json(parsed_memory, output_file_path)
            # Print the parsed memory regions
            for region in parsed_memory:
                print(f"Name: {region['name']}, Attributes: {region['attributes']}, "
                      f"Origin: {region['origin']}, Length: {region['length']}")
        else:
            print("No MEMORY block found in the linker script.")


    except Exception as e:
        print(f"An error occurred during execution: {e}")
