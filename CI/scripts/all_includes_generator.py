import json
import fnmatch
import os

from pathlib import Path
from glob import glob
from time import perf_counter
from typing import List

import sparcle_utils, codegen_context, logger_utils


def load_config(config_path):
    with open(config_path, 'r', encoding='utf-8') as f:
        return json.load(f)


def match_patterns(path, patterns):
    path_str = str(path).replace(os.sep, '/')
    return any(fnmatch.fnmatch(path_str, pattern) for pattern in patterns)


TARGET_TOKENS = ("SR_CLASS", "SR_STRUCT", "SR_ENUM")

def collect_files(logger: logger_utils.Logger, context: codegen_context.CodegenContext):
    start = perf_counter()

    config_path = Path(context.config_dir) / 'codegen-mask.json'
    config = load_config(config_path)

    includes = config.get('scripts-include' if context.is_script else 'engine-include', [])
    excludes = config.get('scripts-exclude' if context.is_script else 'engine-exclude', [])

    includes = [sparcle_utils.normalize_path(p) for p in includes]
    excludes = [sparcle_utils.normalize_path(p) for p in excludes]

    end = perf_counter()
    logger.log_info(f'Loading config \"{config_path}\" time: {end - start:.2f} sec')
    logger.log_info(f'Analyze dir: {context.analyze_dir}')

    collected_files = []

    try:
        for dir_path, _, _ in os.walk(context.analyze_dir):
            for file_path in glob(os.path.join(dir_path, '*.*'), recursive=False):
                file_path = sparcle_utils.normalize_path(file_path)
                if any((check_dir in file_path) for check_dir in excludes):
                    continue
                if any((check_dir in file_path) for check_dir in includes):
                    collected_files.append(file_path)


        files_for_codegen = []
        for file_path in collected_files:
            with open(file_path, 'r', encoding='utf-8', errors='ignore') as f:
                for line in f:
                    if any(token in line for token in TARGET_TOKENS):
                        files_for_codegen.append(file_path)
                        break
    except Exception as e:
        logger.log_fatal_error(f'Error during file collection: {e}')
        return []

    return files_for_codegen


def get_engine_include_args(context: codegen_context.CodegenContext):
    engine_root = ''
    if context.is_script:
        engine_root = context.help_sources_dir
    else:
        engine_root = context.analyze_dir + '/Engine'

    includes = [
        f'{engine_root}/inc',
        f'{engine_root}/libs/Utils/inc',
        f'{engine_root}/libs/Scripting/inc',
        f'{engine_root}/libs/Audio/inc',
        f'{engine_root}/libs/Physics/inc',
        f'{engine_root}/libs/Graphics/inc',
    ]

    include_args = [f'-I{ sparcle_utils.normalize_path(os.path.abspath(inc))}' for inc in includes]
    return include_args


def generate_all_includes_cxx(logger: logger_utils.Logger, context: codegen_context.CodegenContext) -> str:
    logger.log_info(f'Repo path: {os.path.abspath(context.analyze_dir)}')
    logger.log_info('Collect all files...')

    start = perf_counter()
    context.files_for_codegen = collect_files(logger, context)
    end = perf_counter()
    logger.log_info(f'Collecting files time: {end - start:.2f} sec')

    logger.log_info(f'Collected files: {len(context.files_for_codegen)}')

    cached_file = os.path.abspath(sparcle_utils.normalize_path(f'{context.codegen_dir}/AllIncludes.cxx'))

    # Получаем директорию из пути к файлу
    directory = os.path.dirname(cached_file)

    if not os.path.exists(directory):
        os.makedirs(directory)

    with open(f'{cached_file}', 'w', encoding='utf8') as f:
        f.write(sparcle_utils.codegen_cpp_header_comment)

        f.write('#define SR_ENGINE_CODEGEN_CLANG_PARSE_MODE\n\n')

        for file in context.files_for_codegen:
            f.write(f'#include "{os.path.abspath(file)}"' + '\n')

    return cached_file