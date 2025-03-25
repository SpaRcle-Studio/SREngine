import sys, os, subprocess, re, argparse
from glob import glob

import sparcle_utils, reflection_classes, clang_utils, meta_code_generator, script_api_code_generator, logger_utils
import script_library_code_generator


def main(logger: logger_utils.Logger, codegen_dir: str, script_api_library_dir: str, repo_path: str) -> bool:
    logger.log_info('Create cxx file with all includes...')

    meta_code_generator.generate_stub_vulkan_h(codegen_dir)
    all_includes_cxx_path = meta_code_generator.generate_all_includes_cxx(codegen_dir, repo_path)
    logger.log_info(f'All includes cxx file: {all_includes_cxx_path}')

    include_args = clang_utils.get_engine_include_args(repo_path, codegen_dir)

    logger.log_info(f'Parsing all includes cxx file: {all_includes_cxx_path}')
    code_structures: reflection_classes.CodeStructure = clang_utils.parse_header_file(logger, all_includes_cxx_path, include_args)

    codegen_dir = sparcle_utils.normalize_path(codegen_dir + '/Codegen/Codegen') # double "Codegen" for cmake pretty include
    logger.log_info(f'Codegen directory: {codegen_dir}')

    logger.log_info('Remove old generated files...')

    # delete old files
    for file in glob(f'{codegen_dir}/*.hpp'):
        os.remove(file)

    logger.log_info('Generate new files...')

    logger.log_info(f'Count of sparcle classes: {len(code_structures.sparcle_classes)}')
    logger.log_info(f'Count of scriptable classes: {len(code_structures.scriptable_classes)}')
    logger.log_info(f'Count of enums: {len(code_structures.enums)}')

    meta_code_generator.generate_classes_code(codegen_dir, code_structures.sparcle_classes)
    meta_code_generator.generate_enums_code(codegen_dir, code_structures.enums)

    script_api_code_generator.generate_api(logger, codegen_dir, code_structures)
    script_library_code_generator.generate_library(logger, script_api_library_dir, code_structures)

    return True


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="SpaRcle Code generator")
    parser.add_argument("--codegen_dir", required=True, help="Codegen directory")
    parser.add_argument("--repo_dir", required=True, help="Path to the root repo")
    parser.add_argument("--root_build_dir", required=True, help="Root build directory")
    parser.add_argument("--script_api_library_dir", required=True, help="Path to the script API library directory")
    args = parser.parse_args()

    codegen_dir = os.path.abspath(args.codegen_dir).replace("\\", "/")
    repo_dir = os.path.abspath(args.repo_dir).replace("\\", "/")
    root_build_dir = os.path.abspath(args.root_build_dir).replace("\\", "/")
    script_api_library_dir = os.path.abspath(args.script_api_library_dir).replace("\\", "/")

    logger_utils.Logger.DEBUG = True
    logger_utils.init_utf8_console()

    logger = logger_utils.Logger()
    logger.create_log_file(os.path.join(root_build_dir, 'codegen.log'))

    logger.log_info('Start script...')

    logger.log_info(f'Codegen directory: {codegen_dir}')
    logger.log_info(f'Repo directory: {repo_dir}')
    logger.log_info(f'Root build directory: {root_build_dir}')
    logger.log_info(f'Script API library directory: {script_api_library_dir}')

    lib_path = os.path.join(os.path.dirname(clang_utils.clang.cindex.__file__), 'native')
    is_unix = sys.platform.startswith('linux') or sys.platform.startswith('darwin')
    lib_file = ''

    logger.log_info(f'Platform: {sys.platform}')

    if is_unix:
        lib_file = os.path.join(lib_path, 'libclang.so')
    else:
        lib_file = os.path.join(lib_path, 'libclang.dll')
    
    lib_file = os.path.join(lib_path, lib_file)

    logger.log_info(f'libclang path: {lib_file}')

    if not os.path.isfile(lib_file):
        if is_unix:
            logger.log_fatal_error('libclang not found! Try to install libclang, e.g. "pip install libclang".')
        else:
            logger.log_fatal_error('libclang not found! Your .venv is broken.')

    logger.log_info(f'Using libclang: {lib_file}')
    clang_utils.clang.cindex.Config.set_library_file(lib_file)

    if not main(logger, codegen_dir, script_api_library_dir, repo_dir):
        input()

    logger.log_info('End script...')