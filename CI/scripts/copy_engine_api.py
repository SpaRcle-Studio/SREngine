import json
import fnmatch
import os
import re
import shutil

from pathlib import Path
from glob import glob
from time import perf_counter

import sparcle_utils, codegen_context, logger_utils


def load_config(config_path):
    with open(config_path, 'r', encoding='utf-8') as f:
        return json.load(f)


def match_patterns(path, patterns):
    path_str = str(path).replace(os.sep, '/')
    return any(fnmatch.fnmatch(path_str, pattern) for pattern in patterns)


def glob_to_regex(pattern):
    """Преобразует glob-шаблон в регулярное выражение."""
    pattern = pattern.replace('\\', '/')
    if not any(ch in pattern for ch in '*?['):
        if pattern.endswith('/'):
            # папка — экранируем
            pattern = re.escape(pattern.rstrip('/')) + r'(/|$)'
        else:
            # файл — экранируем
            pattern = re.escape(pattern)
        return re.compile(f'^{pattern}')
    else:
        # шаблон — преобразуем
        return re.compile(fnmatch_translate(pattern))


def fnmatch_translate(pat):
    """Аналог fnmatch.translate, но всегда с ^ и $"""
    import fnmatch
    return '^' + fnmatch.translate(pat).rstrip('$\n') + '$'


def collect_files(logger: logger_utils.Logger, context: codegen_context.CodegenContext):
    logger.log_info(f'Collecting source files in \"{context.analyze_dir}\"...')

    start = perf_counter()

    config_path = Path(context.config_dir) / 'PackSourcesConfig.json'
    config = load_config(config_path)

    includes = [glob_to_regex(sparcle_utils.normalize_path(os.path.join(context.analyze_dir, p.lstrip('/')))) for p in config.get('include', [])]
    excludes = [glob_to_regex(sparcle_utils.normalize_path(os.path.join(context.analyze_dir, p.lstrip('/')))) for p in config.get('exclude', [])]

    collected_files = []

    for dir_path, _, _ in os.walk(context.analyze_dir):
        for file_path in glob(os.path.join(dir_path, '*.*'), recursive=False):
            file_path = sparcle_utils.normalize_path(file_path)

            # Проверка на исключение
            if any(regex.search(file_path) for regex in excludes):
                continue

            # Проверка на включение
            if any(regex.search(file_path) for regex in includes):
                collected_files.append([file_path, False])

    for dir_path, _, _ in os.walk(context.build_dir + '/Codegen'):
        for file_path in glob(os.path.join(dir_path, '*.*'), recursive=False):
            file_path = sparcle_utils.normalize_path(file_path)
            collected_files.append([file_path, True])

    end = perf_counter()
    logger.log_info(f'Collecting {len(collected_files)} files time: {end - start:.2f} sec')

    return collected_files

def copy_files(logger: logger_utils.Logger, context: codegen_context.CodegenContext):
    collected_files = collect_files(logger, context)

    api_folder = context.analyze_dir + '/Resources/API'
    if os.path.isdir(api_folder):
        logger.log_info(f'Removing old API folder \"{api_folder}\"...')
        start = perf_counter()
        shutil.rmtree(api_folder)
        end = perf_counter()
        logger.log_info(f'Removing old API folder time: {end - start:.2f} sec')

    start = perf_counter()

    logger.log_info(f'Copying engine API to \"{api_folder}\"...')

    for file_path, in_build_folder in collected_files:
        file_path = Path(file_path)

        if in_build_folder:
            relative_path = file_path.relative_to(context.build_dir)
        else:
            relative_path = file_path.relative_to(context.analyze_dir)

        target_path = Path(api_folder) / relative_path

        target_path.parent.mkdir(parents=True, exist_ok=True)

        with open(file_path, 'rb') as src_file:
            with open(target_path, 'wb') as dst_file:
                dst_file.write(src_file.read())

    end = perf_counter()
    logger.log_info(f'Copying engine API time: {end - start:.2f} sec')
