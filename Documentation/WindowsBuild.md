# Windows Build Guide.

!!! warning "Requirements"
    > - 0.1. Install Clion 2020.1 or newer / Visual Studio 2019 or newer.
    > - 0.2. Install [Vulkan SDK/Runtime](https://vulkan.lunarg.com/sdk/home) 1.3.211.0 or newer.
    > - 0.3. Install CMake 3.16.0 or newer.
    > - 0.4. Install [MS Build Tools](https://download.visualstudio.microsoft.com/download/pr/996d318f-4bd0-4f73-8554-ea3ed556ce9b/9610a60ad452c33dd3f9e8d3b4ce5d88d278f8b063d88717e08e1c0c13c29233/vs_BuildTools.exe) for Visual Studio 16.11.29 or newer (if you are using CLion).
    > - 0.5. Make sure you have Python 3 installed and added to environment variables.

!!! warning "vcpkg"
    If you use Visual Studio, make sure you don't have vcpkg with zlib installed. 
    It can cause undefined behavior. 
    If you have it, uninstall it or remove zlib from vcpkg.
    Use "vcpkg list | findstr zlib" to check if you have it.

===  "Working with CMake GUI (Visual Studio)"

    - 1. Open CMake GUI.
  
    - 2. Choose the path to the SREngine folder (where the source code is located).
  
    - 3. Choose the path where to build the binaries (ex. SREngine/build).
     
    - 4. Press "Configure" and choose your VS version.
    
    - 5. Press `Generate`.

    - 6. Open Visual Studio solution.

    - 7. In Visual Studio right-click on SREngine and press `Set as Startup Project`.

    - 8. Run build.

=== "Working with CMake in CMD (Visual Studio)"

    - 1. Open CMD in root directory of the repository and run the following commands:
  
    - 2. mkdir build

    - 3. cd build
  
    - 4. ```cmake -G "VISUAL_STUDIO_VERSION" ../ -DCMAKE_BUILD_TYPE=Debug```

        * Replace `VISUAL_STUDIO_VERSION` with your version ex. `Visual Studio 17 2022` 
     
    - 5. Now you have your solution generated and you can open it with Visual Studio
    
    - 6. In Visual Studio right-click on SREngine and press `Set as Startup Project`

    - 7. Build and Run the game engine!

=== "Working with CLion"

    - 1. Press Ctrl + Alt + S to open Settings window.
    
    - 2. Select `Build, Execution, Deployment` on the left.
    
    - 3. Select `Toolchains`.
    
    - 4. Add (Alt + Insert) Visual Studio compiler.
    
    - 5. Select `amd64` in `Architecture:`.
    
    - 6. Repeat "2"
    
    - 7. Select `CMake`.
    
    - 8. Pass `-j n` argument as `Build options`, where `n` is a number of your logical processors minus 2.
    
    - 9. In Project window right-click `SREngine` folder and click `Reload CMake Project`.
    
    - 10. Click `Run 'SREngine'` (Shift + F10).

<img width="1920" alt="screenshot" src="https://github.com/SpaRcle-Studio/SREngine/blob/dev/Documentation/images/clion%20toolchains.png">
