import json
import re
import csv
import subprocess
import os
import json_handler

ToolChain_Config = json_handler.load_config('ToolChain_Config.json')


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
        r'(\w+)\s*\(([^)]+)\)\s*:\s*(?:ORIGIN|org|ORG|source)\s*=\s*([0xA-Fa-f0-9]+)\s*,\s*(?:LENGTH|len|LEN|size)\s*=\s*([\dKMG]+)',
        re.MULTILINE | re.IGNORECASE
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


def print_memory_regions_as_json(toolchain_name, memory_regions, file_path):
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
    MemoryRegionName = toolchain_name + "_MemoryRegions"
    output_data[MemoryRegionName] = processed_regions

    # Dump to JSON file
    with open(file_path, 'w') as json_file:
        json.dump(output_data, json_file, indent=4)


def Parse_and_Save_Size_Output(toolchain_name, size_output_file, output_json_file):
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

        SectionName = toolchain_name+"_Sections"
        total_size_dec = toolchain_name+"_total_size_decimal_Bytes"
        total_size_hexa = toolchain_name+"_total_size_hexa_Bytes"
        # Prepare parsed data
        parsed_output = {
            SectionName: sections,
            total_size_dec: total_size_decimal,
            total_size_hexa: total_size_hexa
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


if __name__ == "__main__":
    try:
        # ==============================for arm-none-eabi==============================
        linker_file_path = ToolChain_Config['toolchains_binary-utilities_filePaths']['arm_none_eabi'][
            'linkerScript_path']
        memory_block_content = extract_memory_block(linker_file_path)
        print(memory_block_content)
        memory_regions = parse_memory_regions(memory_block_content)
        MemoryConfigPath = "Memory_Config.json"
        print_memory_regions_as_json('arm_none_eabi',memory_regions, MemoryConfigPath)

        # ================================ for tricore =================================
        linker_file_path = ToolChain_Config['toolchains_binary-utilities_filePaths']['tricore'][
            'linkerScript_path']
        memory_block_content = extract_memory_block(linker_file_path)
        print(memory_block_content)
        memory_regions = parse_memory_regions(memory_block_content)
        MemoryConfigPath = "Memory_Config.json"
        print_memory_regions_as_json('tricore',memory_regions, MemoryConfigPath)

    except Exception as e:
        print("Error loading configurations:", e)
