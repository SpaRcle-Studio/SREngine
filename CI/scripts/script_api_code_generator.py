import typing

import reflection_classes, clang_utils, logger_utils, cpp_operator, script_codegen_utils


def generate_type_string(type_name: str) -> str:
    if clang_utils.is_trivial_type(type_name):
        return type_name
    else:
        return script_codegen_utils.SCRIPT_HANDLE_TYPE_NAME


def generate_param_typed_string(param: reflection_classes.Parameter) -> str:
    return f'{generate_type_string(param.type_name)} {param.name}'


def generate_params_typed_string(parameters: list[reflection_classes.Parameter]) -> str:
    return ', '.join([generate_param_typed_string(param) for param in parameters])


def generate_params_pass_string(parameters: list[reflection_classes.Parameter]) -> str:
    return ', '.join([(param.name if param.is_trivial else param.name + '_scriptHandleUnpacked') for param in parameters])


def generate_params_string_with_self(parameters: list[reflection_classes.Parameter]) -> str:
    params = ', '.join([generate_param_typed_string(param) for param in parameters])
    return f'{script_codegen_utils.SCRIPT_HANDLE_PARAM_NAME}, {params}' if len(parameters) > 0 else script_codegen_utils.SCRIPT_HANDLE_PARAM_NAME


def generate_return_value_string(return_type: str) -> str:
    if return_type == 'nullptr':
        return 'nullptr'
    return f'{return_type}()'


def generate_args_unpacking_string(f: typing.IO, depth: int, code_structure: reflection_classes.CodeStructure, parameters: list[reflection_classes.Parameter], error_return_type: str) -> None:
    for param in parameters:
        if not param.is_trivial:
            corrected_unpacked_type = code_structure.correct_class_name(clang_utils.remove_type_qualifiers(param.type_name))

            f.write(f'{"\t" * depth}auto&& {param.name}_scriptHandleUnpacked = *static_cast<{corrected_unpacked_type}*>({param.name}.pData);\n')
            f.write(f'{"\t" * depth}if (!{param.name}_scriptHandleUnpacked) SR_UNLIKELY_ATTRIBUTE {{\n')
            f.write(f'{"\t" * (depth + 1)}SRHalt("ScriptHandle for argument \\\"{param.name}\\\" is nullptr!");\n')
            f.write(f'{"\t" * (depth + 1)}return {generate_return_value_string(error_return_type)};\n')
            f.write(f'{"\t" * depth}}}\n')


def generate_script_handle_allocation(f: typing.IO, depth: int, var_name: str, type_name: str, is_destructible: bool) -> None:
    f.write(f'{"\t" * depth}MemoryLeakChecker::Instance().OnMemoryAlloc();\n')
    f.write(f'{"\t" * depth}{var_name}.pData = new {type_name};\n')
    f.write(f'{"\t" * depth}{var_name}.pRefCount = new uint32_t(0);\n')
    f.write(f'{"\t" * depth}{var_name}.isDestructible = {'true' if is_destructible else 'false'};\n')


def generate_method(logger: logger_utils.Logger, f: typing.IO, depth: int, class_name: str, code_structure: reflection_classes.CodeStructure, method: reflection_classes.Method):
    is_return_type_trivial, return_type = clang_utils.correct_default_return_type(method.return_type, code_structure)

    class_name_with_namespace = code_structure.correct_class_name(class_name)

    f.write(f'{"\t" * depth}auto&& pSelfObject = static_cast<{class_name_with_namespace}*>({script_codegen_utils.SCRIPT_HANDLE_SELF_VAR_NAME}.pData);\n')
    f.write(f'{"\t" * depth}if (!pSelfObject) SR_UNLIKELY_ATTRIBUTE {{\n')
    f.write(f'{"\t" * (depth + 1)}SRHalt("ScriptHandle for self is nullptr!");\n')
    f.write(f'{"\t" * (depth + 1)}return {generate_return_value_string(return_type)};\n')
    f.write(f'{"\t" * depth}}}\n')

    generate_args_unpacking_string(f, depth, code_structure, method.parameters, return_type)

    call_result = f'pSelfObject->{method.name}({generate_params_pass_string(method.parameters)})'

    if is_return_type_trivial:
        f.write(f'{"\t" * depth}return {call_result};\n')
    else:
        f.write(f'{"\t" * depth}{script_codegen_utils.SCRIPT_HANDLE_TYPE_NAME} returnScriptHandle;\n')
        generate_script_handle_allocation(f, depth, 'returnScriptHandle', f'{code_structure.correct_class_name(method.return_type)}({call_result})', True)
        f.write(f'{"\t" * depth}return returnScriptHandle;\n')


