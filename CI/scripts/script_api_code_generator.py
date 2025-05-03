import typing, os
import reflection_utils, clang_utils, logger_utils, cpp_operator, script_codegen_utils, sparcle_utils

from glob import glob


def generate_type_string(type_name: str) -> str:
    if sparcle_utils.is_trivial_type(type_name):
        return type_name
    else:
        return script_codegen_utils.SCRIPT_HANDLE_TYPE_NAME


def generate_param_typed_string(param: reflection_utils.CPPParameter) -> str:
    return f'{generate_type_string(param.cpp_type.name)} {param.name}'


def generate_params_typed_string(parameters: list[reflection_utils.CPPParameter]) -> str:
    return ', '.join(
        [f'{param.cpp_type.get_full_type() if param.cpp_type.is_trivial else script_codegen_utils.SCRIPT_HANDLE_TYPE_NAME} {param.name}'
            for param in parameters]
    )


def generate_params_pass_string(parameters: list[reflection_utils.CPPParameter]) -> str:
    return ', '.join([(param.name if param.cpp_type.is_trivial else param.name + '_scriptHandleUnpacked') for param in parameters])


def generate_params_string_with_self(parameters: list[reflection_utils.CPPParameter]) -> str:
    other_params: str = generate_params_typed_string(parameters)
    if len(other_params) > 0:
        return f'{script_codegen_utils.SCRIPT_HANDLE_PARAM_NAME}, {other_params}'
    return f'{script_codegen_utils.SCRIPT_HANDLE_PARAM_NAME}'


def generate_args_unpacking_string(f: typing.IO, depth: int, code_structure: reflection_utils.CPPCodeStructure, parameters: list[reflection_utils.CPPParameter], error_return_value: str) -> None:
    for param in parameters:
        if not param.cpp_type.is_trivial:
            corrected_unpacked_type = code_structure.correct_class_name(param.cpp_type.name)

            f.write(f'{"\t" * depth}if (!{param.name}.pData) SR_UNLIKELY_ATTRIBUTE {{\n')
            f.write(f'{"\t" * (depth + 1)}SRHalt("ScriptHandle for argument \\\"{param.name}\\\" is nullptr!");\n')
            f.write(f'{"\t" * (depth + 1)}return {error_return_value};\n')
            f.write(f'{"\t" * depth}}}\n')
            f.write(f'{"\t" * depth}auto&& {param.name}_scriptHandleUnpacked = *static_cast<{corrected_unpacked_type}*>({param.name}.pData);\n')


def generate_script_handle_allocation(f: typing.IO, depth: int, var_name: str, type_name: str, is_destructible: bool) -> None:
    f.write(f'{"\t" * depth}SR_SCRIPTING_NS::SpaRcleAPIRegister::Instance().OnMemoryAlloc();\n')
    f.write(f'{"\t" * depth}{var_name}.pData = {type_name};\n')
    f.write(f'{"\t" * depth}{var_name}.pRefCount = new uint32_t(0);\n')
    f.write(f'{"\t" * depth}{var_name}.isDestructible = {'true' if is_destructible else 'false'};\n')

def make_api_default_return_value(return_type: reflection_utils.CPPType):
    if not return_type.is_trivial:
        return script_codegen_utils.SCRIPT_HANDLE_TYPE_NAME + '()'

    if return_type.is_pointer:
        return 'nullptr'

    if return_type.is_ref:
        return f'*reinterpret_cast<{return_type.name}*>(GetSpaRcleAPIDefaultRefPtr())'

    return return_type.name + '()'


def generate_method(logger: logger_utils.Logger, f: typing.IO, depth: int, class_name: str, code_structure: reflection_utils.CPPCodeStructure, method: reflection_utils.CPPMethod):
    default_return_value = make_api_default_return_value(method.return_type)

    class_name_with_namespace = code_structure.correct_class_name(class_name)

    f.write(f'{"\t" * depth}auto&& pSelfObject = static_cast<{class_name_with_namespace}*>({script_codegen_utils.SCRIPT_HANDLE_SELF_VAR_NAME}.pData);\n')
    f.write(f'{"\t" * depth}if (!pSelfObject) SR_UNLIKELY_ATTRIBUTE {{\n')
    f.write(f'{"\t" * (depth + 1)}SRHalt("ScriptHandle for self is nullptr!");\n')
    f.write(f'{"\t" * (depth + 1)}return {default_return_value};\n')
    f.write(f'{"\t" * depth}}}\n')

    generate_args_unpacking_string(f, depth, code_structure, method.parameters, default_return_value)

    call_result = f'pSelfObject->{method.name}({generate_params_pass_string(method.parameters)})'

    if method.return_type.is_trivial:
        f.write(f'{"\t" * depth}return {call_result};\n')
    else:
        f.write(f'{"\t" * depth}{script_codegen_utils.SCRIPT_HANDLE_TYPE_NAME} returnScriptHandle;\n')
        if method.return_type.is_ref:
            generate_script_handle_allocation(f, depth, 'returnScriptHandle', f'&{call_result}', False)
        else:
            generate_script_handle_allocation(f, depth, 'returnScriptHandle', f'new {code_structure.correct_class_name(method.return_type.get_full_type())}({call_result})', True)
        f.write(f'{"\t" * depth}return returnScriptHandle;\n')


