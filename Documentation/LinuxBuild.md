# Linux Build Guide.

## Cloning repository and installing dependencies.

> [!IMPORTANT]
> 1. ```Clone repository via the command "git clone https://github.com/SpaRcle-Studio/SREngine"```
> 2. ```Switch to the "dev" (or another one) branch via the command "git checkout branch_name"```
> 3. ```Run command "git submodule update --init --recursive" in repository folder```
> 4. ```Install dependencies, see below.```

<details>
<summary>Ubuntu Dependencies.</summary>
    
    Not yet added. If you can help, please create a pull request.
</details>

<details>
<summary>Arch Linux Dependencies.</summary>

    cmake git ninja gcc xorg pkgconf gtk3 vulkan-headers vulkan-validation-layers vulkan-tools xcb-util-cursor python python-pip python-numpy
</details>

## Building with Ninja.

1. In the root directory of the project, create a build directory.
2. Change the directory to the build directory.
3. ```cmake -G "Ninja" ../ -DCMAKE_BUILD_TYPE=Debug``` where CMAKE_BUILD_TYPE can be changed to "Release".
4. ```cmake --build . -j JOBS``` where JOBS is the number of your logical processors minus 2.
5. Run the executable file in ```REPOSITORY_ROOT/your_build_dir/Engine/```.

### Example.
```
git clone https://github.com/SpaRcle-Studio/SREngine
cd SREngine
git checkout dev
git submodule update --init --recursive
mkdir build
cd build
cmake -G "Ninja" ../ -DCMAKE_BUILD_TYPE=Debug
cmake --build . -j 10
```
#### or a one-liner to build:
```
mkdir build && cd build && cmake -G "Ninja" ../ -DCMAKE_BUILD_TYPE=Debug && cmake --build . -j 10
```
