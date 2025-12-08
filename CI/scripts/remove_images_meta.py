import os
import time
import logging
from PIL import Image
from concurrent.futures import ThreadPoolExecutor, as_completed

# Конфигурация
BASE_DIR = os.path.abspath(os.path.join(os.path.dirname(__file__), "../../Resources")) # Папка относительно скрипта
DELAY = 0.0 # Задержка между обработкой файлов (в секундах)
FILES_LIMIT = 200 # Максимальное количество файлов для обработки
MAX_WORKERS = 8  # Количество потоков
USE_MULTITHREADING = True  # Включить многопоточность


# Настройка логирования
logging.basicConfig(
    level=logging.INFO,
    format="%(asctime)s - %(levelname)s - %(message)s",
    handlers=[logging.FileHandler("clean_metadata.log", encoding="utf-8"), logging.StreamHandler()]
)


def clean_image_metadata(file_path):
    """
     Safely remove metadata from PNG, JPEG, and JPG files.
     Works for 8-bit, 16-bit, indexed PNGs, and RGB/RGBA images.
    """

    logging.info(f"Processing file: {file_path}")

    try:
        ext = file_path.lower().split('.')[-1]
        if ext not in ("png", "jpg", "jpeg"):
            logging.warning(f"Skipped unknown file type: {file_path}")
            return

        with Image.open(file_path) as img:
            if ext in ("jpg", "jpeg"):
                # For JPEG: remove EXIF and save
                # Pillow will strip EXIF if not specified
                img.save(file_path, format="JPEG", quality=95)
                logging.info(f"Metadata cleared for JPEG: {file_path}")

            elif ext == "png":
                # For PNG: save without PngInfo → removes all text chunks
                img.save(file_path, format="PNG", optimize=True)
                logging.info(f"Metadata cleared for PNG: {file_path}")

    except Exception as e:
        logging.error(f"Failed to remove metadata from {file_path}: {e}")


def get_image_files(directory):
    files = []
    for root, dirs, filenames in os.walk(directory):
        if not os.path.abspath(root).startswith(BASE_DIR):
            logging.warning(f"Skipped folder outside base dir: {root}")
            continue
        for f in filenames:
            if f.lower().endswith((".png", ".jpg", ".jpeg")):
                files.append(os.path.join(root, f))
    return files


def main():
    logging.info(f"Starting metadata cleanup in {BASE_DIR}")

    files = get_image_files(BASE_DIR)
    if not files:
        logging.info("No image files found to process.")

    if len(files) > FILES_LIMIT:
        logging.error(f"Total files to process ({len(files)}) exceed limit of {FILES_LIMIT}.")
        return

    if USE_MULTITHREADING:
        with ThreadPoolExecutor(max_workers=MAX_WORKERS) as executor:
            futures = [executor.submit(clean_image_metadata, f) for f in files]
            for _ in as_completed(futures):
                pass  # логирование внутри функции
    else:
        for file_path in files:
            clean_image_metadata(file_path)
            time.sleep(DELAY)

    logging.info("Metadata cleanup completed.")


if __name__ == "__main__":
    main()