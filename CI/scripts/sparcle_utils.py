import sys, os, subprocess, re
from glob import glob

def normalize_path(path):
    """Нормализует слеши в путях для различных ОС."""
    return os.path.normpath(path)

def make_serialize_property_name(name):
    if name.startswith('m_'):
        name = name[2:]
    if name.startswith('_'):
        name = name[1:]
    return name


# display name for UI
# example: m_isSomeProperty -> Is Some Property
# example: isSomeProperty -> Is Some Property
# example: is_some_property -> Is Some Property
def make_display_name(name):
    name = make_serialize_property_name(name)
    # 1. Замена snake_case на пробелы и приведение к правильному регистру
    name = re.sub(r'_+', ' ', name)
    # 2. Разделение camelCase и PascalCase на слова
    name = re.sub(r'([a-z])([A-Z])', r'\1 \2', name)
    # 3. Приведение первой буквы каждого слова к верхнему регистру
    name = ' '.join(word.capitalize() for word in name.split())
    return name