def generate_operator(logger: logger_utils.Logger, f: typing.IO, depth: int, class_name: str, code_structure: reflection_utils.CPPCodeStructure, operator: reflection_utils.CPPOperator):
    is_operator_with_assigment = operator.type in cpp_operator.OPERATORS_WITH_ASSIGNMENT

    class_name_with_namespace = code_structure.correct_class_name(class_name)

    #if operator.type == cpp_operator.OperatorType.ASSIGNMENT:
    #    f.write(f'{"\t" * depth}{class_name_with_namespace.replace('::', '_')}_destroy({script_codegen_utils.SCRIPT_HANDLE_SELF_VAR_NAME});\n')
    #    generate_args_unpacking_string(f, depth + 1, code_structure, operator.parameters, script_codegen_utils.SCRIPT_HANDLE_TYPE_NAME)
    #
    #    f.write(f'{'\t' * depth}{script_codegen_utils.SCRIPT_HANDLE_TYPE_NAME} scriptHandle;\n')
    #    generate_script_handle_allocation(f, depth, 'scriptHandle', f'{class_name_with_namespace}({generate_params_pass_string(operator.parameters)})', True)
    #    f.write(f'{'\t' * depth}return scriptHandle;\n')
    #    return

    default_return_value = 'void()' if is_operator_with_assigment else make_api_default_return_value(operator.return_type)

    f.write(f'{"\t" * depth}auto&& pSelfObject = static_cast<{class_name_with_namespace}*>({script_codegen_utils.SCRIPT_HANDLE_SELF_VAR_NAME}.pData);\n')
    f.write(f'{"\t" * depth}if (!pSelfObject) SR_UNLIKELY_ATTRIBUTE {{\n')
    f.write(f'{"\t" * (depth + 1)}SRHalt("ScriptHandle for self is nullptr!");\n')
    f.write(f'{"\t" * (depth + 1)}return {default_return_value};\n')
    f.write(f'{"\t" * depth}}}\n')

    generate_args_unpacking_string(f, depth, code_structure, operator.parameters, default_return_value)

    if is_operator_with_assigment:
        f.write(f'{"\t" * depth}pSelfObject->{str(operator.type)}({generate_params_pass_string(operator.parameters)});\n')
        return

    call_result = f'pSelfObject->{str(operator.type)}({generate_params_pass_string(operator.parameters)})'

    if operator.return_type.is_trivial:
        f.write(f'{"\t" * depth}return {call_result};\n')
    else:
        f.write(f'{"\t" * depth}{script_codegen_utils.SCRIPT_HANDLE_TYPE_NAME} returnScriptHandle;\n')
        generate_script_handle_allocation(f, depth, 'returnScriptHandle', f'new {code_structure.correct_class_name(operator.return_type.get_full_type())}({call_result})', True)
        f.write(f'{"\t" * depth}return returnScriptHandle;\n')


def generate_destroy_function(logger: logger_utils.Logger, f: typing.IO, depth: int, api_function_prefix, class_name_with_namespace):
    f.write(f'{'\t' * depth}/// {class_name_with_namespace} Destroy function\n')
    f.write(f'{'\t' * depth}void {api_function_prefix}_destroy({script_codegen_utils.SCRIPT_HANDLE_PARAM_NAME}) {{\n')
    f.write(f'{'\t' * (depth + 1)}if (!{script_codegen_utils.SCRIPT_HANDLE_SELF_VAR_NAME}.pRefCount) SR_UNLIKELY_ATTRIBUTE {{\n')
    f.write(f'{'\t' * (depth + 2)}return;\n')
    f.write(f'{'\t' * (depth + 1)}}}\n')

    f.write(f'{'\t' * (depth + 1)}CodegenDecrementIfSharedPointer<{class_name_with_namespace}>({script_codegen_utils.SCRIPT_HANDLE_SELF_VAR_NAME}.pData);\n')

    f.write(f'{'\t' * (depth + 1)}SRAssert({script_codegen_utils.SCRIPT_HANDLE_SELF_VAR_NAME}.pRefCount && *{script_codegen_utils.SCRIPT_HANDLE_SELF_VAR_NAME}.pRefCount > 0);\n')
    f.write(f'{'\t' * (depth + 1)}if (--(*{script_codegen_utils.SCRIPT_HANDLE_SELF_VAR_NAME}.pRefCount) > 0) {{\n')
    f.write(f'{'\t' * (depth + 2)}return;\n')
    f.write(f'{'\t' * (depth + 1)}}}\n')
    f.write(f'{'\t' * (depth + 1)}SR_SCRIPTING_NS::SpaRcleAPIRegister::Instance().OnMemoryFree();\n')
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


