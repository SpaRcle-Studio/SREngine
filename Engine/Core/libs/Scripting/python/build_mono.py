import argparse
import os
import subprocess
import threading
import sys
import winreg
import glob

log_prefix = "[MonoBuild]"

def create_log_file(log_file):
    print(f'{log_prefix} Create log file to: {log_file}')
    # delete old log file
    if os.path.exists(log_file):
        os.remove(log_file)
    os.makedirs(os.path.dirname(log_file), exist_ok=True)
    with open(log_file, "w") as log:
        log.write(f'{log_prefix} Log file created.\n')

def log_message(log_file, message, end="\n"):
    with open(log_file, "a") as log:
        log.write(f'{log_prefix} {message}{end}')
    print(f'{log_prefix} {message}{end}', end="")

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

def run_command(log_file, cmd):
    log_message(log_file, f'Run command: "{cmd}"')

    process = subprocess.Popen(
        cmd, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True
    )

    # Создаем потоки для одновременного чтения stdout и stderr
    stdout_thread = threading.Thread(target=stream_output, args=(process.stdout, log_file, '[Command]'))
    stderr_thread = threading.Thread(target=stream_output, args=(process.stderr, log_file, '[Command] [Error]'))

    stdout_thread.start()
    stderr_thread.start()

    # Ждем завершения потоков
    stdout_thread.join()
    stderr_thread.join()

    # Ждем завершения процесса
    process.wait()

    if process.returncode != 0:
        raise Exception(f'Command failed with return code {process.returncode}')


