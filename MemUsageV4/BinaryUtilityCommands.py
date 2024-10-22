import json
import re
import csv
import subprocess
import os
import json_handler


config = json_handler.load_config('ToolChain_Config.json')

###########################################################################################################
#                                    Supported Commands Commands                                          #
###########################################################################################################

def run_objdump_command(toolchain_name, specific_flag_key=None,tool_flag_name='gnu_command_flags'):
    # Retrieve toolchain-specific paths and settings
    toolchain_config = config['toolchains_binary-utilities_filePaths'].get(toolchain_name)
    if not toolchain_config:
        raise ValueError(f"Toolchain '{toolchain_name}' is not defined in the configuration.")

    binary_file_path = toolchain_config['binary_file_path']
    supported_extensions = config.get('supported_extensions', ['.elf', '.out'])

    # Get the file extension of the binary file
    file_extension = os.path.splitext(binary_file_path)[-1].lower()

    # Check if the file extension is supported
    if file_extension not in supported_extensions:
        raise ValueError(
            f"Unsupported binary file extension '{file_extension}'. Supported types: {supported_extensions}")

    # Fetch the objdump command template from the configuration
    objdump_command_template = config['gnu_commands']['objdump_command']

    # Handle specific flags if provided
    objdump_flags_dict = config['toolchains_command_flags'][tool_flag_name]['ObjDump_flags']
    if specific_flag_key:
        flag_keys = [key.strip() for key in specific_flag_key.split(',')]
        objdump_flags = " ".join(objdump_flags_dict.get(key, '') for key in flag_keys if key in objdump_flags_dict)
    else:
        objdump_flags = config.get('default_objdump_flags', '-d')  # Default flag if none provided

    # Construct the objdump command using the template
    objdump_command = objdump_command_template.format(
        objdump_path=toolchain_config['objdump_path'],
        objdump_flags=objdump_flags,
        binary_file_path=binary_file_path,
        Assembly_txt=config['toolchains_output_files'][toolchain_name]['assembly_file_txt']
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


def run_size_command(toolchain_name, specific_flag_key=None,tool_flag_name='gnu_command_flags'):
    # Retrieve toolchain-specific paths and settings
    toolchain_config = config['toolchains_binary-utilities_filePaths'].get(toolchain_name)
    if not toolchain_config:
        raise ValueError(f"Toolchain '{toolchain_name}' is not defined in the configuration.")

    binary_file_path = toolchain_config['binary_file_path']
    supported_extensions = config.get('supported_extensions', ['.elf', '.out'])

    # Get the file extension of the binary file
    file_extension = os.path.splitext(binary_file_path)[-1].lower()

    # Check if the file extension is supported
    if file_extension not in supported_extensions:
        raise ValueError(
            f"Unsupported binary file extension '{file_extension}'. Supported types: {supported_extensions}")

    # Fetch the objdump command template from the configuration
    size_command_template = config['gnu_commands']['size_command']

    # Handle specific flags if provided
    size_flags_dict = config['toolchains_command_flags'][tool_flag_name]['Size_flags']
    if specific_flag_key:
        flag_keys = [key.strip() for key in specific_flag_key.split(',')]
        size_flags = " ".join(size_flags_dict.get(key, '') for key in flag_keys if key in size_flags_dict)
    else:
        size_flags = config.get('default_size_flags', '-A')  # Default flag if none provided

    # Construct the objdump command using the template
    size_command = size_command_template.format(
        size_path=toolchain_config['size_utility_path'],
        size_flags=size_flags,
        binary_file_path=binary_file_path,
        SizeFile_txt=config['toolchains_output_files'][toolchain_name]['size_sections_file_txt']
    )

    print("Constructed Size Command:", size_command)  # Debug: Show the command being run

    try:
        # Run the constructed command
        result = subprocess.run(size_command, shell=True, check=True, capture_output=True, text=True)
        print("Size command ran successfully!")
        print("Raw output:", result.stdout)  # Debug: Print raw output
        return result.stdout.strip()  # Return the stdout output
    except subprocess.CalledProcessError as e:
        print(f"Command failed with return code {e.returncode}")
        print(f"Error output: {e.stderr}")
        return None


def run_nm_command(toolchain_name, specific_flag_key=None,tool_flag_name='gnu_command_flags'):
    # Retrieve toolchain-specific paths and settings
    toolchain_config = config['toolchains_binary-utilities_filePaths'].get(toolchain_name)
    if not toolchain_config:
        raise ValueError(f"Toolchain '{toolchain_name}' is not defined in the configuration.")

    binary_file_path = toolchain_config['binary_file_path']
    supported_extensions = config.get('supported_extensions', ['.elf', '.out'])

    # Get the file extension of the binary file
    file_extension = os.path.splitext(binary_file_path)[-1].lower()

    # Check if the file extension is supported
    if file_extension not in supported_extensions:
        raise ValueError(
            f"Unsupported binary file extension '{file_extension}'. Supported types: {supported_extensions}")

    # Fetch the objdump command template from the configuration
    nm_command_template = config['gnu_commands']['nm_command']

    # Handle specific flags if provided
    nm_flags_dict = config['toolchains_command_flags'][tool_flag_name]['NM_flags']
    if specific_flag_key:
        flag_keys = [key.strip() for key in specific_flag_key.split(',')]
        nm_flags = " ".join(nm_flags_dict.get(key, '') for key in flag_keys if key in nm_flags_dict)
    else:
        nm_flags = config.get('default_nm_flags', '--print-size')  # Default flag if none provided

    # Construct the objdump command using the template
    nm_command = nm_command_template.format(
        nm_path=toolchain_config['nm_path'],
        nm_flags=nm_flags,
        binary_file_path=binary_file_path,
        nm_objects_txt=config['toolchains_output_files'][toolchain_name]['nm_objects_file_txt']
    )

    print("Constructed nm Command:", nm_command)  # Debug: Show the command being run

    try:
        # Run the constructed command
        result = subprocess.run(nm_command, shell=True, check=True, capture_output=True, text=True)
        print("nm command ran successfully!")
        print("Raw output:", result.stdout)  # Debug: Print raw output
        return result.stdout.strip()  # Return the stdout output
    except subprocess.CalledProcessError as e:
        print(f"Command failed with return code {e.returncode}")
        print(f"Error output: {e.stderr}")
        return None


def run_addr2line_command(toolchain_name, specific_flag_key=None, Address=None,tool_flag_name='gnu_command_flags'):
    # Retrieve toolchain-specific paths and settings
    toolchain_config = config['toolchains_binary-utilities_filePaths'].get(toolchain_name)
    if not toolchain_config:
        raise ValueError(f"Toolchain '{toolchain_name}' is not defined in the configuration.")

    binary_file_path = toolchain_config['binary_file_path']
    supported_extensions = config.get('supported_extensions', ['.elf', '.out'])

    # Get the file extension of the binary file
    file_extension = os.path.splitext(binary_file_path)[-1].lower()

    # Check if the file extension is supported
    if file_extension not in supported_extensions:
        raise ValueError(
            f"Unsupported binary file extension '{file_extension}'. Supported types: {supported_extensions}")

    # Fetch the objdump command template from the configuration
    addr2line_command_template = config['gnu_commands']['addr2line_command']

    # Handle specific flags if provided
    addr2line_flags_dict = config['toolchains_command_flags'][tool_flag_name]['Addr2line_flags']
    ExecutableName_flag = config['toolchains_command_flags'][tool_flag_name]['Addr2line_flags']['ExecutableName']

    if specific_flag_key:
        flag_keys = [key.strip() for key in specific_flag_key.split(',')]
        addr2line_flags = " ".join(
            addr2line_flags_dict.get(key, '') for key in flag_keys if key in addr2line_flags_dict)
    else:
        addr2line_flags = config.get('default_addr2line_flags', '-f')  # Default flag if none provided

    # Construct the objdump command using the template
    addr2line_command = addr2line_command_template.format(
        addr2line_Path=toolchain_config['addr2line_path'],
        ExecutableName_flag=ExecutableName_flag,
        binary_file_path=binary_file_path.strip(),
        flags=addr2line_flags,
        HexadecimalAddress=Address,
        addr2line_Output_txt=config['toolchains_output_files'][toolchain_name]['addr2line_file_txt']
    )

    print("Constructed addr2line Command:", addr2line_command)  # Debug: Show the command being run

    try:
        # Run the constructed command
        result = subprocess.run(addr2line_command, shell=True, check=True, capture_output=True, text=True)
        print("addr2line command ran successfully!")
        print("Raw output:", result.stdout)  # Debug: Print raw output
        return result.stdout.strip()  # Return the stdout output
    except subprocess.CalledProcessError as e:
        print(f"Command failed with return code {e.returncode}")
        print(f"Error output: {e.stderr}")
        return None

def run_strip_command(toolchain_name, specific_flag_key=None,tool_flag_name='gnu_command_flags'):
    # Retrieve toolchain-specific paths and settings
    toolchain_config = config['toolchains_binary-utilities_filePaths'].get(toolchain_name)
    if not toolchain_config:
        raise ValueError(f"Toolchain '{toolchain_name}' is not defined in the configuration.")

    binary_file_path = toolchain_config['binary_file_path']
    supported_extensions = config.get('supported_extensions', ['.elf', '.out'])

    # Get the file extension of the binary file
    file_extension = os.path.splitext(binary_file_path)[-1].lower()

    # Check if the file extension is supported
    if file_extension not in supported_extensions:
        raise ValueError(
            f"Unsupported binary file extension '{file_extension}'. Supported types: {supported_extensions}")

    # Fetch the objdump command template from the configuration
    strip_command_template = config['gnu_commands']['strip_command']

    # Handle specific flags if provided
    strip_flags_dict = config['toolchains_command_flags'][tool_flag_name]['Strip_flags']
    if specific_flag_key:
        flag_keys = [key.strip() for key in specific_flag_key.split(',')]
        strip_flags = " ".join(strip_flags_dict.get(key, '') for key in flag_keys if key in strip_flags_dict)
    else:
        strip_flags = config.get('default_strip_flags', '--print-size')  # Default flag if none provided

    # Construct the objdump command using the template
    strip_command = strip_command_template.format(
        strip_path=toolchain_config['strip_utility_path'],
        strip_flags=strip_flags,
        binary_file_path=binary_file_path,
        strip_output_flag=config['toolchains_command_flags']['gnu_command_flags']['Strip_flags']['OutputFile'],
        stripped_elf=config['toolchains_output_files'][toolchain_name]['stripped_file_elf']
    )

    print("Constructed strip Command:", strip_command)  # Debug: Show the command being run

    try:
        # Run the constructed command
        result = subprocess.run(strip_command, shell=True, check=True, capture_output=True, text=True)
        print("strip command ran successfully!")
        print("Raw output:", result.stdout)  # Debug: Print raw output
        return result.stdout.strip()  # Return the stdout output
    except subprocess.CalledProcessError as e:
        print(f"Command failed with return code {e.returncode}")
        print(f"Error output: {e.stderr}")
        return None




if __name__ == "__main__":
    try:
        # To use the "arm_none_eabi" toolchain
        run_objdump_command(toolchain_name="arm_none_eabi")

        # To use the "tricore" toolchain
        run_objdump_command(toolchain_name="tricore")
        run_objdump_command(toolchain_name="ti_cgt_tms470")
        run_objdump_command(toolchain_name="ti_cgt_armllvm")


        run_nm_command(toolchain_name="arm_none_eabi", specific_flag_key='defined_only, print_size')
        run_nm_command(toolchain_name="tricore", specific_flag_key='defined_only, print_size')
        run_nm_command(toolchain_name="ti-cgt-msp430", specific_flag_key='defined_only, print_size')

        run_addr2line_command(toolchain_name="arm_none_eabi", specific_flag_key='DisplayFunctionName', Address='e3e')
        run_addr2line_command(toolchain_name="tricore", specific_flag_key='DisplayFunctionName', Address='800020fa')

        run_strip_command(toolchain_name="arm_none_eabi", specific_flag_key='RemoveDebugging')
        run_strip_command(toolchain_name="tricore", specific_flag_key='RemoveDebugging')


        run_size_command(toolchain_name="arm_none_eabi", specific_flag_key='format,SizeHexaDecimal')
        run_size_command(toolchain_name="tricore", specific_flag_key='format,SizeHexaDecimal')
        run_size_command(toolchain_name="ti_cgt_tms470", specific_flag_key='format,SizeHexaDecimal')
        run_size_command(toolchain_name="ti_cgt_armllvm", specific_flag_key='format,SizeHexaDecimal')


    except Exception as e:
        print("Error loading configurations:", e)
