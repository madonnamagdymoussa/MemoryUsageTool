from typing import List, Any

import wx
import json  # To handle JSON operations
import madonna_main  # Assuming your main processing functions are in this module
import os
import tempfile  # To create temporary files


def load_config(file_path):
    """Load configuration from a JSON file."""
    if not os.path.exists(file_path):
        raise FileNotFoundError(f"Configuration file not found: {file_path}")

    with open(file_path, 'r') as file:
        return json.load(file)


class MyApp(wx.App):
    def OnInit(self):
        self.frame = MyFrame()
        self.frame.Show()
        return True


class MyFrame(wx.Frame):
    def __init__(self):
        super().__init__(parent=None, title="Madonna Memory Usage Tool")
        self.panel = wx.Panel(self)
        self.sizer = wx.BoxSizer(wx.VERTICAL)

        # Configuration file input
        self.config_label = wx.StaticText(self.panel, label="Configuration File:")
        self.sizer.Add(self.config_label, 0, wx.ALL | wx.CENTER, 5)
        self.config_entry = wx.TextCtrl(self.panel, size=(400, -1))
        self.sizer.Add(self.config_entry, 0, wx.ALL | wx.CENTER, 5)
        self.config_button = wx.Button(self.panel, label="Browse Config")
        self.config_button.Bind(wx.EVT_BUTTON, self.on_browse_config)
        self.sizer.Add(self.config_button, 0, wx.ALL | wx.CENTER, 5)

        # Map file input
        self.mapfile_label = wx.StaticText(self.panel, label="Map File:")
        self.sizer.Add(self.mapfile_label, 0, wx.ALL | wx.CENTER, 5)
        self.mapfile_entry = wx.TextCtrl(self.panel, size=(400, -1))
        self.sizer.Add(self.mapfile_entry, 0, wx.ALL | wx.CENTER, 5)
        self.mapfile_button = wx.Button(self.panel, label="Browse Map File")
        self.mapfile_button.Bind(wx.EVT_BUTTON, self.on_browse_map_file)
        self.sizer.Add(self.mapfile_button, 0, wx.ALL | wx.CENTER, 5)

        # NM flags checkboxes
        self.checkbox_vars = {}
        self.load_nm_flags()  # Load NM flags from the configuration

        # Buttons for processing
        self.run_nm_button = wx.Button(self.panel, label="Run NM Command")
        self.run_nm_button.Bind(wx.EVT_BUTTON, self.on_run_nm_command)
        self.sizer.Add(self.run_nm_button, 0, wx.ALL | wx.CENTER, 5)

        self.parse_map_button = wx.Button(self.panel, label="Parse Map File")
        self.parse_map_button.Bind(wx.EVT_BUTTON, self.on_parse_map_file)
        self.sizer.Add(self.parse_map_button, 0, wx.ALL | wx.CENTER, 5)

        self.parse_nm_output_button = wx.Button(self.panel, label="Parse NM Output")
        self.parse_nm_output_button.Bind(wx.EVT_BUTTON, self.on_parse_nm_output)
        self.sizer.Add(self.parse_nm_output_button, 0, wx.ALL | wx.CENTER, 5)

        self.save_config_button = wx.Button(self.panel, label="Save Configuration")
        self.save_config_button.Bind(wx.EVT_BUTTON, self.on_save_config)
        self.sizer.Add(self.save_config_button, 0, wx.ALL | wx.CENTER, 5)

        self.panel.SetSizer(self.sizer)
        self.SetSize((500, 400))

    def load_nm_flags(self):
        """Load NM flags from configuration or set defaults if not present."""
        self.nm_flags = {
            "all_symbols": "-a",
            "global_symbols": "-g",
            "source_info": "-l",
            "undefined_symbols": "-u",
            "sort_by_address": "-n",
            "reverse_sort": "-r",
            "display_size": "-S",
            "no_sort": "-p",
            "only_names": "-j",
            "specific_section": "-s",
            "demangle": "--demangle",
            "size_sort": "--size-sort",
            "demangle_equivalent": "-C",
            "defined_only": "--defined-only",
            "print_size": "--print-size"
        }

        # Create checkboxes for NM flags
        for flag_name, flag_value in self.nm_flags.items():
            var = wx.CheckBox(self.panel, label=flag_name)
            self.sizer.Add(var, 0, wx.ALL | wx.LEFT, 5)
            self.checkbox_vars[flag_value] = var

    def on_browse_config(self, event):
        with wx.FileDialog(self, "Select Configuration File", wildcard="JSON files (*.json)|*.json|All files (*.*)|*.*",
                           style=wx.FD_OPEN | wx.FD_FILE_MUST_EXIST) as file_dialog:
            if file_dialog.ShowModal() == wx.ID_OK:
                config_path = file_dialog.GetPath()
                self.config_entry.SetValue(config_path)

    def on_browse_map_file(self, event):
        with wx.FileDialog(self, "Select Map File", wildcard="Map files (*.map)|*.map|All files (*.*)|*.*",
                           style=wx.FD_OPEN | wx.FD_FILE_MUST_EXIST) as file_dialog:
            if file_dialog.ShowModal() == wx.ID_OK:
                map_file_path = file_dialog.GetPath()
                self.mapfile_entry.SetValue(map_file_path)

    def on_parse_map_file(self, event):
        config_path = self.config_entry.GetValue()  # Get the config file path as a string --> JSON file path
        map_file_path = self.mapfile_entry.GetValue()  # Get the map file path as a string

        if not config_path or not map_file_path:
            wx.MessageBox("Please provide both a configuration file and a map file.", "Input Error",
                          wx.OK | wx.ICON_ERROR)
            return

        try:
            # Load the configuration as a dictionary
            #config = load_config(config_path)  # This function returns the config dictionary

            # Now pass the correct map file path (string) and config (dict) to parse_map_file
            entries = madonna_main.parse_map_file(map_file_path,
                                                             madonna_main.Compiled_Regex_Patterns_Dict)  # Ensure correct order of arguments
            my_parsed_mapfile_csv = madonna_main.csv_files_Dict['map_file_parsing_csv']
            madonna_main.write_entries_to_csv(entries, my_parsed_mapfile_csv)
            wx.MessageBox("Map file parsed successfully!", "Success", wx.OK | wx.ICON_INFORMATION)
        except Exception as e:
            wx.MessageBox(f"Error parsing map file: {e}", "Processing Error", wx.OK | wx.ICON_ERROR)

    def on_run_nm_command(self, event):
        try:
            # Load the configuration from the JSON file
            config_path = self.config_entry.GetValue()
            if not os.path.exists(config_path):
                wx.MessageBox("Configuration file not found. Please provide a valid configuration file.", "Input Error",
                              wx.OK | wx.ICON_ERROR)
                return

            with open(config_path, 'r') as json_file:
                config_data = json.load(json_file)

            # Get the selected NM flags from the JSON file
            selected_keys = config_data.get("NM_flags", {}).keys()

            if not selected_keys:
                wx.MessageBox("No NM flags are selected in the configuration file.", "Warning",
                              wx.OK | wx.ICON_WARNING)
                return

            # Join the selected keys to display them
            keys_string = ', '.join(selected_keys)
            print(f"Selected flag keys from JSON: {keys_string}")

            # Run the NM command with the selected flag keys
            madonna_main.run_nm_command(specific_flag_key=keys_string)

            # Read the content from the nm_Objects.txt file after running the command
            nm_objects_txt_path = madonna_main.csv_files_Dict['nm_objects_file']
            with open(nm_objects_txt_path, 'r') as nm_temp_file:
                nm_output = nm_temp_file.read()
                print("NM Command Output:")
                print(nm_output)

                # Parse the NM output
                self.on_parse_nm_output(nm_output)

        except Exception as e:
            wx.MessageBox(f"An error occurred while running the NM command: {e}", "Error", wx.OK | wx.ICON_ERROR)

    def on_parse_nm_output(self, nm_output):
        # Debug: Print the type of nm_output
        #print(f"Type of nm_output: {type(nm_output)}")

        '''
        # Check if nm_output is indeed a string
        if not isinstance(nm_output, str):
            wx.MessageBox("NM output is not in the expected string format.", "Error", wx.OK | wx.ICON_ERROR)
            return

        # Debug: Print out the nm_output content
        print(f"NM output content: {nm_output}")

        # Use a temporary file to store the NM command output
        with tempfile.NamedTemporaryFile(delete=False, mode='w', suffix='.txt') as nm_temp_file:
            nm_temp_file.write(nm_output)  # Write the string output to the temp file
            nm_objects_txt = nm_temp_file.name  # Get the path of the temp file

        # Define the CSV output path (you can ask the user to provide it via GUI)
        csv_output_path = os.path.join(os.getcwd(), "parsed_nm_output.csv")  # Example path to save CSV
        '''
        try:
            # Call the madonna_main function to process the NM output and save it to the CSV
            madonna_main.parse_nm_output(madonna_main.csv_files_Dict['nm_objects_file'], madonna_main.csv_files_Dict['elf_objects_file'])
            wx.MessageBox(f"NM output parsed successfully and saved to {madonna_main.csv_files_Dict['elf_objects_file']}.", "Success",
                          wx.OK | wx.ICON_INFORMATION)
        except Exception as e:
            wx.MessageBox(f"Error parsing NM output: {e}", "Processing Error", wx.OK | wx.ICON_ERROR)
        #finally:
            # Clean up the temporary file
            #if os.path.exists(nm_objects_txt):
                #os.remove(nm_objects_txt)

    def on_save_config(self, event):
        config_path = self.config_entry.GetValue()
        if not config_path:
            wx.MessageBox("Please specify a configuration file to save.", "Input Error", wx.OK | wx.ICON_ERROR)
            return

        try:
            # Load the existing configuration
            if os.path.exists(config_path):
                with open(config_path, 'r') as json_file:
                    config_data = json.load(json_file)
            else:
                config_data = {}  # Create a new config data if the file does not exist

            # Update configurations
            config_data["map_path"] = self.mapfile_entry.GetValue()
            config_data["NM_flags"] = {name: value for name, value in self.nm_flags.items() if
                                       value in self.checkbox_vars and self.checkbox_vars[value].GetValue()}

            # Save the updated configuration back to the JSON file
            with open(config_path, 'w') as json_file:
                json.dump(config_data, json_file, indent=4)

            wx.MessageBox("Configuration saved successfully!", "Success", wx.OK | wx.ICON_INFORMATION)
        except Exception as e:
            wx.MessageBox(f"Error saving configuration: {e}", "Processing Error", wx.OK | wx.ICON_ERROR)


if __name__ == "__main__":
    app = MyApp()
    app.MainLoop()
