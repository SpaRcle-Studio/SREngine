class CodegenContext:
    def __init__(self):
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