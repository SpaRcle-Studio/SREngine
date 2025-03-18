import argparse
import os
import subprocess
import threading
import sys
import winreg
import glob

sys.stdout.reconfigure(encoding='utf-8')

log_prefix = "[MonoBuild]"

def create_log_file(log_file):
    print(f'{log_prefix} Create log file to: {log_file}')
    # delete old log file
    if os.path.exists(log_file):
        os.remove(log_file)
    os.makedirs(os.path.dirname(log_file), exist_ok=True)
    with open(log_file, "w", encoding="utf-8") as log:
        log.write(f'{log_prefix} Log file created.\n')

def log_message(log_file, message, end="\n"):
    with open(log_file, "a", encoding="utf-8") as log:
        log.write(f'{log_prefix} {message}{end}')
    #print(f'{log_prefix} {message}{end}', end="")

def find_msbuild(log_file):
    """Ищет msbuild.exe в системе."""

    # 1. Поиск через стандартные пути
    possible_roots = [
        "C:/Program Files/Microsoft Visual Studio",
        "C:/Program Files (x86)/Microsoft Visual Studio"
    ]

    log_message(log_file, f'Looking for MSBuild in: {possible_roots}')

    for root in possible_roots:
        for msbuild_path in glob.glob(f"{root}/*/*/MSBuild/*/Bin/msbuild.exe"):
            if os.path.exists(msbuild_path):
                return msbuild_path

    log_message(log_file, f'MSBuild not found in standard paths. Trying registry...')

    # 2. Поиск через реестр (работает даже если VS установлена в нестандартный путь)
    try:
        with winreg.OpenKey(winreg.HKEY_LOCAL_MACHINE, r"SOFTWARE\Microsoft\MSBuild\ToolsVersions", 0, winreg.KEY_READ | winreg.KEY_WOW64_64KEY) as key:
            index = 0
            while True:
                version = winreg.EnumKey(key, index)
                try:
                    with winreg.OpenKey(key, version) as subkey:
                        msbuild_path, _ = winreg.QueryValueEx(subkey, "MSBuildToolsPath")
                        msbuild_exe = os.path.join(msbuild_path, "msbuild.exe")
                        if os.path.exists(msbuild_exe):
                            return msbuild_exe
                except FileNotFoundError:
                    pass
                index += 1
    except FileNotFoundError:
        pass

    log_message(log_file, f'MSBuild not found in registry. Trying to find it in all drives...')

    # 3. Обход всех доступных дисков в системе (самый медленный, но надёжный способ)
    available_drives = [f"{d}:\\" for d in string.ascii_uppercase if os.path.exists(f"{d}:\\")]

    for drive in available_drives:
        try:
            output = subprocess.check_output(
                f'where /R {drive} msbuild.exe',
                shell=True,
                text=True,
                errors='ignore'
            ).strip()
            paths = output.split("\n")
            for path in paths:
                path = path.strip()
                if path and os.path.exists(path):
                    return path
        except subprocess.SubprocessError:
            pass

    log_message(log_file, f'MSBuild not found in all drives.')

    return None


def stream_output(pipe, log_file, prefix):
    """Поток для логирования вывода"""
    for line in iter(pipe.readline, ''):
        log_message(log_file, f'{prefix} {line}', end="")
    pipe.close()

def run_command(log_file, prefix, cmd):
    log_message(log_file, f'[{prefix}] Run command: "{cmd}"')

    process = subprocess.Popen(
        cmd, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True
    )

    # Создаем потоки для одновременного чтения stdout и stderr
    stdout_thread = threading.Thread(target=stream_output, args=(process.stdout, log_file, f'[{prefix}] [Command]'))
    stderr_thread = threading.Thread(target=stream_output, args=(process.stderr, log_file, f'[{prefix}] [Command] [Error]'))

    stdout_thread.start()
    stderr_thread.start()

    # Ждем завершения потоков
    stdout_thread.join()
    stderr_thread.join()

    # Ждем завершения процесса
    process.wait()

    if process.returncode != 0:
        raise Exception(f'[{prefix}] Command failed with return code {process.returncode}')


