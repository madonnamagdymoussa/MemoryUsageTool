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
        r'(\w+)\s*\(([^)]+)\)\s*:\s*(?:org|ORG|origin|ORIGIN)\s*=\s*([0xA-Fa-f0-9]+)\s*,\s*(?:len|LEN|length|LENGTH)\s*=\s*(0x[A-Fa-f0-9]+|[\dKMGkmg]+)',
        re.MULTILINE | re.IGNORECASE
    )

    # Extract memory regions
    memory_regions = []
    for match in memory_pattern.finditer(memory_block):
        name = match.group(1).strip()
        attributes = match.group(2).strip()
        origin = match.group(3).strip()
        length = match.group(4).strip()

        # Convert length to a consistent format
        length_value = convert_length_to_decimal(length)

        # Store each memory region as a dictionary
        memory_region = {
            "name": name,
            "attributes": attributes,
            "origin": origin,
            "length": length,
            "length_value": length_value
        }
        memory_regions.append(memory_region)

    return memory_regions


def convert_length_to_decimal(length):
    """ Convert lengths with K, M, G suffixes to decimal bytes. """
    if length.endswith('K'):
        return int(length[:-1]) * 1024  # Kilobytes to bytes
    elif length.endswith('M'):
        return int(length[:-1]) * 1024 * 1024  # Megabytes to bytes
    elif length.endswith('G'):
        return int(length[:-1]) * 1024 * 1024 * 1024  # Gigabytes to bytes
    elif length.startswith('0x'):
        return int(length, 16)  # Hexadecimal to decimal
    else:
        return int(length)  # Decimal


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
        # Determine if the length is in hex or decimal
        length = region['length'].strip()  # Remove any surrounding whitespace
        print(f"Processing length: {length}")  # Verify the raw length value
        if length.lower().startswith('0x'):
            # Convert hex length directly to an integer
            length_bytes = int(length, 16)

        else:
            # Assume it's a decimal and use the convert function
            length_bytes = convert_length_to_bytes(length)

        #length_bytes = convert_length_to_bytes(region['length'])  # Convert length to bytes

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
    total_size_hexadec = None

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
                    total_size_hexadec = total_match.group(1)

        SectionName = toolchain_name+"_Sections"
        total_size_dec = toolchain_name+"_total_size_decimal_Bytes"
        total_size_hexa = toolchain_name+"_total_size_hexa_Bytes"
        # Prepare parsed data
        parsed_output = {
            SectionName: sections,
            total_size_dec: total_size_decimal,
            total_size_hexa: total_size_hexadec
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

def add_memory_type_to_sections(sections, memory_regions):
    # Iterate over each section in the high_tech_sections list
    for section in sections:
        try:
            # Convert SectionAddress from hex string to integer for comparison
            section_address = int(section.get("SectionAddress", "0"), 16)

            # Flag to indicate if a matching memory region is found
            memory_type_found = False

            # Loop through memory regions to find the matching range
            for region in memory_regions:
                origin = int(region.get("origin", "0"), 16)
                end_address = int(region.get("end_address", "0"), 16)
                # Check if the section address is within the range of the memory region
                if origin <= section_address < end_address:
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

    return sections

def add_consumed_percentage_to_sections(toolchain_name,sections, memory_regions):
    # Create a mapping of memory region names to their total sizes
    MemoryRegionName = toolchain_name + "_MemoryRegions"
    SectionName = toolchain_name + "_Sections"
    memory_region_sizes = {region["name"]: region["length_decimal_bytes"] for region in memory_regions}

    # Iterate over each section to calculate and add the consumed percentage
    for section in sections:
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

    return sections


def add_consumed_size_to_memory_regions(sections, memory_regions):
    # Initialize consumed size for each memory region
    for region in memory_regions:
        region["Consumed_Size"] = 0

    # Sum up the section sizes based on their MemoryType
    for section in sections:
        memory_type = section.get("MemoryType")
        section_size = section.get("SectionSize_Decimal_Bytes", 0)

        # Find the corresponding memory region and add the section size
        for region in memory_regions:
            if region.get("name") == memory_type:
                region["Consumed_Size"] += section_size
                break

    # Calculate the percentage consumed for each memory region
    for region in memory_regions:
        total_memory_size = region.get("length_decimal_bytes", 0)
        consumed_size = region.get("Consumed_Size", 0)

        if total_memory_size > 0:
            region["PercentageConsumedSize"] = (consumed_size / total_memory_size) * 100
        else:
            region["PercentageConsumedSize"] = 0.0  # Handle edge case where total size is zero

    return memory_regions


def create_memory_consumption_csv(sections, memory_regions,
                                  filename=None):
    # Open the CSV file in write mode
    with open(filename, mode='w', newline='') as file:
        writer = csv.writer(file)

        # Write the first table for HighTechSections
        writer.writerow(["Section Name", "Section Size in Bytes (Decimal Format)",
                         "Section Size in Bytes (Hexadecimal Format)", "Section Address",
                         "Memory Name", "Consumed Percentage from MemoryType"])

        for section in sections:
            writer.writerow([
                section.get("SectionName", "N/A"),
                section.get("SectionSize_Decimal_Bytes", "N/A"),
                section.get("SectionSize_Hexa_Bytes", "N/A"),
                section.get("SectionAddress", "N/A"),
                section.get("MemoryType", "N/A"),
                section.get("consumed_percentage_MemType", "N/A")
            ])

        # Leave a blank line between the two tables
        writer.writerow([])

        # Write the second table for HighTechMemoryRegions
        writer.writerow(["Memory Name", "Attributes", "Origin Address",
                         "Length in Hexa Bytes", "Length in Decimal Bytes",
                         "End Address", "Consumed Size", "Percentage Consumed Size"])

        for region in memory_regions:
            writer.writerow([
                region.get("name", "N/A"),
                region.get("attributes", "N/A"),
                region.get("origin", "N/A"),
                region.get("length_hexa_bytes", "N/A"),
                region.get("length_decimal_bytes", "N/A"),
                region.get("end_address", "N/A"),
                region.get("Consumed_Size", "N/A"),
                region.get("PercentageConsumedSize", "N/A")
            ])

    print(f"Memory consumption details have been written to {filename}.")



if __name__ == "__main__":
    try:
        MemoryConfigPath = "Memory_Config.json"

        # ==============================for arm-none-eabi==============================
        linker_file_path = ToolChain_Config['toolchains_binary-utilities_filePaths']['arm_none_eabi'][
            'linkerScript_path']
        memory_block_content = extract_memory_block(linker_file_path)
        print(memory_block_content)
        memory_regions = parse_memory_regions(memory_block_content)
        print_memory_regions_as_json('arm_none_eabi', memory_regions, MemoryConfigPath)

        size_output_file = ToolChain_Config['toolchains_output_files']['arm_none_eabi']['size_sections_file_txt']
        Parse_and_Save_Size_Output('arm_none_eabi', size_output_file, MemoryConfigPath)


        Memory_Config = json_handler.load_config(MemoryConfigPath)
        mem_regions_dict = Memory_Config['arm_none_eabi_MemoryRegions']
        sections_dict = Memory_Config['arm_none_eabi_Sections']
        add_memory_type_to_sections(sections_dict, mem_regions_dict)
        json_handler.save_config(MemoryConfigPath, Memory_Config)

        Memory_Config = json_handler.load_config(MemoryConfigPath)
        mem_regions_dict = Memory_Config['arm_none_eabi_MemoryRegions']
        sections_dict = Memory_Config['arm_none_eabi_Sections']
        add_consumed_percentage_to_sections('arm_none_eabi', sections_dict, mem_regions_dict)
        json_handler.save_config(MemoryConfigPath, Memory_Config)

        Memory_Config = json_handler.load_config(MemoryConfigPath)
        mem_regions_dict = Memory_Config['arm_none_eabi_MemoryRegions']
        sections_dict = Memory_Config['arm_none_eabi_Sections']
        add_consumed_size_to_memory_regions(sections_dict, mem_regions_dict)
        json_handler.save_config(MemoryConfigPath, Memory_Config)

        Memory_Config = json_handler.load_config(MemoryConfigPath)
        mem_regions_dict = Memory_Config['arm_none_eabi_MemoryRegions']
        sections_dict = Memory_Config['arm_none_eabi_Sections']
        MemConsumptionFile=ToolChain_Config['toolchains_output_files']['arm_none_eabi']['memory_usage_file_csv']
        create_memory_consumption_csv(sections_dict, mem_regions_dict,filename=MemConsumptionFile)

        # ================================ for tricore =================================
        linker_file_path = ToolChain_Config['toolchains_binary-utilities_filePaths']['tricore'][
            'linkerScript_path']
        memory_block_content = extract_memory_block(linker_file_path)
        print(memory_block_content)
        memory_regions = parse_memory_regions(memory_block_content)
        MemoryConfigPath = "Memory_Config.json"
        print_memory_regions_as_json('tricore',memory_regions, MemoryConfigPath)
        size_output_file=ToolChain_Config['toolchains_output_files']['tricore']['size_sections_file_txt']
        Parse_and_Save_Size_Output('tricore', size_output_file, MemoryConfigPath)

        Memory_Config = json_handler.load_config(MemoryConfigPath)
        mem_regions_dict_tricore = Memory_Config['tricore_MemoryRegions']
        sections_dict_tricore = Memory_Config['tricore_Sections']
        add_memory_type_to_sections(sections_dict_tricore, mem_regions_dict_tricore)
        json_handler.save_config(MemoryConfigPath, Memory_Config)


        Memory_Config = json_handler.load_config(MemoryConfigPath)
        mem_regions_dict = Memory_Config['tricore_MemoryRegions']
        sections_dict = Memory_Config['tricore_Sections']
        add_consumed_percentage_to_sections('tricore', sections_dict, mem_regions_dict)
        json_handler.save_config(MemoryConfigPath, Memory_Config)

        Memory_Config = json_handler.load_config(MemoryConfigPath)
        mem_regions_dict = Memory_Config['tricore_MemoryRegions']
        sections_dict = Memory_Config['tricore_Sections']
        add_consumed_size_to_memory_regions(sections_dict, mem_regions_dict)
        json_handler.save_config(MemoryConfigPath, Memory_Config)

        Memory_Config = json_handler.load_config(MemoryConfigPath)
        mem_regions_dict = Memory_Config['tricore_MemoryRegions']
        sections_dict = Memory_Config['tricore_Sections']
        MemConsumptionFile=ToolChain_Config['toolchains_output_files']['tricore']['memory_usage_file_csv']
        create_memory_consumption_csv(sections_dict, mem_regions_dict,filename=MemConsumptionFile)

        # ================================ for ti_cgt_arm =================================
        linker_file_path = ToolChain_Config['toolchains_binary-utilities_filePaths']['ti_cgt_arm'][
            'linkerScript_path']
        memory_block_content = extract_memory_block(linker_file_path)
        print(memory_block_content)
        memory_regions = parse_memory_regions(memory_block_content)
        print("************ti_cgt_arm*************")
        print(memory_regions)
        MemoryConfigPath = "Memory_Config.json"
        print_memory_regions_as_json('ti_cgt_arm',memory_regions, MemoryConfigPath)
        size_output_file=ToolChain_Config['toolchains_output_files']['ti_cgt_arm']['size_sections_file_txt']
        Parse_and_Save_Size_Output('ti_cgt_arm', size_output_file, MemoryConfigPath)


        Memory_Config = json_handler.load_config(MemoryConfigPath)
        mem_regions_dict = Memory_Config['ti_cgt_arm_MemoryRegions']
        sections_dict = Memory_Config['ti_cgt_arm_Sections']
        add_memory_type_to_sections(sections_dict, mem_regions_dict)
        json_handler.save_config(MemoryConfigPath, Memory_Config)

        Memory_Config = json_handler.load_config(MemoryConfigPath)
        mem_regions_dict = Memory_Config['ti_cgt_arm_MemoryRegions']
        sections_dict = Memory_Config['ti_cgt_arm_Sections']
        add_consumed_percentage_to_sections('ti_cgt_arm', sections_dict, mem_regions_dict)
        json_handler.save_config(MemoryConfigPath, Memory_Config)

        Memory_Config = json_handler.load_config(MemoryConfigPath)
        mem_regions_dict = Memory_Config['ti_cgt_arm_MemoryRegions']
        sections_dict = Memory_Config['ti_cgt_arm_Sections']
        add_consumed_size_to_memory_regions(sections_dict, mem_regions_dict)
        json_handler.save_config(MemoryConfigPath, Memory_Config)

        Memory_Config = json_handler.load_config(MemoryConfigPath)
        mem_regions_dict = Memory_Config['ti_cgt_arm_MemoryRegions']
        sections_dict = Memory_Config['ti_cgt_arm_Sections']
        MemConsumptionFile=ToolChain_Config['toolchains_output_files']['ti_cgt_arm']['memory_usage_file_csv']
        create_memory_consumption_csv(sections_dict, mem_regions_dict,filename=MemConsumptionFile)

        # ================================ for ti_cgt_armllvm =================================
        linker_file_path = ToolChain_Config['toolchains_binary-utilities_filePaths']['ti_cgt_armllvm'][
            'linkerScript_path']
        memory_block_content = extract_memory_block(linker_file_path)
        print(memory_block_content)
        memory_regions = parse_memory_regions(memory_block_content)
        MemoryConfigPath = "Memory_Config.json"
        print_memory_regions_as_json('ti_cgt_armllvm',memory_regions, MemoryConfigPath)
        size_output_file=ToolChain_Config['toolchains_output_files']['ti_cgt_armllvm']['size_sections_file_txt']
        Parse_and_Save_Size_Output('ti_cgt_armllvm', size_output_file, MemoryConfigPath)

        Memory_Config = json_handler.load_config(MemoryConfigPath)
        mem_regions_dict = Memory_Config['ti_cgt_armllvm_MemoryRegions']
        sections_dict = Memory_Config['ti_cgt_armllvm_Sections']
        add_memory_type_to_sections(sections_dict, mem_regions_dict)
        json_handler.save_config(MemoryConfigPath, Memory_Config)

        Memory_Config = json_handler.load_config(MemoryConfigPath)
        mem_regions_dict = Memory_Config['ti_cgt_armllvm_MemoryRegions']
        sections_dict = Memory_Config['ti_cgt_armllvm_Sections']
        add_consumed_percentage_to_sections('ti_cgt_armllvm', sections_dict, mem_regions_dict)
        json_handler.save_config(MemoryConfigPath, Memory_Config)

        Memory_Config = json_handler.load_config(MemoryConfigPath)
        mem_regions_dict = Memory_Config['ti_cgt_armllvm_MemoryRegions']
        sections_dict = Memory_Config['ti_cgt_armllvm_Sections']
        add_consumed_size_to_memory_regions(sections_dict, mem_regions_dict)
        json_handler.save_config(MemoryConfigPath, Memory_Config)

        Memory_Config = json_handler.load_config(MemoryConfigPath)
        mem_regions_dict = Memory_Config['ti_cgt_armllvm_MemoryRegions']
        sections_dict = Memory_Config['ti_cgt_armllvm_Sections']
        MemConsumptionFile=ToolChain_Config['toolchains_output_files']['ti_cgt_armllvm']['memory_usage_file_csv']
        create_memory_consumption_csv(sections_dict, mem_regions_dict,filename=MemConsumptionFile)


    except Exception as e:
        print("Error loading configurations:", e)