def generate_increment_ref_count(logger: logger_utils.Logger, f: typing.IO, depth: int, api_function_prefix, class_name_with_namespace):
    f.write(f'{'\t' * depth}/// {class_name_with_namespace} Increment reference count function\n')
    f.write(f'{'\t' * depth}void {api_function_prefix}_increment_ref_count({script_codegen_utils.SCRIPT_HANDLE_PARAM_NAME}) {{\n')
    f.write(f'{'\t' * (depth + 1)}if (!{script_codegen_utils.SCRIPT_HANDLE_SELF_VAR_NAME}.pRefCount) SR_UNLIKELY_ATTRIBUTE {{\n')
    f.write(f'{'\t' * (depth + 2)}return;\n')
    f.write(f'{'\t' * (depth + 1)}}}\n')

    f.write(f'{'\t' * (depth + 1)}++(*{script_codegen_utils.SCRIPT_HANDLE_SELF_VAR_NAME}.pRefCount);\n')

    f.write(f'{'\t' * (depth + 1)}CodegenIncrementIfSharedPointer<{class_name_with_namespace}>({script_codegen_utils.SCRIPT_HANDLE_SELF_VAR_NAME}.pData);\n')

    f.write(f'{'\t' * depth}}}\n\n')


def generate_copy_function(logger: logger_utils.Logger, f: typing.IO, depth: int, api_function_prefix, class_name_with_namespace):
    f.write(f'{'\t' * depth}/// {class_name_with_namespace} Copy function\n')
    f.write(f'{'\t' * depth}{script_codegen_utils.SCRIPT_HANDLE_TYPE_NAME} {api_function_prefix}_copy({script_codegen_utils.SCRIPT_HANDLE_PARAM_NAME}) {{\n')
    f.write(f'{'\t' * (depth + 1)}if (!{script_codegen_utils.SCRIPT_HANDLE_SELF_VAR_NAME}.pData) SR_UNLIKELY_ATTRIBUTE {{\n')
    f.write(f'{'\t' * (depth + 2)}return {script_codegen_utils.SCRIPT_HANDLE_TYPE_NAME}();\n')
    f.write(f'{'\t' * (depth + 1)}}}\n')
    f.write(f'{'\t' * (depth + 1)}{script_codegen_utils.SCRIPT_HANDLE_TYPE_NAME} copyScriptHandle;\n')
    generate_script_handle_allocation(f, depth + 1, 'copyScriptHandle', f'new {class_name_with_namespace}(*static_cast<{class_name_with_namespace}*>({script_codegen_utils.SCRIPT_HANDLE_SELF_VAR_NAME}.pData))', True)
    f.write(f'{'\t' * (depth + 1)}return copyScriptHandle;\n')
    f.write(f'{'\t' * depth}}}\n\n')


