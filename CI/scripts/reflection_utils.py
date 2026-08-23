import cpp_operator
import sparcle_utils


class CPPType:
    def __init__(self, name: str):
        self.name: str = name
        self.is_const: bool = name.startswith('const ')
        self.is_ref: bool = name.endswith('&')
        self.is_pointer: bool = name.endswith('*')

        if self.is_const:
            self.name = self.name[6:]

        self.name = self.name.replace(' ', '')

        if self.is_ref:
            self.name = self.name[:-1]

        if self.is_pointer:
            self.name = self.name[:-1]

        if self.name.endswith('&') or self.name.endswith('*') or self.name.endswith(' '):
            raise ValueError(f'Invalid type name: \"{name}\", processed name: \"{self.name}\"')

        self.is_trivial: bool = sparcle_utils.is_trivial_type(self.name)

    def get_full_type(self) -> str:
        return f'{"const " if self.is_const else ""}{self.name}{" &" if self.is_ref else ""}{"*" if self.is_pointer else ""}'


    def get_handle_or_full_type(self) -> str:
        return self.get_full_type() if self.is_trivial else f'{sparcle_utils.script_codegen_utils.SCRIPT_HANDLE_TYPE_NAME}'


    def __str__(self):
        return f'CPPType: {self.name}, Is const: {self.is_const}, Is ref: {self.is_ref}, Is trivial: {self.is_trivial}'


class CPPParameter:
    def __init__(self, name: str, type_name: str):
        self.name: str = name
        self.type: CPPType = CPPType(type_name)


    def set_type(self, new_type: str):
        self.type = CPPType(new_type)


    def __str__(self):
        return f'Parameter: {self.name}, Type: {self.type}'


class CPPProperty:
    def __init__(self, name, type_name):
        self.name = name
        self.display_name = None
        self.serialize_name = name
        self.type_name = type_name
        self.default_value = None
        self.change_callback = None
        self.enum_filter = None
        self.setter = None
        self.getter = None
        self.reset_value = None
        self.range = None
        self.property_condition = None
        self.load_condition = None
        self.custom_args = {}
        self.drag_value = None
        self.editor_width = None
        self.read_only = False
        self.debug_only = False
        self.not_null = False
        self.no_header = False
        self.group = None
        self.hidden = False
        self.private = False
        self.dontLoad = False
        self.dont_save_tags = []
        self.virtual = False

    def __str__(self):
        return f'Property: {self.name}, Type: {self.type_name}, Default value: {self.default_value}'

    def add_custom_arg(self, arg, index):
        key = arg[:index]
        value = arg[index:]

        if key.startswith(' '):
            key = key[1:]

        if value.startswith(': '):
            value = value[2:]

        #print(f'Add custom arg to prop \"{self.name}\": \"{arg}\", key: \"{key}\", value: \"{value}\"')

        self.custom_args[key] = value


class CPPMethod:
    def __init__(self, name: str, return_type: str):
        self.name: str = name
        self.return_type: CPPType = CPPType(return_type)
        self.parameters: list[CPPParameter] = []
        self.is_const = False
        self.condition = None
        self.editor_button = False
        self.evaluate = False

    def add_parameter(self, parameter: CPPParameter):
        self.parameters.append(parameter)

    def __str__(self):
        return f'Method: {self.name}, Return type: {self.return_type}, Parameters: {self.parameters}'


class CPPEnum:
    def __init__(self, name, variant, count, type, enum_class, namespaces, source_path, va_args):
        self.name = name
        self.variant = variant
        self.code_module_name = None
        self.count = count
        self.namespaces = namespaces
        self.type = type
        self.enum_class = enum_class
        self.source_path = sparcle_utils.normalize_path(source_path)
        self.va_args = va_args
        self.is_help_source = False


class SpaRcleClass:
    def __init__(self, name, namespaces):
        self.name = name
        self.display_name = None
        self.inspector = None
        self.version = None
        self.category = None
        self.extension = None
        self.hidden = False
        self.namespaces = namespaces
        self.variables = []
        self.methods: list[CPPMethod] = []
        self.path = None
        self.code_module_name = None
        self.inherited_classes = []
        self.is_help_source = False
        self.abstract = False
        self.no_copyable = False
        self.no_movable = False

    def add_variable(self, variable):
        self.variables.append(variable)

    def add_method(self, method: CPPMethod):
        self.methods.append(method)

    def to_string(self, depth):
        namespace_str = '::'.join(self.namespaces)
        #properties_str = ', '.join([str(prop) for prop in self.variables])
        #return f'Class: {namespace_str}::{self.name}, Variables: {properties_str}'
        str = f'{namespace_str} Class: {self.name} Path: {self.path}\n'

        for prop in self.inherited_classes:
            str += "\t" * depth
            str += f'Inherited: {prop}\n'
        for prop in self.variables:
            str += "\t" * depth
            str += f'{prop}\n'

        return str


class CPPCodeStructure:
    def __init__(self):
        self.sparcle_classes: list[SpaRcleClass] = []
        self.enums: list[CPPEnum] = []
        # example class name StringAtom and full name is SpaRcle::Utils::StringAtom
        self.class_names_table: dict[str, str] = {}

    def find_class_by_name(self, class_name: str) -> SpaRcleClass | None:
        for sparcle_class in self.sparcle_classes:
            if sparcle_class.name == class_name:
                return sparcle_class

        return None

    def add_class_name_correction(self, class_name: str, full_class_name: str):
        # add class name to class_namespaces_table
        self.class_names_table[class_name] = full_class_name
        #self.logger.log_debug(f'Add class name to class_names_table: {class_name} -> {full_class_name}')

    def correct_class_name(self, class_name: str) -> str:
        # use class_names_table to get full class name

        #print(f'Correct class name: \"{class_name}\"')

        if class_name in self.class_names_table:
            class_name = self.class_names_table[class_name]

        return class_name

    def set_sources_as_help(self):
        for sparcle_class in self.sparcle_classes:
            sparcle_class.is_help_source = True
        for enum in self.enums:
            enum.is_help_source = True