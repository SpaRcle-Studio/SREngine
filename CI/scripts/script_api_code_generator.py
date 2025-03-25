import typing

import reflection_classes, clang_utils, logger_utils, cpp_operator

SCRIPT_HANDLE_TYPE_NAME = 'ScriptHandle'
SCRIPT_HANDLE_SELF_VAR_NAME = 'selfScriptHandle'
SCRIPT_HANDLE_PARAM_NAME = f'{SCRIPT_HANDLE_TYPE_NAME} {SCRIPT_HANDLE_SELF_VAR_NAME}'


def generate_type_string(type_name: str) -> str:
    if clang_utils.is_trivial_type(type_name):
        return type_name
    else:
        return SCRIPT_HANDLE_TYPE_NAME


def generate_param_typed_string(param: reflection_classes.Parameter) -> str:
    return f'{generate_type_string(param.type_name)} {param.name}'


def generate_params_typed_string(parameters: list[reflection_classes.Parameter]) -> str:
    return ', '.join([generate_param_typed_string(param) for param in parameters])


def generate_params_pass_string(parameters: list[reflection_classes.Parameter]) -> str:
    return ', '.join([(param.name if param.is_trivial else param.name + '_scriptHandleUnpacked') for param in parameters])


def generate_params_string_with_self(parameters: list[reflection_classes.Parameter]) -> str:
    params = ', '.join([generate_param_typed_string(param) for param in parameters])
    return f'{SCRIPT_HANDLE_PARAM_NAME}, {params}' if len(parameters) > 0 else SCRIPT_HANDLE_PARAM_NAME


def generate_args_unpacking_string(f: typing.IO, depth: int, code_structure: reflection_classes.CodeStructure, parameters: list[reflection_classes.Parameter], error_return_type: str) -> None:
    for param in parameters:
        if not param.is_trivial:
            corrected_unpacked_type = code_structure.correct_class_namespaces(clang_utils.remove_type_qualifiers(param.type_name))

            f.write(f'{"\t" * depth}auto&& {param.name}_scriptHandleUnpacked = *static_cast<{corrected_unpacked_type}*>({param.name}.pData);\n')
            f.write(f'{"\t" * depth}if (!{param.name}_scriptHandleUnpacked) SR_UNLIKELY_ATTRIBUTE {{\n')
            f.write(f'{"\t" * (depth + 1)}SRHalt("ScriptHandle for argument \\\"{param.name}\\\" is nullptr!");\n')
            f.write(f'{"\t" * (depth + 1)}return {error_return_type}();\n')
            f.write(f'{"\t" * depth}}}\n')


def generate_method(logger: logger_utils.Logger, f: typing.IO, depth: int, class_name: str, code_structure: reflection_classes.CodeStructure, method: reflection_classes.Method):
    is_return_type_trivial = clang_utils.is_trivial_type(method.return_type)
    return_type = code_structure.correct_class_namespaces(method.return_type if is_return_type_trivial else SCRIPT_HANDLE_TYPE_NAME)

    class_name_with_namespace = code_structure.correct_class_namespaces(class_name)

    f.write(f'{"\t" * depth}auto&& pSelfObject = static_cast<{class_name_with_namespace}*>({SCRIPT_HANDLE_SELF_VAR_NAME}.pData);\n')
    f.write(f'{"\t" * depth}if (!pSelfObject) SR_UNLIKELY_ATTRIBUTE {{\n')
    f.write(f'{"\t" * (depth + 1)}SRHalt("ScriptHandle for self is nullptr!");\n')
    f.write(f'{"\t" * (depth + 1)}return {return_type}();\n')
    f.write(f'{"\t" * depth}}}\n')

    generate_args_unpacking_string(f, depth, code_structure, method.parameters, return_type)

    call_result = f'pSelfObject->{method.name}({generate_params_pass_string(method.parameters)})'

    if is_return_type_trivial:
        f.write(f'{"\t" * depth}return {call_result};\n')
    else:
        f.write(f'{"\t" * depth}{SCRIPT_HANDLE_TYPE_NAME} returnScriptHandle;\n')
        f.write(f'{"\t" * depth}returnScriptHandle.pData = new {code_structure.correct_class_namespaces(method.return_type)}({call_result});\n')
        f.write(f'{"\t" * depth}returnScriptHandle.isDestructible = true;\n')
        f.write(f'{"\t" * depth}return returnScriptHandle;\n')