def generate_scriptable_class(logger: logger_utils.Logger, f: typing.IO, depth: int, code_structure: reflection_utils.CPPCodeStructure, class_obj: reflection_utils.ScriptableClass):
    api_function_prefix  = code_structure.correct_class_name(class_obj.alias).replace('::', '_')
    class_name_with_namespace = code_structure.correct_class_name(class_obj.alias)

    generate_destroy_function(logger, f, depth, api_function_prefix, class_name_with_namespace)
    generate_increment_ref_count(logger, f, depth, api_function_prefix, class_name_with_namespace)

    if class_obj.has_copy_constructor:
        generate_copy_function(logger, f, depth, api_function_prefix, class_name_with_namespace)

    if len(class_obj.constructors) > 0:
        f.write(f'{'\t' * depth}/// {class_name_with_namespace} Constructors\n')
        for i, constructor in enumerate(class_obj.constructors):
            f.write(f'{'\t' * depth}/// {constructor}\n')
            f.write(f'{'\t' * depth}{script_codegen_utils.SCRIPT_HANDLE_TYPE_NAME} {api_function_prefix}_constructor_{i}({generate_params_typed_string(constructor.parameters)}) {{\n')

            generate_args_unpacking_string(f, depth + 1, code_structure, constructor.parameters, script_codegen_utils.SCRIPT_HANDLE_TYPE_NAME)

            f.write(f'{'\t' * (depth + 1)}{script_codegen_utils.SCRIPT_HANDLE_TYPE_NAME} scriptHandle;\n')
            generate_script_handle_allocation(f, depth + 1, 'scriptHandle', f'new {class_name_with_namespace}({generate_params_pass_string(constructor.parameters)})', True)
            f.write(f'{'\t' * (depth + 1)}return scriptHandle;\n')
            f.write(f'{'\t' * depth}}}\n')
        f.write('\n')

    if len(class_obj.operators) > 0:
        f.write(f'{'\t' * depth}/// {class_name_with_namespace} Operators\n')
        for i, operator in enumerate(class_obj.operators):
            params_str = generate_params_string_with_self(operator.parameters)

            operator_return_type = 'void' if (operator.type in cpp_operator.OPERATORS_WITH_ASSIGNMENT) else operator.return_type.get_handle_or_full_type()

            f.write(f'{'\t' * depth}{operator_return_type} {api_function_prefix}_operator_{operator.type.name}_{i}({params_str}) {{\n')
            generate_operator(logger, f, depth + 1, class_obj.alias, code_structure, operator)
            f.write(f'{'\t' * depth}}}\n')
        f.write('\n')

    if len(class_obj.methods) > 0:
        f.write(f'{'\t' * depth}/// {class_name_with_namespace} Methods\n')
        for i, method in enumerate(class_obj.methods):
            params_str = generate_params_string_with_self(method.parameters)
            f.write(f'{'\t' * depth}{method.return_type.get_handle_or_full_type()} {api_function_prefix}_method_{method.name}_{i}({params_str}) {{\n')
            generate_method(logger, f, depth + 1, class_obj.alias, code_structure, method)
            f.write(f'{'\t' * depth}}}\n')
        f.write('\n')

    f.write(f'{'\t' * depth}/// End of {class_obj.alias} class\n')

def generate_script_handle_struct(f: typing.IO, repo_dir: str, depth: int):
    with open(f'{repo_dir}/CI/Codegen/ScriptHandle.h', 'r', encoding='utf-8') as script_handle_header:
        for line in script_handle_header:
            f.write(f'{"\t" * depth}{line}')
    f.write(f'\n')


def generate_functions_registration(logger: logger_utils.Logger, f: typing.IO, depth: int, code_structure: reflection_utils.CPPCodeStructure):
    f.write(f'{"\t" * (depth)}void APIRegisterCallback(std::vector<void*>& table) {{\n')
    f.write(f'{"\t" * (depth + 1)}SR_INFO("APIRegisterCallback(): registering all scriptable classes...");\n')

    total_functions_count = 0
    for class_obj in code_structure.scriptable_classes:
        total_functions_count += 1 # destroy function
        total_functions_count += 1 # increment function
        if class_obj.has_copy_constructor:
            total_functions_count += 1 # copy function
        total_functions_count += len(class_obj.constructors)
        total_functions_count += len(class_obj.operators)
        total_functions_count += len(class_obj.methods)

    f.write(f'{"\t" * (depth + 1)}table.clear();\n')
    f.write(f'{"\t" * (depth + 1)}table.reserve({total_functions_count});\n\n')

    function_index = 0

    def add_func_register(file: typing.IO, depth_reg: int, code: str):
        nonlocal function_index
        file.write(f'{"\t" * depth_reg}{code} /// index: {function_index}\n')
        function_index += 1

    for class_obj in code_structure.scriptable_classes:
        class_name_with_namespace = code_structure.correct_class_name(class_obj.alias)
        api_function_prefix = class_name_with_namespace.replace('::', '_')

        f.write(f'{"\t" * (depth + 1)}SR_INFO("APIRegisterCallback(): registering {class_name_with_namespace} class...");\n')
        add_func_register(f, depth + 1, f'table.emplace_back({api_function_prefix}_destroy);')
        add_func_register(f, depth + 1, f'table.emplace_back({api_function_prefix}_increment_ref_count);')

        if class_obj.has_copy_constructor:
            add_func_register(f, depth + 1, f'table.emplace_back({api_function_prefix}_copy);')

        for i, constructor in enumerate(class_obj.constructors):
            add_func_register(f, depth + 1, f'table.emplace_back({api_function_prefix}_constructor_{i});')

        for i, operator in enumerate(class_obj.operators):
            add_func_register(f, depth + 1, f'table.emplace_back({api_function_prefix}_operator_{operator.type.name}_{i});')

        for i, method in enumerate(class_obj.methods):
            add_func_register(f, depth + 1, f'table.emplace_back({api_function_prefix}_method_{method.name}_{i});')

    f.write(f'{"\t" * (depth + 1)}SR_INFO("APIRegisterCallback(): registration done!");\n')
    f.write(f'{"\t" * (depth)}}}\n\n')