def patch_msvc_compile_script(log_file, src_dir):
    log_message(log_file, f'Patch MSVC compile script...')

    msbuild_dir = find_msbuild(log_file)
    if not msbuild_dir:
        log_message(log_file, f'Error: MSBuild not found.')
        sys.exit(1)
    msbuild_dir = msbuild_dir.replace("\\", "/")

    log_message(log_file, f'MSBuild found: {msbuild_dir}')

    bat_file = f"{src_dir}/msvc/run-msbuild.bat"

    new_content = f"""
@echo off
setlocal

set BUILD_RESULT=1

:: Get path for current running script.
set RUN_MSBUILD_SCRIPT_PATH=%~dp0

:: Configure all known build arguments.
set VS_TARGET=build
if /i "%~1" == "clean" (
    set VS_TARGET="clean"
)
shift

set VS_PLATFORM=x64
if /i "%~1" == "i686" (
    set VS_PLATFORM="Win32"
)
if /i "%~1" == "win32" (
    set VS_PLATFORM="Win32"
)
shift

set VS_CONFIGURATION=Release
if /i "%~1" == "debug" (
    set VS_CONFIGURATION="Debug"
)
shift

set VS_TARGET_GC=sgen
if /i "%~1" == "boehm" (
    set VS_TARGET_GC="boehm"
)
shift

set VS_ADDITIONAL_ARGUMENTS=
if not "%~1" == "" (
    set VS_ADDITIONAL_ARGUMENTS=%~1
)
shift

set VS_BUILD_PROJ=mono.sln
if /i not "%~1" == "" (
    set VS_BUILD_PROJ=%~1
)

if not exist %VS_BUILD_PROJ% (
    set VS_BUILD_PROJ=%RUN_MSBUILD_SCRIPT_PATH%%VS_BUILD_PROJ%
)

set VS_BUILD_ARGS=/p:Configuration=%VS_CONFIGURATION% /p:Platform=%VS_PLATFORM% /m /p:MONO_TARGET_GC=%VS_TARGET_GC% %VS_ADDITIONAL_ARGUMENTS% /t:%VS_TARGET% /nologo /fl /v:diag /p:SkipInvalidConfigurations=true /p:ContinueOnError=true /t:build

:: Выводим аргументы для отладки
echo Running: {msbuild_dir} %VS_BUILD_ARGS% "%VS_BUILD_PROJ%"

:: Принудительно отключаем интерактивный режим, убираем /m
cmd.exe /C "{msbuild_dir} %VS_BUILD_ARGS% "%VS_BUILD_PROJ%"" < NUL && (
    set BUILD_RESULT=0
) || (
    set BUILD_RESULT=%ERRORLEVEL%
)

exit /b %BUILD_RESULT%
    """

    log_message(log_file, f'New content for {bat_file}:\n{new_content}')

    # Записываем новый файл
    with open(bat_file, "w", encoding="utf-8") as f:
        f.write(new_content)

    log_message(log_file, f'Patch MSVC: {bat_file} successfully created.')