def generate_operator(logger: logger_utils.Logger, f: typing.IO, depth: int, class_name: str, code_structure: reflection_classes.CodeStructure, operator: reflection_classes.Operator):
    is_return_type_trivial, return_type = clang_utils.correct_default_return_type(operator.return_type, code_structure)

    class_name_with_namespace = code_structure.correct_class_name(class_name)

    if operator.type == cpp_operator.OperatorType.ASSIGNMENT:
        f.write(f'{"\t" * depth}{class_name_with_namespace.replace('::', '_')}_destroy({script_codegen_utils.SCRIPT_HANDLE_SELF_VAR_NAME});\n')
        generate_args_unpacking_string(f, depth + 1, code_structure, operator.parameters, script_codegen_utils.SCRIPT_HANDLE_TYPE_NAME)

        f.write(f'{'\t' * depth}{script_codegen_utils.SCRIPT_HANDLE_TYPE_NAME} scriptHandle;\n')
        generate_script_handle_allocation(f, depth, 'scriptHandle', f'{class_name_with_namespace}({generate_params_pass_string(operator.parameters)})', True)
        f.write(f'{'\t' * depth}return scriptHandle;\n')
        return

    f.write(f'{"\t" * depth}auto&& pSelfObject = static_cast<{class_name_with_namespace}*>({script_codegen_utils.SCRIPT_HANDLE_SELF_VAR_NAME}.pData);\n')
    f.write(f'{"\t" * depth}if (!pSelfObject) SR_UNLIKELY_ATTRIBUTE {{\n')
    f.write(f'{"\t" * (depth + 1)}SRHalt("ScriptHandle for self is nullptr!");\n')
    f.write(f'{"\t" * (depth + 1)}return {generate_return_value_string(return_type)};\n')
    f.write(f'{"\t" * depth}}}\n')

    generate_args_unpacking_string(f, depth, code_structure, operator.parameters, return_type)

    call_result = f'pSelfObject->{cpp_operator.OperatorType.to_string(operator.type)}({generate_params_pass_string(operator.parameters)})'

    if is_return_type_trivial:
        f.write(f'{"\t" * depth}return {call_result};\n')
    else:
        f.write(f'{"\t" * depth}{script_codegen_utils.SCRIPT_HANDLE_TYPE_NAME} returnScriptHandle;\n')
        generate_script_handle_allocation(f, depth, 'returnScriptHandle', f'{code_structure.correct_class_name(operator.return_type)}({call_result})', True)
        f.write(f'{"\t" * depth}return returnScriptHandle;\n')


def generate_destroy_function(logger: logger_utils.Logger, f: typing.IO, depth: int, api_function_prefix, class_name_with_namespace):
    f.write(f'{'\t' * depth}/// {class_name_with_namespace} Destroy function\n')
    f.write(f'{'\t' * depth}void {api_function_prefix}_destroy({script_codegen_utils.SCRIPT_HANDLE_PARAM_NAME}) {{\n')
    f.write(f'{'\t' * (depth + 1)}if (!{script_codegen_utils.SCRIPT_HANDLE_SELF_VAR_NAME}.pData) SR_UNLIKELY_ATTRIBUTE {{\n')
    f.write(f'{'\t' * (depth + 2)}return;\n')
    f.write(f'{'\t' * (depth + 1)}}}\n')
    f.write(f'{'\t' * (depth + 1)}SRAssert({script_codegen_utils.SCRIPT_HANDLE_SELF_VAR_NAME}.pRefCount && *{script_codegen_utils.SCRIPT_HANDLE_SELF_VAR_NAME}.pRefCount > 0);\n')
    f.write(f'{'\t' * (depth + 1)}if (--(*{script_codegen_utils.SCRIPT_HANDLE_SELF_VAR_NAME}.pRefCount) > 0) {{\n')
    f.write(f'{'\t' * (depth + 2)}return;\n')
    f.write(f'{'\t' * (depth + 1)}}}\n')
    f.write(f'{'\t' * (depth + 1)}MemoryLeakChecker::Instance().OnMemoryFree();\n')
    f.write(f'{'\t' * (depth + 1)}delete {script_codegen_utils.SCRIPT_HANDLE_SELF_VAR_NAME}.pRefCount;\n')
    f.write(f'{'\t' * (depth + 1)}{script_codegen_utils.SCRIPT_HANDLE_SELF_VAR_NAME}.pRefCount = nullptr;\n')
    f.write(f'{'\t' * (depth + 1)}if (!{script_codegen_utils.SCRIPT_HANDLE_SELF_VAR_NAME}.isDestructible) SR_UNLIKELY_ATTRIBUTE {{\n')
    f.write(f'{'\t' * (depth + 2)}return;\n')
    f.write(f'{'\t' * (depth + 1)}}}\n')
    f.write(f'{'\t' * (depth + 1)}if constexpr (SR_UTILS_NS::HasPublicDestructor<{class_name_with_namespace}>()) {{\n')
    f.write(f'{'\t' * (depth + 2)}delete static_cast<{class_name_with_namespace}*>({script_codegen_utils.SCRIPT_HANDLE_SELF_VAR_NAME}.pData);\n')
    f.write(f'{'\t' * (depth + 2)}{script_codegen_utils.SCRIPT_HANDLE_SELF_VAR_NAME}.pData = nullptr;\n')
    f.write(f'{'\t' * (depth + 1)}}} else {{\n')
    f.write(f'{'\t' * (depth + 2)}SRHalt("ScriptHandle destructor called for non-destructible class");\n')
    f.write(f'{'\t' * (depth + 1)}}}\n')
    f.write(f'{'\t' * depth}}}\n\n')