def generate_shared_ptr_template_methods(f: typing.IO, depth: int):
    f.write('''\ttemplate <typename T> void CodegenDecrementIfSharedPointer(void* rawPtr) {
        if constexpr (SR_UTILS_NS::IsSharedPointerV<T>) {
            dynamic_cast<SR_HTYPES_NS::SharedPtrBase*>(static_cast<T*>(rawPtr))->DecrementPointer();
        }
    }
    
    template <typename T> void CodegenIncrementIfSharedPointer(void* rawPtr) {
        if constexpr (SR_UTILS_NS::IsSharedPointerV<T>) {
            dynamic_cast<SR_HTYPES_NS::SharedPtrBase*>(static_cast<T*>(rawPtr))->IncrementPointer();
        }
    }\n\n''')


def generate_script_handle_file(logger: logger_utils.Logger, repo_dir: str, codegen_dir: str):
    with open(f'{codegen_dir}/ScriptHandle.generated.hpp', 'w', encoding='utf-8') as f:
        f.write(sparcle_utils.codegen_cpp_header_comment)

        f.write('#ifndef SR_CODEGEN_SPARCLE_API_SCRIPT_HANDLE_GENERATED_HPP\n')
        f.write('#define SR_CODEGEN_SPARCLE_API_SCRIPT_HANDLE_GENERATED_HPP\n\n')

        f.write('#include <Utils/stdInclude.h>\n\n')

        f.write('namespace SpaRcleAPI {\n')
        generate_script_handle_struct(f, repo_dir, 0)
        f.write('}\n\n')

        f.write('#endif /// SR_CODEGEN_SPARCLE_API_SCRIPT_HANDLE_GENERATED_HPP\n')



def generate_api(logger: logger_utils.Logger, repo_dir: str, codegen_dir: str, code_structure: reflection_utils.CPPCodeStructure):
    logger.log_info('Start generating script API...')

    for file in glob(f'{codegen_dir}/../ScriptAPI/*.hpp'):
        os.remove(file)

    os.makedirs(f'{codegen_dir}/../ScriptAPI', exist_ok=True)

    generate_script_handle_file(logger, repo_dir, codegen_dir)

    for i, class_obj in enumerate(code_structure.scriptable_classes):
        with open(f'{codegen_dir}/../ScriptAPI/{class_obj.alias}.generated.hpp', 'w', encoding='utf-8') as f:
            f.write(sparcle_utils.codegen_cpp_header_comment)
            generate_scriptable_class(logger, f, 0, code_structure, class_obj)

    with open(f'{codegen_dir}/SpaRcleAPI.generated.hpp', 'w', encoding='utf-8') as f:
        f.write(sparcle_utils.codegen_cpp_header_comment)

        f.write('#ifndef SR_CODEGEN_SPARCLE_API_GENERATED_HPP\n')
        f.write('#define SR_CODEGEN_SPARCLE_API_GENERATED_HPP\n\n')

        f.write('#include <Utils/Debug.h>\n')
        f.write('#include <Utils/Common/StringFormat.h>\n\n')

        f.write('#include <Codegen/ScriptHandle.generated.hpp>\n\n')

        if len(code_structure.scriptable_classes) > 0:
            f.write('/// Include all scriptable classes\n')
            include_set = set()
            for class_obj in code_structure.scriptable_classes:
                if class_obj.path not in include_set:
                    include_set.add(class_obj.path)
                    f.write(f'#include "{class_obj.path}"\n')
            f.write('\n')

        f.write('namespace SpaRcleAPI {\n')

        f.write('\n')

        f.write('\tvoid* GetSpaRcleAPIDefaultRefPtr() { static uint64_t def; return &def; }\n\n')

        generate_shared_ptr_template_methods(f, 1)

        for i, class_obj in enumerate(code_structure.scriptable_classes):
            f.write(f'\t#include <ScriptAPI/{class_obj.alias}.generated.hpp>\n')

        f.write('\n\t/// =========================== Register functions ==============================\n\n')

        generate_functions_registration(logger, f, 1, code_structure)

        f.write('}\n\n') # Close SpaRcleAPI namespace

        f.write('#endif /// SR_CODEGEN_SPARCLE_API_GENERATED_HPP\n')
