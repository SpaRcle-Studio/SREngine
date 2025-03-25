import typing

import reflection_classes, clang_utils, logger_utils, cpp_operator

def generate_library(logger: logger_utils.Logger, library_dir: str, code_structure: reflection_classes.CodeStructure):
    print('Start generating script library...')