def generate_operator(logger: logger_utils.Logger, f: typing.IO, depth: int, class_name: str, code_structure: reflection_classes.CodeStructure, operator: reflection_classes.Operator):
    is_return_type_trivial = clang_utils.is_trivial_type(operator.return_type)
    return_type = code_structure.correct_class_namespaces(operator.return_type if is_return_type_trivial else SCRIPT_HANDLE_TYPE_NAME)

    class_name_with_namespace = code_structure.correct_class_namespaces(class_name)

    if operator.type == cpp_operator.OperatorType.ASSIGNMENT:
        f.write(f'{"\t" * depth}{class_name_with_namespace.replace('::', '_')}_destroy({SCRIPT_HANDLE_SELF_VAR_NAME});\n')
        generate_args_unpacking_string(f, depth + 1, code_structure, operator.parameters, SCRIPT_HANDLE_TYPE_NAME)

        f.write(f'{'\t' * depth}{SCRIPT_HANDLE_TYPE_NAME} scriptHandle;\n')
        f.write(f'{'\t' * depth}scriptHandle.pData = new {class_name_with_namespace}({generate_params_pass_string(operator.parameters)});\n')
        f.write(f'{'\t' * depth}scriptHandle.isDestructible = true;\n')
        f.write(f'{'\t' * depth}return scriptHandle;\n')
        return

    f.write(f'{"\t" * depth}auto&& pSelfObject = static_cast<{class_name_with_namespace}*>({SCRIPT_HANDLE_SELF_VAR_NAME}.pData);\n')
    f.write(f'{"\t" * depth}if (!pSelfObject) SR_UNLIKELY_ATTRIBUTE {{\n')
    f.write(f'{"\t" * (depth + 1)}SRHalt("ScriptHandle for self is nullptr!");\n')
    f.write(f'{"\t" * (depth + 1)}return {return_type}();\n')
    f.write(f'{"\t" * depth}}}\n')

    generate_args_unpacking_string(f, depth, code_structure, operator.parameters, return_type)

    call_result = f'pSelfObject->{cpp_operator.OperatorType.to_string(operator.type)}({generate_params_pass_string(operator.parameters)})'

    if is_return_type_trivial:
        f.write(f'{"\t" * depth}return {call_result};\n')
    else:
        f.write(f'{"\t" * depth}{SCRIPT_HANDLE_TYPE_NAME} returnScriptHandle;\n')
        f.write(f'{"\t" * depth}returnScriptHandle.pData = new {code_structure.correct_class_namespaces(operator.return_type)}({call_result});\n')
        f.write(f'{"\t" * depth}returnScriptHandle.isDestructible = true;\n')
        f.write(f'{"\t" * depth}return returnScriptHandle;\n')