def generate_copy_function(logger: logger_utils.Logger, f: typing.IO, depth: int, api_function_prefix, class_name_with_namespace):
    f.write(f'{'\t' * depth}/// {class_name_with_namespace} Copy function\n')
    f.write(f'{'\t' * depth}{script_codegen_utils.SCRIPT_HANDLE_TYPE_NAME} {api_function_prefix}_copy({script_codegen_utils.SCRIPT_HANDLE_PARAM_NAME}) {{\n')
    f.write(f'{'\t' * (depth + 1)}if (!{script_codegen_utils.SCRIPT_HANDLE_SELF_VAR_NAME}.pData) SR_UNLIKELY_ATTRIBUTE {{\n')
    f.write(f'{'\t' * (depth + 2)}return {script_codegen_utils.SCRIPT_HANDLE_TYPE_NAME}();\n')
    f.write(f'{'\t' * (depth + 1)}}}\n')
    f.write(f'{'\t' * (depth + 1)}{script_codegen_utils.SCRIPT_HANDLE_TYPE_NAME} copyScriptHandle;\n')
    generate_script_handle_allocation(f, depth + 1, 'copyScriptHandle', f'{class_name_with_namespace}(*static_cast<{class_name_with_namespace}*>({script_codegen_utils.SCRIPT_HANDLE_SELF_VAR_NAME}.pData))', True)
    f.write(f'{'\t' * (depth + 1)}return copyScriptHandle;\n')
    f.write(f'{'\t' * depth}}}\n\n')


def generate_scriptable_class(logger: logger_utils.Logger, f: typing.IO, depth: int, code_structure: reflection_classes.CodeStructure, class_obj: reflection_classes.ScriptableClass):
    api_function_prefix  = code_structure.correct_class_name(class_obj.alias).replace('::', '_')
    class_name_with_namespace = code_structure.correct_class_name(class_obj.alias)

    generate_destroy_function(logger, f, depth, api_function_prefix, class_name_with_namespace)
    generate_copy_function(logger, f, depth, api_function_prefix, class_name_with_namespace)

    if len(class_obj.constructors) > 0:
        f.write(f'{'\t' * depth}/// {class_name_with_namespace} Constructors\n')
        for i, constructor in enumerate(class_obj.constructors):
            f.write(f'{'\t' * depth}/// {constructor}\n')
            f.write(f'{'\t' * depth}{script_codegen_utils.SCRIPT_HANDLE_TYPE_NAME} {api_function_prefix}_constructor_{i}({generate_params_typed_string(constructor.parameters)}) {{\n')

            generate_args_unpacking_string(f, depth + 1, code_structure, constructor.parameters, script_codegen_utils.SCRIPT_HANDLE_TYPE_NAME)

            f.write(f'{'\t' * (depth + 1)}{script_codegen_utils.SCRIPT_HANDLE_TYPE_NAME} scriptHandle;\n')
            generate_script_handle_allocation(f, depth + 1, 'scriptHandle', f'{class_name_with_namespace}({generate_params_pass_string(constructor.parameters)})', True)
            f.write(f'{'\t' * (depth + 1)}return scriptHandle;\n')
            f.write(f'{'\t' * depth}}}\n')
        f.write('\n')

    if len(class_obj.operators) > 0:
        f.write(f'{'\t' * depth}/// {class_name_with_namespace} Operators\n')
        for i, operator in enumerate(class_obj.operators):
            params_str = generate_params_string_with_self(operator.parameters)
            f.write(f'{'\t' * depth}{generate_type_string(operator.return_type)} {api_function_prefix}_operator_{operator.type.name}_{i}({params_str}) {{\n')
            generate_operator(logger, f, depth + 1, class_obj.alias, code_structure, operator)
            f.write(f'{'\t' * depth}}}\n')
        f.write('\n')

    if len(class_obj.methods) > 0:
        f.write(f'{'\t' * depth}/// {class_name_with_namespace} Methods\n')
        for i, method in enumerate(class_obj.methods):
            params_str = generate_params_string_with_self(method.parameters)
            f.write(f'{'\t' * depth}{generate_type_string(method.return_type)} {api_function_prefix}_method_{method.name}_{i}({params_str}) {{\n')
            generate_method(logger, f, depth + 1, class_obj.alias, code_structure, method)
            f.write(f'{'\t' * depth}}}\n')
        f.write('\n')

    f.write(f'{'\t' * depth}/// End of {class_obj.alias} class\n')

