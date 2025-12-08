#!/bin/bash

# Получить путь до текущего скрипта
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

# Путь к виртуальному окружению
VENV_PYTHON="../.venv/python/python"

# Проверяем, существует ли путь к Python в виртуальном окружении
if [[ -f "$VENV_PYTHON" ]]; then
    PYTHON="$VENV_PYTHON"
else
    # Если файл не существует, используем системный Python
    PYTHON="python3"
fi

# Запустить Python скрипт
"$PYTHON" scripts/remove_images_meta.py

read -p "Press Enter to continue..."
