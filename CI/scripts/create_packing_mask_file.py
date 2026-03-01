import json
import fnmatch
import os
import re
import shutil

from pathlib import Path
from glob import glob
from time import perf_counter

import sparcle_utils, codegen_context, logger_utils

def wildcard_to_regex(mask: str) -> str:
    regex = ""
    for c in mask:
        if c == '*':
            regex += ".*"
        elif c == '?':
            regex += "."
        elif c == '.':
            regex += r"\."
        elif c == '\\':
            regex += "/"
        else:
            regex += c
    return "^" + regex + "$"


def is_excluded(rel_path: Path, exclude_patterns: list[re.Pattern]) -> bool:
    path_str = rel_path.as_posix()
    for pattern in exclude_patterns:
        if pattern.fullmatch(path_str):   # аналог std::regex_match
            return True
    return False
    #path_str = rel_path.as_posix()  # Normalize
    #for pattern in exclude_patterns:
    #    if pattern.fullmatch(path_str):
    #        return True
    #    parts = path_str.split('/')
    #    for i in range(1, len(parts)):
    #        sub = '/'.join(parts[:i])
    #        if pattern.fullmatch(sub):
    #            return True
    #return False


def get_resources_pack_files(resources_path: Path, exclude_patterns):
    files = []

    for root, dirs, filenames in os.walk(resources_path):
        root_path = Path(root)
        rel_root = root_path.relative_to(resources_path)

        # копия списка, потому что будем модифицировать
        for d in dirs[:]:
            rel_dir = (rel_root / d)
            if is_excluded(rel_dir, exclude_patterns):
                dirs.remove(d)  # отключаем рекурсию как в C++

        for f in filenames:
            rel_file = rel_root / f
            if not is_excluded(rel_file, exclude_patterns):
                files.append(str((root_path / f).resolve()))

    return files


def load_exclude_mask(path_to_file: str):
    masks = {}

    with open(path_to_file, 'r', encoding='utf-8') as f:
        current_platform = None
        for line in f:
            line = line.strip()
            if not line or line == '\n' or line == '':
                continue
            if line.startswith('['):
                current_platform = line.split('[')[1].split(']')[0]
                masks[current_platform] = ['Utilities/libclang', 'Utilities/codegen']
            elif current_platform:
                masks[current_platform].append(line)

    result = []
    for platform, masks_by_platform in masks.items():
        result.append([platform, [re.compile(wildcard_to_regex(mask)) for mask in masks_by_platform]])
    return result


def load_exclude_mask_by_platform(path_to_file: str, platform: str):
    masks = load_exclude_mask(path_to_file)
    masks_for_platform = []
    for p, m in masks:
        if p == platform or p == 'All':
            masks_for_platform.extend(m)
    return masks_for_platform


def create_mask(logger: logger_utils.Logger, context: codegen_context.CodegenContext):
    output_file_path = context.resources_dir + '/Engine/Configs/OnlineDownloaderMask.conf'
    config_path = context.resources_dir + '/Engine/Configs/PackExcludeSettings.conf'

    logger.log_info(f'Creating online downloader mask file \"{output_file_path}\" from \"{config_path}\"...')

    start = perf_counter()

    masks = load_exclude_mask(config_path)
    print(masks)

    resources_path = Path(context.resources_dir).resolve()

    with open(output_file_path, 'w', encoding='utf-8') as f:
        current_platform = None
        for platform, exclude_patterns in masks:
            if not current_platform or current_platform != platform:
                f.write(f'[{platform}]\n')

            for entry in resources_path.rglob("*"):
                rel_path = entry.relative_to(resources_path)
                if entry.is_dir():
                    continue

                if is_excluded(rel_path, exclude_patterns):
                    continue

                if entry.is_file():
                    f.write(f'{rel_path.as_posix()}\n')

    end = perf_counter()
    logger.log_info(f'Creating online downloader mask file time: {end - start:.2f} sec')