def generate_script_handle_struct(f: typing.IO, repo_dir: str, depth: int):
    with open(f'{repo_dir}/CI/Codegen/ScriptHandle.h', 'r', encoding='utf-8') as script_handle_header:
        for line in script_handle_header:
            f.write(f'{"\t" * depth}{line}')
    f.write(f'\n')


def generate_functions_registration(logger: logger_utils.Logger, f: typing.IO, depth: int, code_structure: reflection_classes.CodeStructure):
    f.write(f'{"\t" * depth} class SpaRcleAPIRegister {{\n')
    f.write(f'{"\t" * (depth + 1)}using FunctionHandle = void*;\n')
    f.write(f'{"\t" * (depth + 0)}private:\n')
    f.write(f'{"\t" * (depth + 1)}SpaRcleAPIRegister() = default;\n')
    f.write(f'{"\t" * (depth + 1)}~SpaRcleAPIRegister() = default;\n\n')
    f.write(f'{"\t" * (depth + 0)}public:\n')
    f.write(f'{"\t" * (depth + 1)}static SpaRcleAPIRegister& Instance() {{\n')
    f.write(f'{"\t" * (depth + 2)}static SpaRcleAPIRegister instance;\n')
    f.write(f'{"\t" * (depth + 2)}return instance;\n')
    f.write(f'{"\t" * (depth + 1)}}}\n\n')
    f.write(f'{"\t" * (depth + 1)}SR_NODISCARD uint64_t GetCountFunctions() {{ return m_functionTable.size(); }}\n\n')
    f.write(f'{"\t" * (depth + 1)}SR_NODISCARD void* GetFunction(uint64_t index) {{ return m_functionTable[index]; }}\n\n')
    f.write(f'{"\t" * (depth + 1)}void RegisterAll() {{\n')
    f.write(f'{"\t" * (depth + 2)}SR_INFO("SpaRcleAPIRegister::RegisterAll(): registering all scriptable classes...");\n')

    total_functions_count = 0
    for class_obj in code_structure.scriptable_classes:
        total_functions_count += 1 # destroy function
        total_functions_count += 1 # copy function
        total_functions_count += len(class_obj.constructors)
        total_functions_count += len(class_obj.operators)
        total_functions_count += len(class_obj.methods)

    f.write(f'{"\t" * (depth + 2)}m_functionTable.reserve({total_functions_count});\n\n')

    for class_obj in code_structure.scriptable_classes:
        class_name_with_namespace = code_structure.correct_class_name(class_obj.alias)
        api_function_prefix = class_name_with_namespace.replace('::', '_')

        f.write(f'{"\t" * (depth + 2)}SR_INFO("SpaRcleAPIRegister::RegisterAll(): registering {class_name_with_namespace} class...");\n')
        f.write(f'{"\t" * (depth + 2)}m_functionTable.emplace_back({api_function_prefix}_destroy);\n')
        f.write(f'{"\t" * (depth + 2)}m_functionTable.emplace_back({api_function_prefix}_copy);\n')

        for i, constructor in enumerate(class_obj.constructors):
            f.write(f'{"\t" * (depth + 2)}m_functionTable.emplace_back({api_function_prefix}_constructor_{i});\n')

        for i, operator in enumerate(class_obj.operators):
            f.write(f'{"\t" * (depth + 2)}m_functionTable.emplace_back({api_function_prefix}_operator_{operator.type.name}_{i});\n')

        for i, method in enumerate(class_obj.methods):
            f.write(f'{"\t" * (depth + 2)}m_functionTable.emplace_back({api_function_prefix}_method_{method.name}_{i});\n')

    f.write(f'{"\t" * (depth + 2)}SR_INFO("SpaRcleAPIRegister::RegisterAll(): registration done!");\n')
    f.write(f'{"\t" * (depth + 1)}}}\n\n')
    f.write(f'{"\t" * (depth + 0)}private:\n')
    f.write(f'{"\t" * (depth + 1)}std::vector<FunctionHandle> m_functionTable;\n\n')
    f.write(f'{"\t" * (depth + 0)}}};\n')


