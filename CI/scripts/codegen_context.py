import json
from pathlib import Path

CODEGEN_SAVE_ENABLED = True
CODEGEN_LOAD_ENABLED = True
CODEGEN_CLONE_ENABLED = True
CODEGEN_ENTT_ENABLED = True

class CodegenContext:
    def __init__(self):
        self.resources_dir = ''
        self.config_dir = ''
        self.module_name = ''
        self.codegen_dir = ''
        self.analyze_dir = ''
        self.build_dir = ''
        self.help_sources_dir = ''
        self.is_script = False
        self.files_for_codegen = []
        self.valid_files_for_codegen = set()
        self.codegen_stack_trace = []
        self.modules_mask = []

    def initialize(self):
        config_path = Path(self.config_dir) / 'codegen-modules.json'
        with open(config_path, 'r', encoding='utf-8') as f:
            data = json.load(f)
            pairs = list(data["modules"].items())
            self.modules_mask = pairs
