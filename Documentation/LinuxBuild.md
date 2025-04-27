# Linux Build Guide.

## Dependencies.

=== "Arch Linux Dependencies."

    ```bash
    pacman -S cmake git ninja gcc xorg pkgconf gtk3 vulkan-headers vulkan-validation-layers vulkan-tools xcb-util-cursor python python-pip python-numpy
    ```

=== "Ubuntu Dependencies."

    ```bash
    Not yet added. If you can help, please create a pull request.
    ```

=== "Fedora Dependencies."

    ```bash
    dnf install cmake git ninja-build gcc gcc-c++ libX11-devel libXext-devel libXrandr-devel libXrender-devel libXinerama-devel libXcursor-devel gtk3-devel vulkan-devel vulkan-loader xorg-x11-server-Xwayland xcb-util-cursor-devel xcb-util-wm-devel libxcb-devel xcb-util-keysyms-devel python-numpy python-clang binutils-devel xcb-util-devel openal-devel
    ```

## Building with Ninja.

1. In the root directory of the project, create a build directory.
2. Change the directory to the build directory.
3. ```cmake -G "Ninja" ../ -DCMAKE_BUILD_TYPE=Debug``` where CMAKE_BUILD_TYPE can be changed to "Release".
4. ```cmake --build . -j JOBS``` where JOBS is the number of your logical processors minus 2.
5. Run the executable file in ```REPOSITORY_ROOT/your_build_dir/Engine/```.

### Example.
```
mkdir build
cd build
cmake -G "Ninja" ../ -DCMAKE_BUILD_TYPE=Debug
cmake --build . -j 10
```
#### or a one-liner to build:
```
mkdir build && cd build && cmake -G "Ninja" ../ -DCMAKE_BUILD_TYPE=Debug && cmake --build . -j 10
```
