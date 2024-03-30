import os 
import subprocess

if __name__ == '__main__':
    current_directory = os.path.abspath(os.getcwd()) + '/'
    root_directory = os.path.abspath(current_directory + "/../") + '/'
    config_path = current_directory + "embed resources.txt"
    export_path = root_directory + "Engine/Core/libs/Utils/inc/Utils/Resources/"
    script_path = root_directory + "Engine/Core/libs/Utils/inc/Utils/Resources/ResourceEmbedder.py"
    
    if not os.path.exists(config_path) or not os.path.isfile(config_path):
        raise Exception(f"Config file does not exist in current directory: '{config_path}'")
        
    if not os.path.exists(script_path) or not os.path.isfile(script_path):
        script_path_exception = f"Script file does not exist, path: '{script_path}'\n"
        script_path_exception += "Try syncing submodules with: 'git submodule --init --recursive' in engine's root directory."
        raise Exception(script_path_exception)
    
    config_file = open(config_path, "r")
    for line in config_file:
        resource_path = root_directory + '/' + line 
        command = "python " + script_path + ' ' + export_path + ' ' + resource_path
        subprocess.call(command, shell=True)