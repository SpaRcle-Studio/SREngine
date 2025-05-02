import sys, os, argparse
import clang.cindex
import shutil

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="SpaRcle libclang copy utility")
    parser.add_argument("--repo_dir", required=True, help="Path to the root repo")
    args = parser.parse_args()

    lib_path = os.path.join(os.path.dirname(clang.cindex.__file__), 'native')
    is_unix = sys.platform.startswith('linux') or sys.platform.startswith('darwin')
    lib_file = ''

    prefix = '[SpaRcle libclang copy script]'

    print(f'{prefix} Platform: {sys.platform}')

    if is_unix:
        lib_file = os.path.join(lib_path, 'libclang.so')
    else:
        lib_file = os.path.join(lib_path, 'libclang.dll')

    lib_file = os.path.join(lib_path, lib_file)

    print(f'{prefix} libclang path: {lib_file}')

    if not os.path.isfile(lib_file):
        print(f'{prefix} libclang not found!')
        exit(1)
    else:
        print(f'{prefix} libclang found!')

    target_folder = os.path.join(os.path.abspath(args.repo_dir), 'Resources', 'Engine', 'Utilities')
    target_file = os.path.join(target_folder, os.path.basename(lib_file))

    if os.path.isfile(target_file):
        print(f'{prefix} libclang already exists in {target_folder}, skipping copy')
        exit(0)

    print(f'{prefix} Copying {lib_file} to {target_file}')
    shutil.copyfile(lib_file, target_file)
    print(f'{prefix} Copy completed!')