def main():
    parser = argparse.ArgumentParser(description="Сборка Mono")
    parser.add_argument("--src", required=True, help="Путь к исходникам Mono")
    parser.add_argument("--build", required=True, help="Путь к директории сборки")
    parser.add_argument("--jobs", default="4", help="Количество потоков для make")
    parser.add_argument("--bash", required=True, help="Bash shell")
    parser.add_argument("--python", required=True, help="Python interpreter")
    parser.add_argument("--venv", required=True, help="Virtual environment directory")
    parser.add_argument("--library", required=True, help="Target library file")
    parser.add_argument("--platform", required=True, help="Target platform (Windows, Linux, Android, etc.)")
    args = parser.parse_args()

    src_dir = os.path.abspath(args.src).replace("\\", "/")
    build_dir = os.path.abspath(args.build).replace("\\", "/")
    bash_path = os.path.abspath(args.bash).replace("\\", "/")
    python_dir = os.path.abspath(args.python).replace("\\", "/")
    venv_dir = os.path.abspath(args.venv).replace("\\", "/")
    target_lib = os.path.abspath(args.library).replace("\\", "/")
    platform = args.platform

    log_file = os.path.join(build_dir, 'build_mono_python.log')

    create_log_file(log_file)

    log_message(log_file, f'Running mono build script...')

    if os.path.exists(target_lib):
        log_message(log_file, f'Target library already exists: {target_lib}')
        log_message(log_file, f'Build skipped.')
        sys.exit(0)

    log_message(log_file, f'Source directory: {src_dir}')
    log_message(log_file, f'Build directory: {build_dir}')
    log_message(log_file, f'Bash path: {bash_path}')
    log_message(log_file, f'Python path: {python_dir}')

    patch_msvc_compile_script(log_file, src_dir)

    #sdk_path = 'Work/SREngine/Android/android-sdk/ndk'
    #ndk_path = 'C:/Work/SREngine/Android/android-sdk/ndk/29.0.13113456'
    ndk_path = '/cygdrive/c/Work/SREngine/Android/android-sdk/ndk/29.0.13113456'

    # Проверяем наличие configure
    configure_path = os.path.join(src_dir, "configure")
    #if not os.path.exists(configure_path) or True:
    if not os.path.exists(configure_path):
        log_message(log_file, f'Run autogen.sh...')

        additional_args = ''

        if platform == 'Windows':
            additional_args = '--host=x86_64-w64-mingw32 --enable-msvc'
        elif platform == 'Linux':
            additional_args = '--enable-static --disable-shared'
        elif platform == 'Android':
            #additional_args = '--host=aarch64-linux-android'
            additional_args = f'--host=aarch64-linux-android --with-btls-android-ndk={ndk_path} CC={ndk_path}/toolchains/llvm/prebuilt/windows-x86_64/bin/aarch64-linux-android21-clang CXX={ndk_path}/toolchains/llvm/prebuilt/windows-x86_64/bin/aarch64-linux-android21-clang++'

        #run_command(log_file, 'Autogen', f'\"{bash_path}\" --login -c \"cd {src_dir} && export ANDROID_TOOLCHAIN_NAME={ndk_path}/build/core/toolchains/arm-linux-androideabi-clang && ./autogen.sh --prefix={build_dir} {additional_args} --disable-boehm PYTHON={python_dir}\"')
        run_command(log_file, 'Autogen', f'\"{bash_path}\" --login -c \"cd {src_dir} && ./autogen.sh --prefix={build_dir} {additional_args} --disable-boehm PYTHON={python_dir}\"')
    else:
        log_message(log_file, f'Configure found, skipping autogen.sh')

    # Запускаем сборку
    log_message(log_file, 'Building Mono...')

    if platform == 'Windows' or platform == 'Android':
        drive, path = os.path.splitdrive(venv_dir)
        drive = drive.lower().replace(":", "")  # Приводим букву диска к нижнему регистру
        mono_bin_executable = f"/cygdrive/{drive}{path.replace('\\', '/')}/MonoBuildTool/bin"

        log_message(log_file, f'Mono bin executable: {mono_bin_executable}')

        if platform == 'Android':
            #make_path = ndk_path + '/toolchains/llvm/prebuilt/windows-x86_64/bin/make.exe'
            #run_command(log_file, 'Make', f'SET ANDROID_NDK={ndk_path} && \"{make_path}\"')

            command_args = f'export ANDROID_NDK={ndk_path}'
            command_args += ' && export ANDROID_NDK_ROOT="$ANDROID_NDK"'
            command_args += ' && export ANDROID_NDK_TOOLCHAIN="$ANDROID_NDK/toolchains/llvm/prebuilt/windows-x86_64"'
            command_args += ' && export PATH="$ANDROID_NDK_TOOLCHAIN/bin:$PATH"'
            #command_args += ' && which aarch64-linux-android21-clang'
            #command_args += ' && echo $ANDROID_NDK_TOOLCHAIN'
            #command_args += ' && ls -l $ANDROID_NDK_TOOLCHAIN/bin'
            command_args += f' && export ANDROID_NDK_TOOLCHAINS_PATH="{ndk_path}/toolchains"'

            run_command(log_file, 'Make', f'\"{bash_path}\" --login -c \"{command_args} && cd \\\"{src_dir}\\\" && make -j{args.jobs}\" V=1')
        else:
            run_command(log_file, 'Make', f'\"{bash_path}\" --login -c \"export PATH=\\\"{mono_bin_executable}:$PATH\\\" && export MONO_EXECUTABLE=\\\"{mono_bin_executable}/mono\\\" && cd \\\"{src_dir}\\\" && make -j{args.jobs}\" V=1')

        #run_command(log_file, 'Make', f'\"{bash_path}\" --login -c \"export PATH=\\\"{mono_bin_executable}:$PATH\\\" && export MONO_EXECUTABLE=\\\"{mono_bin_executable}/mono\\\" && export ANDROID_NDK=\\\"C:/{ndk_path}\\\" && export CMAKE_TOOLCHAIN_FILE=\\\"$ANDROID_NDK/build/cmake/android.toolchain.cmake\\\" && export CMAKE_C_COMPILER=\\\"$ANDROID_NDK/toolchains/llvm/prebuilt/windows-x86_64/bin/aarch64-linux-android21-clang\\\" && export CMAKE_CXX_COMPILER=\\\"$ANDROID_NDK/toolchains/llvm/prebuilt/windows-x86_64/bin/aarch64-linux-android21-clang++\\\" && cd \\\"{src_dir}\\\" && make -j{args.jobs}\" V=1')
    else:
        run_command(log_file, 'Make', f'\"{bash_path}\" --login -c \"cd \\\"{src_dir}\\\" && make -j{args.jobs}\" V=1')

    log_message(log_file, 'Mono build script finished.')

    # to make install call
    # "C:/Work/SREngine/.venv/cygwin/bin/bash.exe" --login -c "cd "C:\Work\SREngine\.venv\mono" && make install"
    # replace paths to your

if __name__ == "__main__":
    main()