import os
import sys
import argparse
from pylint.lint import Run


def run_pylint_analyze(directory):
    if not os.path.isdir(directory):
        print(f"Ошибка: Папка '{directory}' не найдена.")
        sys.exit(1)

    print(f"Запуск pylint для всех .py файлов в: {directory}")
    Run([directory, '--disable=all', '--enable=E,F'])


def main():
    parser = argparse.ArgumentParser(description="Запуск pylint для указанной папки")
    parser.add_argument("path", help="Путь до папки со скриптами")
    args = parser.parse_args()

    run_pylint_analyze(os.path.abspath(args.path))


if __name__ == '__main__':
    main()