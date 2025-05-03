import sys, os, argparse
from glob import glob

import sparcle_utils
import codegen_context
import logger_utils
import clang_utils
import meta_code_generator


def main(logger: logger_utils.Logger, context: codegen_context.CodegenContext) -> bool:
    logger.log_info('Create cxx file with all includes...')

    meta_code_generator.generate_stub_vulkan_h(context.codegen_dir)
    all_includes_cxx_path = meta_code_generator.generate_all_includes_cxx(context)
    logger.log_info(f'All includes cxx file: {all_includes_cxx_path}')

    include_args = clang_utils.get_engine_include_args(context)

    logger.log_info(f'Parsing all includes cxx file: {all_includes_cxx_path}')
    code_structures = clang_utils.parse_header_file(logger, all_includes_cxx_path, include_args, context)

    logger.log_info('Remove old generated files...')

    # delete old files
    for file in glob(f'{context.codegen_dir}/*.hpp'):
        os.remove(file)

    logger.log_info('Generate new files...')

    logger.log_info(f'Count of sparcle classes: {len(code_structures.sparcle_classes)}')
    #logger.log_info(f'Count of scriptable classes: {len(code_structures.scriptable_classes)}')
    logger.log_info(f'Count of enums: {len(code_structures.enums)}')

    meta_code_generator.generate_classes_code(logger, context, code_structures.sparcle_classes)
    meta_code_generator.generate_enums_code(context.codegen_dir, code_structures.enums)

    #script_api_code_generator.generate_api(logger, repo_dir, codegen_dir, code_structures)
    #script_library_code_generator.generate_library(logger, repo_dir, script_api_library_dir, code_structures)

    return True


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="SpaRcle Code generator")
    parser.add_argument("--codegen_dir", required=True, help="Codegen directory")
    parser.add_argument("--repo_dir", required=True, help="Path to the root repo")
    parser.add_argument("--root_build_dir", required=True, help="Root build directory")
    parser.add_argument("--lib_clang_dir", required=True, help="Folder with libclang")
    parser.add_argument("--module_name", required=True, help="Module name")
    parser.add_argument("--is_script", action='store_true', help="Is script")
    parser.add_argument("--help_sources_dir", required=False, help="Help sources directory")
    args = parser.parse_args()

    lib_clang_dir = os.path.abspath(args.lib_clang_dir).replace("\\", "/")

    context = codegen_context.CodegenContext()
    context.build_dir = os.path.abspath(args.root_build_dir).replace("\\", "/")
    context.module_name = args.module_name
    context.analyze_dir = os.path.abspath(args.repo_dir).replace("\\", "/")
    context.is_script = args.is_script
    context.help_sources_dir = os.path.abspath(args.help_sources_dir).replace("\\", "/") if args.help_sources_dir else ""

    logger_utils.Logger.DEBUG = True
    logger_utils.init_utf8_console()

    logger = logger_utils.Logger()
    logger.set_module_name(args.module_name)
    logger.create_log_file(os.path.join(context.build_dir, 'codegen.log'))

    logger.log_info('Start script...')

    context.codegen_dir = sparcle_utils.normalize_path(os.path.abspath(args.codegen_dir).replace("\\", "/") + '/Codegen/Codegen') # double "Codegen" for cmake pretty include

    logger.log_info(f'Codegen directory: {context.codegen_dir}')
    logger.log_info(f'Analyze directory: {context.analyze_dir}')
    logger.log_info(f'Root build directory: {context.build_dir}')

    is_unix = sys.platform.startswith('linux') or sys.platform.startswith('darwin')
    logger.log_info(f'Platform: {sys.platform}')

    lib_file = ''

    if is_unix:
        lib_file = os.path.join(f'{lib_clang_dir}', 'libclang.so')
    else:
        lib_file = os.path.join(f'{lib_clang_dir}', 'libclang.dll')
    
    logger.log_info(f'libclang path: {lib_file}')

    if not os.path.isfile(lib_file):
        logger.log_fatal_error(f'libclang not found! Your resources folder is broken. lib path: {lib_file}')

    logger.log_info(f'Using libclang: {lib_file}')
    clang_utils.clang.cindex.Config.set_library_file(lib_file)

    if not main(logger, context):
        input()

    logger.log_info('End script...')