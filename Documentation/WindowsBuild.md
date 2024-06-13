# Windows Build Guide.
 
> [!IMPORTANT]
> ```Requirements:```
> - 0.1. Install Clion 2020.1 or newer / Visual Studio 2019 or newer
> - 0.2. Install [Vulkan SDK/Runtime](https://vulkan.lunarg.com/sdk/home) 1.3.211.0 or newer
> - 0.3. Install CMake 3.16.0 or newer
> - 0.4. Install [MS Build Tools](https://download.visualstudio.microsoft.com/download/pr/996d318f-4bd0-4f73-8554-ea3ed556ce9b/9610a60ad452c33dd3f9e8d3b4ce5d88d278f8b063d88717e08e1c0c13c29233/vs_BuildTools.exe) for Visual Studio 16.11.29 or newer (if you are using CLion)
1. ```Clone repository via the command "git clone https://github.com/SpaRcle-Studio/SREngine"```
2. ```Switch to the "dev" (or another one) branch via the command "git checkout branch_name"```
3. ```Run command "git submodule update --init --recursive" in repository folder```
 <details>
 <summary> 4. Working with CMake (if you're using Visual Studio): </summary>

    - 4.1 Open CMake GUI
  
    - 4.2 Choose the path to the SREngine folder (where the source code is located).
  
    - 4.3 Choose the path where to build the binaries (SREngine/Build).
     
    - 4.4 Press "Configure" and choose your VS version.
    
    - 4.5 Press "Generate"

    - 4.6 Open Visual Studio solution

    - 4.7 Set as startap project SREngine 

    - 4.8 Run build 

 </details>
 <details>
 <summary> 5. Working with CLion: </summary>

    - 5.1 Press Ctrl + Alt + S to open Settings window
    
    - 5.2. Select "Build, Execution, Deployment" on the left
    
    - 5.3. Select "Toolchains"
    
    - 5.4. Add (Alt + Insert) Visual Studio compiler
    
    - 5.5. Select amd64 in "Architecture:"
    
    - 5.6. Repeat 5.2
    
    - 5.7. Select "CMake"
    
    - 5.8. Pass "-j*" argument as "Build options", while * is a number of your logical processors minus 2
    
    - 5.9. In Project window right-click SREngine folder and click "Reload CMake Project"
    
    - 5.10. Click "Run 'SREngine'" (Shift + F10)
 </details>