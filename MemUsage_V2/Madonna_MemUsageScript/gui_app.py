import wx
import json  # To handle JSON operations
import madonna_main  # Assuming your main processing functions are in this module
import os

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

    def on_run_nm_command(self, event):
        selected_flags = [flag for flag, var in self.checkbox_vars.items() if var.GetValue()]
        nm_command = f"nm {' '.join(selected_flags)}"
        print(f"NM Command: {nm_command}")
        # You may want to execute the command here and handle the output



    def on_parse_map_file(self, event):
      config_path = self.config_entry.GetValue()  # Get the config file path as a string
      map_file_path = self.mapfile_entry.GetValue()  # Get the map file path as a string

      if not config_path or not map_file_path:
        wx.MessageBox("Please provide both a configuration file and a map file.", "Input Error",
                      wx.OK | wx.ICON_ERROR)
        return

      try:
        # Load the configuration as a dictionary
        config = load_config(config_path)  # This function returns the config dictionary

        # Now pass the correct map file path (string) and config (dict) to parse_map_file
        madonna_main.parse_map_file(map_file_path, config)  # Ensure correct order of arguments
        wx.MessageBox("Map file parsed successfully!", "Success", wx.OK | wx.ICON_INFORMATION)
      except Exception as e:
         wx.MessageBox(f"Error parsing map file: {e}", "Processing Error", wx.OK | wx.ICON_ERROR)

    def on_run_nm_command(self, event):
        selected_flags = [flag for flag, var in self.checkbox_vars.items() if var.GetValue()]
        flags_string = ','.join(selected_flags)

        # Call the function to execute the nm command
        output = madonna_main.run_nm_command(flags_string)  # Ensure the flags string is passed

        if output:  # Check if output is not None or empty
            print("NM Command Output:")
            print(output)
            # Call the parse function to handle the NM output
            self.on_parse_nm_output(output)  # Pass the output to the parser
        else:
            print("Failed to run nm command.")

    def on_parse_nm_output(self, nm_output):
        # Ensure nm_output is a string and not an event
        if isinstance(nm_output, str):
            lines = nm_output.strip().split('\n')
        else:
            print("Invalid output received.")
            return

        parsed_data = []

        for line in lines:
            # Example parsing logic (you can adjust based on NM output format)
            parts = line.split()
            if len(parts) >= 3:
                address = parts[0]
                size = parts[1]
                name = ' '.join(parts[2:])  # Join the remaining parts for the name
                parsed_data.append({'address': address, 'size': size, 'name': name})

        # Now you can use parsed_data for display or further processing
        for entry in parsed_data:
            print(f"Address: {entry['address']}, Size: {entry['size']}, Name: {entry['name']}")
            # If you want to display in GUI, uncomment below lines:
            # self.output_text.AppendText(f"Address: {entry['address']}, Size: {entry['size']}, Name: {entry['name']}\n")

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
            config_data["NM_flags"] = {name: value for name, value in self.nm_flags.items() if value in self.checkbox_vars and self.checkbox_vars[value].GetValue()}

            # Save the updated configuration back to the JSON file
            with open(config_path, 'w') as json_file:
                json.dump(config_data, json_file, indent=4)

            wx.MessageBox("Configuration saved successfully!", "Success", wx.OK | wx.ICON_INFORMATION)
        except Exception as e:
            wx.MessageBox(f"Error saving configuration: {e}", "Processing Error", wx.OK | wx.ICON_ERROR)


if __name__ == "__main__":
    app = MyApp()
    app.MainLoop()
