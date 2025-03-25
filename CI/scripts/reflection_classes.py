import os, cpp_operator, clang_utils, logger_utils


class Parameter:
    def __init__(self, name: str, type_name: str):
        self.name: str = name
        self.type_name: str = type_name
        self.is_trivial: bool = clang_utils.is_trivial_type(type_name)

    def set_type(self, new_type: str):
        self.type_name = new_type
        self.is_trivial = clang_utils.is_trivial_type(new_type)


    def __str__(self):
        return f'Parameter: {self.name}, Type: {self.type_name}'


class Operator:
    def __init__(self, op_type: cpp_operator.OperatorType, return_type: str):
        self.type: cpp_operator.OperatorType = op_type
        self.return_type: str = return_type
        self.parameters: list[Parameter] = []

    def add_parameter(self, parameter: Parameter):
        self.parameters.append(parameter)

    def __str__(self):
        return f'Operator: {self.type}, Return type: {self.return_type}, Parameters: {self.parameters}'

class Constructor:
    def __init__(self):
        self.parameters: list[Parameter] = []

    def __str__(self):
        return f'Constructor: {', '.join([str(param) for param in self.parameters])}'

    def add_parameter(self, parameter: Parameter):
        self.parameters.append(parameter)


class Property:
    def __init__(self, name, type_name):
        self.name = name
        self.display_name = name
        self.serialize_name = name
        self.type_name = type_name
        self.default_value = None
        self.change_callback = None
        self.setter = None
        self.getter = None
        self.reset_value = None
        self.property_condition = None
        self.load_condition = None
        self.custom_args = {}
        self.drag_value = None
        self.editor_width = None
        self.read_only = False
        self.not_null = False
        self.no_header = False
        self.hidden = False
        self.private = False
        self.dontLoad = False
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

        print(f'Add custom arg to prop \"{self.name}\": \"{arg}\", key: \"{key}\", value: \"{value}\"')

        self.custom_args[key] = value


class Method:
    def __init__(self, name: str, return_type: str):
        self.name: str = name
        self.return_type: str = return_type
        self.parameters: list[Parameter] = []

    def add_parameter(self, parameter: Parameter):
        self.parameters.append(parameter)

    def __str__(self):
        return f'Method: {self.name}, Return type: {self.return_type}, Parameters: {self.parameters}'


class Enum:
    def __init__(self, name, variant, count, type, enum_class, namespaces, source_path):
        self.name = name
        self.variant = variant
        self.count = count
        self.namespaces = namespaces
        self.type = type
        self.enum_class = enum_class
        self.source_path = os.path.normpath(source_path)


class SpaRcleClass:
    def __init__(self, name, namespaces):
        self.name = name
        self.inspector = None
        self.version = None
        self.category = None
        self.hidden = False
        self.namespaces = namespaces
        self.variables = []
        self.path = None
        self.inherited_classes = []

    def add_variable(self, variable):
        self.variables.append(variable)


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


class ScriptableClass:
    def __init__(self, name: str, namespaces: list[str], alias: str = ''):
        self.name = name
        self.namespaces = namespaces

        # alias example: name is "Vector3<float_t>" and alias is "FVector3"
        # by default alias is equal to name
        if alias == '':
            self.alias = name
        else:
            self.alias = alias

        self.constructors: list[Constructor] = []
        self.methods: list[Method] = []
        self.operators: list[Operator] = []
        self.path = None


    def replace_type(self, logger: logger_utils.Logger, old_type: str, new_type: str):
        for constructor in self.constructors:
            for parameter in constructor.parameters:
                parameter.set_type(clang_utils.replace_type_templated_name(logger, parameter.type_name, old_type, new_type))

        for method in self.methods:
            for parameter in method.parameters:
                parameter.set_type(clang_utils.replace_type_templated_name(logger, parameter.type_name, old_type, new_type))
            method.return_type = clang_utils.replace_type_templated_name(logger, method.return_type, old_type, new_type)

        for operator in self.operators:
            for parameter in operator.parameters:
                parameter.set_type(clang_utils.replace_type_templated_name(logger, parameter.type_name, old_type, new_type))
            operator.return_type = clang_utils.replace_type_templated_name(logger, operator.return_type, old_type, new_type)


    def add_constructor(self, constructor: Constructor):
        self.constructors.append(constructor)


    def add_method(self, method: Method):
        self.methods.append(method)


    def add_operator(self, operator: Operator):
        self.operators.append(operator)


class CodeStructure:
    def __init__(self, logger: logger_utils.Logger):
        self.sparcle_classes: list[SpaRcleClass] = []
        self.scriptable_classes: list[ScriptableClass] = []
        self.enums: list[Enum] = []
        # example class name StringAtom and full name is SpaRcle::Utils::StringAtom
        self.class_namespaces_table: dict[str, str] = {}
        self.logger = logger

    def add_class_namespace(self, class_name: str, full_class_name: str):
        # add class name to class_namespaces_table
        self.class_namespaces_table[class_name] = full_class_name
        self.logger.log_debug(f'Add class name to class_namespaces_table: {class_name} -> {full_class_name}')

    def correct_class_namespaces(self, class_name: str) -> str:
         # use class_namespaces_table to get full class name
        if class_name in self.class_namespaces_table:
            return self.class_namespaces_table[class_name]
        return class_name