def generate_memory_leak_checker(f: typing.IO, depth: int):
    f.write(f'{"\t" * depth}/// Memory leak checker\n')
    f.write(f'{"\t" * depth}class MemoryLeakChecker {{\n')
    f.write(f'{"\t" * depth}private:\n')
    f.write(f'{"\t" * (depth + 1)}MemoryLeakChecker() = default;\n')
    f.write(f'{"\t" * (depth + 1)}~MemoryLeakChecker() = default;\n\n')
    f.write(f'{"\t" * depth}public:\n')
    f.write(f'{"\t" * (depth + 1)}MemoryLeakChecker(const MemoryLeakChecker&) = delete;\n')
    f.write(f'{"\t" * (depth + 1)}MemoryLeakChecker& operator=(const MemoryLeakChecker&) = delete;\n\n')
    f.write(f'{"\t" * (depth + 1)}MemoryLeakChecker(MemoryLeakChecker&&) = delete;\n')
    f.write(f'{"\t" * (depth + 1)}MemoryLeakChecker& operator=(MemoryLeakChecker&&) = delete;\n\n')
    f.write(f'{"\t" * depth}public:\n')
    f.write(f'{"\t" * (depth + 1)}static MemoryLeakChecker& Instance() {{\n')
    f.write(f'{"\t" * (depth + 2)}static MemoryLeakChecker instance;\n')
    f.write(f'{"\t" * (depth + 2)}return instance;\n')
    f.write(f'{"\t" * (depth + 1)}}}\n\n')
    f.write(f'{"\t" * (depth + 1)}void OnMemoryAlloc() {{ m_allocationsCount++; }}\n')
    f.write(f'{"\t" * (depth + 1)}void OnMemoryFree() {{ m_allocationsCount--; }}\n')
    f.write(f'{"\t" * (depth + 1)}void CheckMemoryLeaks() {{\n')
    f.write(f'{"\t" * (depth + 2)}if (m_allocationsCount > 0) {{\n')
    f.write(f'{"\t" * (depth + 3)}SRHalt("Memory leak detected! Allocations count: {{}}", m_allocationsCount.load());\n')
    f.write(f'{"\t" * (depth + 2)}}}\n')
    f.write(f'{"\t" * (depth + 1)}}}\n\n')
    f.write(f'{"\t" * depth}private:\n')
    f.write(f'{"\t" * (depth + 1)}std::atomic<uint64_t> m_allocationsCount = 0;\n\n')
    f.write(f'{"\t" * (depth + 0)}}};\n\n')


def generate_api(logger: logger_utils.Logger, repo_dir: str, codegen_dir: str, code_structure: reflection_classes.CodeStructure):
    logger.log_info('Start generating script API...')

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

        f.write('namespace SpaRcleAPI {\n')

        generate_script_handle_struct(f, repo_dir, 0)
        f.write('\n')
        generate_memory_leak_checker(f, 1)

        for i, class_obj in enumerate(code_structure.scriptable_classes):
            generate_scriptable_class(logger, f, 1, code_structure, class_obj)
            if i < len(code_structure.scriptable_classes) - 1:
                f.write('\n')

        f.write('\n\t/// =========================== Register functions ==============================\n\n')

        generate_functions_registration(logger, f, 1, code_structure)

        f.write('}\n\n') # Close SpaRcleAPI namespace

        f.write('#endif /// SR_CODEGEN_SPARCLE_API_GENERATED_HPP\n')