def patch_msbuild(log_file, src_dir):
    log_message(log_file, f'Patch MSBuild...')

    msbuild_dir = find_msbuild(log_file)
    if not msbuild_dir:
        log_message(log_file, f'Error: MSBuild not found.')
        sys.exit(1)
    msbuild_dir = os.path.dirname(msbuild_dir).replace("\\", "/")
    #msbuild_dir = msbuild_dir.replace("\\", "/")

    log_message(log_file, f'MSBuild found: {msbuild_dir}')

    bat_file = f"{src_dir}/msvc/setup-vs-msbuild-env.bat"

    new_content = f"""
@echo off
:: Указываем путь к msbuild
set "MSBUILD_PATH={msbuild_dir}"

:: Добавляем в PATH (если нужно)
set "PATH=%MSBUILD_PATH%;%PATH%"

:: Проверяем, что msbuild.exe доступен
where msbuild.exe >nul 2>nul
if %ERRORLEVEL% neq 0 (
    echo Error: msbuild.exe not found in PATH.
    exit /b 1
)

echo Environment for MSBuild is set up.
exit /b 0
    """

    log_message(log_file, f'New content for {bat_file}:\n{new_content}')

    # Записываем новый файл
    with open(bat_file, "w", encoding="utf-8") as f:
        f.write(new_content)

    log_message(log_file, f'Patch MSBuild: {bat_file} successfully created.')

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
    args = parser.parse_args()

    src_dir = os.path.abspath(args.src).replace("\\", "/")
    build_dir = os.path.abspath(args.build).replace("\\", "/")
    bash_path = os.path.abspath(args.bash).replace("\\", "/")
    python_dir = os.path.abspath(args.python).replace("\\", "/")
    venv_dir = os.path.abspath(args.venv).replace("\\", "/")
    target_lib = os.path.abspath(args.library).replace("\\", "/")

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

    #patch_msbuild(log_file, src_dir)
    patch_msvc_compile_script(log_file, src_dir)

    # Проверяем наличие configure
    configure_path = os.path.join(src_dir, "configure")
    if not os.path.exists(configure_path):
        log_message(log_file, f'Run autogen.sh...')
        #run_command(log_file, f'\"{bash_path}\" --login -c \"cd {src_dir} && ./autogen.sh\"')
        run_command(log_file, f'\"{bash_path}\" --login -c \"cd {src_dir} && ./autogen.sh --prefix={build_dir} --host=x86_64-w64-mingw32 --enable-msvc --disable-boehm PYTHON={python_dir}\"')
    else:
        log_message(log_file, f'Configure found, skipping autogen.sh')

    #log_message(log_file, f'Getting latest monolite...')
    #run_command(log_file, f'\"{bash_path}\" --login -c \"cd {src_dir} && make get-monolite-latest\"')

    #monolite = src_dir + '/mcs/class/lib/monolite-win32/1A5E0066-58DC-428A-B21C-0AD6CDAE2789/mcs.exe'

    #log_message(log_file, f'Give execute permissions to monolite: {monolite}')
    #run_command(log_file, f'\"{bash_path}\" --login -c \"chmod +x {monolite}\"')

    # Определяем, нужна ли конвертация в Cygwin-путь
    if os.name == "nt":
        drive, path = os.path.splitdrive(venv_dir)
        drive = drive.lower().replace(":", "")  # Приводим букву диска к нижнему регистру
        mono_bin_executable = f"/cygdrive/{drive}{path.replace('\\', '/')}/MonoPrebuild/bin"
    else:
        mono_bin_executable = os.path.join(venv_dir, "MonoPrebuild", "bin")

    #mono_relative_path = os.path.relpath(venv_dir, src_dir)
    #mono_bin = os.path.join("..", mono_relative_path, "MonoPrebuild", "bin")
    #mono_bin = mono_bin.replace("\\", "/")

    #mono_bin = '../../../.venv/MonoPrebuild/bin'

    log_message(log_file, f'Mono bin executable: {mono_bin_executable}')

    # Запускаем сборку
    #run_command(log_file, f'\"{bash_path}\" --login -c \"cd {src_dir} && make MONO_EXECUTABLE=\"{monolite}\" -j{args.jobs}\" V=1')
    log_message(log_file, 'Building Mono...')
    #run_command(log_file, f'\"{bash_path}\" --login -c \"export PATH={mono_bin}:$PATH && export MONO_EXECUTABLE={mono_bin}/mono && export MONO_PATH={mono_bin} && cd {src_dir} && make -j{args.jobs}\" V=1')
    #run_command(log_file, f'\"{bash_path}\" --login -c \"export PATH={mono_bin}:$PATH && export MONO_EXECUTABLE={mono_bin}/mono && export MONO_PATH={mono_bin} && echo $MONO_PATH && cd {src_dir} && make -j{args.jobs}\" V=1')
    #run_command(log_file, f'\"{bash_path}\" --login -c \"export PATH={msbuild_dir}:$PATH && export PATH={mono_bin}:$PATH && export MONO_EXECUTABLE={mono_bin}/mono && export MONO_PATH={mono_bin} && echo $MONO_PATH && cd {src_dir} && make -j{args.jobs}\" V=1')
    #run_command(log_file, f'\"{bash_path}\" --login -c \"export PATH=\\\"{mono_bin}:$PATH\\\" && export MONO_EXECUTABLE=\\\"{mono_bin}/mono\\\" && export MONO_PATH=\\\"{mono_bin}\\\" && echo \\\"$MONO_PATH\\\" && cd \\\"{src_dir}\\\" && make -j{args.jobs}\" V=1')
    #run_command(log_file, f'\"{bash_path}\" --login -c \"export PATH=\\\"{mono_bin}:$PATH\\\" && export MONO_EXECUTABLE=\\\"{mono_bin_executable}/mono\\\" && export MONO_PATH=\\\"{mono_bin}\\\" && cd \\\"{src_dir}\\\" && make -j{args.jobs}\" V=1')
    run_command(log_file, f'\"{bash_path}\" --login -c \"export PATH=\\\"{mono_bin_executable}:$PATH\\\" && export MONO_EXECUTABLE=\\\"{mono_bin_executable}/mono\\\" && cd \\\"{src_dir}\\\" && make -j{args.jobs}\" V=1')
    #run_command(log_file, f'\"{bash_path}\" --login -c \"cd \\\"{src_dir}\\\" && make -j{args.jobs}\" V=1')

    #command = f'"{bash_path}" --login -c "export PATH={msbuild_dir}:$PATH; export PATH={mono_bin}:$PATH; export MONO_EXECUTABLE={mono_bin}/mono; export MONO_PATH={mono_bin}; echo \\"MSBuild: $(which msbuild)\\"; echo \\"MONO_PATH: $MONO_PATH\\"; cd {src_dir} && make -j{args.jobs}"'
    #run_command(log_file, command)

    # Устанавливаем
    #log_message(log_file, 'Making install...')
    #run_command(log_file, f'\"{bash_path}\" --login -c \"cd {src_dir} && make install\"')

    log_message(log_file, 'Mono build script finished.')

if __name__ == "__main__":
    main()