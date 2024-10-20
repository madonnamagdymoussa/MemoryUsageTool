import json
import re
import csv
import subprocess
import os

def load_config(file_path):
    """Load configuration from a JSON file."""
    if not os.path.exists(file_path):
        raise FileNotFoundError(f"Configuration file not found: {file_path}")

    with open(file_path, 'r') as file:
        return json.load(file)

config = load_config('ToolChain_Config.json')

def run_objdump_command(toolchain_name, specific_flag_key=None):
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
    objdump_flags_dict = config['toolchains_command_flags']['gnu_command_flags']['ObjDump_flags']
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


if __name__ == "__main__":
    try:
        # To use the "arm_none_eabi" toolchain
        run_objdump_command(toolchain_name="arm_none_eabi")

        # To use the "tricore" toolchain
        run_objdump_command(toolchain_name="tricore")

    except Exception as e:
        print("Error loading configurations:", e)