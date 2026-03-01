import sys, os, argparse, re, shutil
from glob import glob
from time import perf_counter
from pathlib import Path

import logger_utils, create_packing_mask_file

def main(logger: logger_utils.Logger, resources_dir: str, build_dir: str, config_file: str, platform: str) -> bool:
    start = perf_counter()

    masks = create_packing_mask_file.load_exclude_mask_by_platform(config_file, platform)
    logger.log_info(masks)

    resources_path = Path(resources_dir).resolve()
    files = create_packing_mask_file.get_resources_pack_files(resources_path, masks)

    resources_to_pack_build_path = os.path.join(build_dir, 'PackedResources')

    if os.path.exists(resources_to_pack_build_path):
        logger.log_info(f'Cleaning existing packed resources directory: {resources_to_pack_build_path}')
        shutil.rmtree(resources_to_pack_build_path)

    for f in files:
        logger.log_info(f'File to pack: {f}')
        rel_path = os.path.relpath(f, resources_dir)
        target_path = os.path.join(resources_to_pack_build_path, rel_path)
        os.makedirs(os.path.dirname(target_path), exist_ok=True)
        shutil.copyfile(f, target_path)

    end = perf_counter()
    logger.log_info(f'Copying resources time: {end - start:.2f} sec')

    return True


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="SpaRcle Code generator")
    parser.add_argument("--repo_dir", required=True, help="Path to the root repo")
    parser.add_argument("--root_build_dir", required=True, help="Root build directory")
    parser.add_argument("--platform", required=True, help="Target platform")
    args = parser.parse_args()

    resources_dir = os.path.abspath(args.repo_dir.replace('\"', '')).replace("\\", "/") + '/Resources'
    build_dir = os.path.abspath(args.root_build_dir.replace('\"', '')).replace("\\", "/")
    platform = args.platform.replace('\"', '')

    config_path = resources_dir + '/Engine/Configs/PackExcludeSettings.conf'

    logger_utils.Logger.DEBUG = False
    logger_utils.init_utf8_console()

    logger = logger_utils.Logger()
    logger.create_log_file(os.path.join(build_dir, 'copy_res.log'))

    logger.log_info('Start copying resources...')

    logger.log_info(f'Root build directory: {build_dir}')
    logger.log_info(f'Resource directory: {resources_dir}')
    logger.log_info(f'Config directory: {config_path}')
    logger.log_info(f'Platform: {platform}')

    if not os.path.isfile(config_path):
        logger.log_fatal_error(f'Config file not found! Your resources folder is broken. Config path: {config_path}')

    logger.log_info(f'Using config file: {config_path}')

    if not main(logger, resources_dir, build_dir, config_path, platform):
        logger.log_fatal_error('Failed to copy resources!')
        input()

    logger.log_info('Finished copying resources!')