def generate_scriptable_class(logger: logger_utils.Logger, f: typing.IO, depth: int, code_structure: reflection_classes.CodeStructure, class_obj: reflection_classes.ScriptableClass):
    api_function_prefix  = code_structure.correct_class_namespaces(class_obj.alias).replace('::', '_')

    f.write(f'{'\t' * depth}/// {class_obj.alias} Destroy function\n')
    f.write(f'{'\t' * depth}void {api_function_prefix}_destroy({SCRIPT_HANDLE_PARAM_NAME}) {{\n')
    f.write(f'{'\t' * (depth + 1)}if (!{SCRIPT_HANDLE_SELF_VAR_NAME}.pData) SR_UNLIKELY_ATTRIBUTE {{\n')
    f.write(f'{'\t' * (depth + 2)}return;\n')
    f.write(f'{'\t' * (depth + 1)}}}\n')
    f.write(f'{'\t' * (depth + 1)}SRAssert({SCRIPT_HANDLE_SELF_VAR_NAME}.pRefCount && *{SCRIPT_HANDLE_SELF_VAR_NAME}.pRefCount > 0);\n')
    f.write(f'{'\t' * (depth + 1)}if (--(*{SCRIPT_HANDLE_SELF_VAR_NAME}.pRefCount) > 0) {{\n')
    f.write(f'{'\t' * (depth + 2)}return;\n')
    f.write(f'{'\t' * (depth + 1)}}}\n')
    f.write(f'{'\t' * (depth + 1)}delete {SCRIPT_HANDLE_SELF_VAR_NAME}.pRefCount;\n')
    f.write(f'{'\t' * (depth + 1)}{SCRIPT_HANDLE_SELF_VAR_NAME}.pRefCount = nullptr;\n')
    f.write(f'{'\t' * (depth + 1)}if (!{SCRIPT_HANDLE_SELF_VAR_NAME}.isDestructible) SR_UNLIKELY_ATTRIBUTE {{\n')
    f.write(f'{'\t' * (depth + 2)}return;\n')
    f.write(f'{'\t' * (depth + 1)}}}\n')
    f.write(f'{'\t' * (depth + 1)}if constexpr (SR_UTILS_NS::HasPublicDestructor<{code_structure.correct_class_namespaces(class_obj.alias)}>()) {{\n')
    f.write(f'{'\t' * (depth + 2)}delete static_cast<{code_structure.correct_class_namespaces(class_obj.alias)}*>({SCRIPT_HANDLE_SELF_VAR_NAME}.pData);\n')
    f.write(f'{'\t' * (depth + 2)}{SCRIPT_HANDLE_SELF_VAR_NAME}.pData = nullptr;\n')
    f.write(f'{'\t' * (depth + 1)}}} else {{\n')
    f.write(f'{'\t' * (depth + 2)}SRHalt("ScriptHandle destructor called for non-destructible class");\n')
    f.write(f'{'\t' * (depth + 1)}}}\n')
    f.write(f'{'\t' * depth}}}\n\n')

    if len(class_obj.constructors) > 0:
        f.write(f'{'\t' * depth}/// {class_obj.alias} Constructors\n')
        for i, constructor in enumerate(class_obj.constructors):
            f.write(f'{'\t' * depth}/// {constructor}\n')
            f.write(f'{'\t' * depth}{SCRIPT_HANDLE_TYPE_NAME} {api_function_prefix}_constructor_{i}({generate_params_typed_string(constructor.parameters)}) {{\n')

            generate_args_unpacking_string(f, depth + 1, code_structure, constructor.parameters, SCRIPT_HANDLE_TYPE_NAME)

            f.write(f'{'\t' * (depth + 1)}{SCRIPT_HANDLE_TYPE_NAME} scriptHandle;\n')
            f.write(f'{'\t' * (depth + 1)}scriptHandle.pData = new {code_structure.correct_class_namespaces(class_obj.alias)}({generate_params_pass_string(constructor.parameters)});\n')
            f.write(f'{'\t' * (depth + 1)}scriptHandle.isDestructible = true;\n')
            f.write(f'{'\t' * (depth + 1)}return scriptHandle;\n')
            f.write(f'{'\t' * depth}}}\n')
        f.write('\n')

    if len(class_obj.operators) > 0:
        f.write(f'{'\t' * depth}/// {class_obj.alias} Operators\n')
        for i, operator in enumerate(class_obj.operators):
            params_str = generate_params_string_with_self(operator.parameters)
            f.write(f'{'\t' * depth}{generate_type_string(operator.return_type)} {api_function_prefix}_operator_{operator.type.name}_{i}({params_str}) {{\n')
            generate_operator(logger, f, depth + 1, class_obj.alias, code_structure, operator)
            f.write(f'{'\t' * depth}}}\n')
        f.write('\n')

    if len(class_obj.methods) > 0:
        f.write(f'{'\t' * depth}/// {class_obj.alias} Methods\n')
        for i, method in enumerate(class_obj.methods):
            params_str = generate_params_string_with_self(method.parameters)
            f.write(f'{'\t' * depth}{generate_type_string(method.return_type)} {api_function_prefix}_method_{method.name}_{i}({params_str}) {{\n')
            generate_method(logger, f, depth + 1, class_obj.alias, code_structure, method)
            f.write(f'{'\t' * depth}}}\n')
        f.write('\n')

    f.write(f'{'\t' * depth}/// End of {class_obj.alias} class\n')


def generate_api(logger: logger_utils.Logger, codegen_dir: str, code_structure: reflection_classes.CodeStructure):
    print('Start generating script API...')

    with open(f'{codegen_dir}/SpaRcleAPI.generated.hpp', 'w', encoding='utf-8') as f:
        f.write(clang_utils.codegen_cpp_header_comment)

        f.write('#ifndef SR_CODEGEN_SPARCLE_API_GENERATED_HPP\n')
        f.write('#define SR_CODEGEN_SPARCLE_API_GENERATED_HPP\n\n')

        if len(code_structure.scriptable_classes) > 0:
            f.write('/// Include all scriptable classes\n')
            include_set = set()
            for class_obj in code_structure.scriptable_classes:
                if class_obj.path not in include_set:
                    include_set.add(class_obj.path)
                    f.write(f'#include "{class_obj.path}"\n')
            f.write('\n')

        f.write('namespace SparcleAPI {\n')

        f.write('#ifdef SR_MSVC\n')
        f.write('    #pragma pack(push, 1) // MSVC: Remove padding\n')
        f.write('#endif\n\n')

        f.write(f'\textern "C" {{\n')
        f.write(f'\t    struct {SCRIPT_HANDLE_TYPE_NAME} {{\n')
        f.write(f'\t        void* pData = nullptr;\n')
        f.write(f'\t        uint32_t* pRefCount = nullptr;\n')
        f.write(f'\t        bool isDestructible = false;\n')
        f.write(f'\t    }} SR_GCC_CLANG_REMOVE_PADDING_ATTRIB;\n')
        f.write(f'\t}}\n\n')

        f.write('#ifdef SR_MSVC\n')
        f.write('    #pragma pack(pop) // MSVC: Restore pack settings\n')
        f.write('#endif\n\n')

        for i, class_obj in enumerate(code_structure.scriptable_classes):
            generate_scriptable_class(logger, f, 1, code_structure, class_obj)
            if i < len(code_structure.scriptable_classes) - 1:
                f.write('\n')

        f.write('}\n\n') # Close SparcleAPI namespace

        f.write('#endif /// SR_CODEGEN_SPARCLE_API_GENERATED_HPP\n')
