import wx
import json  # To handle JSON operations
import madonna_main  # Assuming your main processing functions are in this module
import os

# Sample NM flags from your configuration
nm_flags = {
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
        for flag_name, flag_value in nm_flags.items():
            var = wx.CheckBox(self.panel, label=flag_name)
            self.sizer.Add(var, 0, wx.ALL | wx.LEFT, 5)
            self.checkbox_vars[flag_value] = var

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
        config_path = self.config_entry.GetValue()
        map_file_path = self.mapfile_entry.GetValue()

        if not config_path or not map_file_path:
            wx.MessageBox("Please provide both a configuration file and a map file.", "Input Error",
                          wx.OK | wx.ICON_ERROR)
            return

        try:
            # Load the configuration as a dictionary
            config = load_config(config_path)
            madonna_main.parse_map_file(config, map_file_path)  # Pass the loaded dictionary
            wx.MessageBox("Map file parsed successfully!", "Success", wx.OK | wx.ICON_INFORMATION)
        except Exception as e:
            wx.MessageBox(f"Error parsing map file: {e}", "Processing Error", wx.OK | wx.ICON_ERROR)

    def on_parse_nm_output(self, event):
        # Implement your logic for parsing the NM output here
        pass

    def on_save_config(self, event):
        config_path = self.config_entry.GetValue()
        if not config_path:
            wx.MessageBox("Please specify a configuration file to save.", "Input Error", wx.OK | wx.ICON_ERROR)
            return

        try:
            # Load existing configurations
            with open(config_path, 'r') as json_file:
                config_data = json.load(json_file)

            # Update NM flags based on selected checkboxes
            selected_flags = [flag for flag, var in self.checkbox_vars.items() if var.GetValue()]
            config_data["NM_flags"] = {name: value for name, value in nm_flags.items() if value in selected_flags}

            # Save the updated configuration back to the JSON file
            with open(config_path, 'w') as json_file:
                json.dump(config_data, json_file, indent=4)

            wx.MessageBox("Configuration saved successfully!", "Success", wx.OK | wx.ICON_INFORMATION)
        except Exception as e:
            wx.MessageBox(f"Error saving configuration: {e}", "Processing Error", wx.OK | wx.ICON_ERROR)

if __name__ == "__main__":
    app = MyApp()
    app.MainLoop()
