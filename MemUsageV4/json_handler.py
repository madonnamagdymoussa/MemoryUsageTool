import json
import os

def load_config(file_path):
    """Load configuration from a JSON file."""
    if not os.path.exists(file_path):
        raise FileNotFoundError(f"Configuration file not found: {file_path}")

    with open(file_path, 'r') as file:
        return json.load(file)

# Save the updated JSON data back to the file
def save_config(file_path, data):
    with open(file_path, 'w') as file:
        json.dump(data, file, indent=4)