import typing, os, re
import reflection_classes, clang_utils, logger_utils, cpp_operator, script_api_code_generator, script_codegen_utils


def delete_old_library(logger: logger_utils.Logger, library_dir: str):
    if os.path.isdir(library_dir):
        logger.log_info(f'Delete old library directory: {library_dir}')

        files_to_delete = []
        for root, dirs, files in os.walk(library_dir):
            for file in files:
                if file.endswith('.h') or file.endswith('.cpp'):
                    files_to_delete.append(os.path.join(root, file))
                else:
                    logger.log_fatal_error(f'File "{file}" is not a header or cpp file. Destructive operation!')
                    return

        for file in files_to_delete:
            logger.log_debug(f'Delete file: {file}')
            os.remove(file)

        empty_dirs = []
        for dirpath, dirnames, filenames in os.walk(library_dir, topdown=False):
            if filenames:
                logger.log_fatal_error(f'Library directory "{library_dir}" contains non-empty files. Destructive operation!')
                return

            if not dirnames:
                empty_dirs.append(dirpath)
            else:
                if all(os.path.join(dirpath, d) in empty_dirs for d in dirnames):
                    empty_dirs.append(dirpath)
                else:
                    logger.log_fatal_error(f'Directory "{dirpath}" contains non-empty subdirectories. Destructive operation!')
                    return

        for dirpath in empty_dirs:
            logger.log_debug(f'Delete directory: {dirpath}')
            os.rmdir(dirpath)

        logger.log_info(f'Old library directory deleted.')


def make_correct_type_for_library(code_structure: reflection_classes.CodeStructure, cpp_type: reflection_classes.CPPType, is_return_type = False) -> str:
    full_type_name = code_structure.correct_class_name(cpp_type.name)
    if cpp_type.is_ref and is_return_type and not cpp_type.is_trivial:
        return f'UnsafeRef<{full_type_name}>'
    return f'{"const " if cpp_type.is_const else ""}{full_type_name}{" &" if cpp_type.is_ref else ""}{"*" if cpp_type.is_pointer else ""}'


def make_correct_type_for_api(code_structure: reflection_classes.CodeStructure, cpp_type: reflection_classes.CPPType) -> str:
    if cpp_type.is_trivial:
        return make_correct_type_for_library(code_structure, cpp_type)
    return script_codegen_utils.SCRIPT_HANDLE_TYPE_NAME


def generate_header_constructor(f: typing.IO, depth: int, scriptable_class: reflection_classes.ScriptableClass, constructor: reflection_classes.Constructor, code_structure: reflection_classes.CodeStructure):
    f.write(f'{depth * '\t'}\t{scriptable_class.alias}(')
    f.write(', '.join([f'{make_correct_type_for_library(code_structure, parameter.cpp_type)} {parameter.name}' for parameter in constructor.parameters]))
    f.write(');\n')


def generate_header_operator(f: typing.IO, depth: int, scriptable_class: reflection_classes.ScriptableClass, operator: reflection_classes.Operator, code_structure: reflection_classes.CodeStructure):
    return_type = make_correct_type_for_library(code_structure, operator.return_type)

    f.write(f'{depth * '\t'}\t{return_type} {str(operator.type)}(')
    f.write(', '.join([f'{make_correct_type_for_library(code_structure, parameter.cpp_type)} {parameter.name}' for parameter in operator.parameters]))
    f.write(f'){' const;' if operator.is_const else ';'}\n')


def generate_header_method(f: typing.IO, depth: int, scriptable_class: reflection_classes.ScriptableClass, method: reflection_classes.Method, code_structure: reflection_classes.CodeStructure):
    return_type = make_correct_type_for_library(code_structure, method.return_type, True)
    nodiscard_attr = '[[nodiscard]] ' if method.return_type != 'void' and method.is_const else ''

    f.write(f'{depth * '\t'}\t{nodiscard_attr}{return_type} {method.name}(')
    f.write(', '.join([f'{make_correct_type_for_library(code_structure, parameter.cpp_type)} {parameter.name}' for parameter in method.parameters]))
    f.write(f'){' const;' if method.is_const else ';'}\n')


def generate_cpp_constructor(f: typing.IO, depth: int, function_index: int, increment_function_index: int, scriptable_class: reflection_classes.ScriptableClass,
                             constructor: reflection_classes.Constructor, code_structure: reflection_classes.CodeStructure):

    f.write(f'{depth * '\t'}{'::'.join(scriptable_class.namespaces)}::{scriptable_class.alias}::{scriptable_class.alias}(')
    f.write(', '.join([f'{make_correct_type_for_library(code_structure, parameter.cpp_type)} {parameter.name}' for parameter in constructor.parameters]))
    f.write(') {\n')

    operator_fn = f'{script_codegen_utils.SCRIPT_HANDLE_TYPE_NAME} (*)('
    operator_fn += ', '.join([f'{make_correct_type_for_api(code_structure, parameter.cpp_type)}' for parameter in constructor.parameters]) + ')'

    f.write(f'{depth * '\t'}\tauto&& pConstructorFunc = ({operator_fn})CoreAPI::Instance().GetFunction({function_index});\n')
    f.write(f'{depth * '\t'}\tm_handle = pConstructorFunc(')
    f.write(', '.join([(parameter.name + ('.GetScriptHandle()' if not parameter.cpp_type.is_trivial else ''))
                       for parameter in constructor.parameters]))
    f.write(');\n')
    f.write(f'{depth * '\t'}\tauto&& pIncrementFunc = (void (*)(ScriptHandle))CoreAPI::Instance().GetFunction(API_INCREMENT_FUNCTION_INDEX);\n')
    f.write(f'{depth * '\t'}\tpIncrementFunc(m_handle);\n')

    f.write(f'{depth * '\t'}}}\n')


def generate_cpp_operator(f: typing.IO, depth: int, function_index: int, scriptable_class: reflection_classes.ScriptableClass, operator: reflection_classes.Operator, code_structure: reflection_classes.CodeStructure):
    return_type_lib = make_correct_type_for_library(code_structure, operator.return_type)

    f.write(f'{depth * '\t'}{return_type_lib} {'::'.join(scriptable_class.namespaces)}::{scriptable_class.alias}::{str(operator.type)}(')
    f.write(', '.join([f'{make_correct_type_for_library(code_structure, parameter.cpp_type)} {parameter.name}' for parameter in operator.parameters]))
    f.write(f') {'const ' if operator.is_const else ''}{{\n')

    if operator.type in cpp_operator.OPERATORS_WITH_ASSIGNMENT:
        f.write(f'{depth * '\t'}\tauto&& pOperatorFunc = (void (*)(ScriptHandle, {make_correct_type_for_api(code_structure, operator.parameters[0].cpp_type)}))CoreAPI::Instance().GetFunction({function_index});\n')
        f.write(f'{depth * '\t'}\tpOperatorFunc(m_handle, {operator.parameters[0].name}' + ('.GetScriptHandle()' if not operator.parameters[0].cpp_type.is_trivial else '') + ');\n')
        f.write(f'{depth * '\t'}\treturn *this;\n')
    else:
        operator_func_args = f'{script_codegen_utils.SCRIPT_HANDLE_TYPE_NAME}' + ''.join([f', {make_correct_type_for_api(code_structure, parameter.cpp_type)}' for parameter in operator.parameters])

        return_type_api = make_correct_type_for_api(code_structure, operator.return_type)
        f.write(f'{depth * '\t'}\tauto&& pOperatorFunc = ({return_type_api} (*)({operator_func_args}))CoreAPI::Instance().GetFunction({function_index});\n')

        f.write(f'{depth * '\t'}\treturn pOperatorFunc(m_handle')
        f.write(''.join([(f', {parameter.name}' + ('.GetScriptHandle()' if not parameter.cpp_type.is_trivial else ''))
                         for parameter in operator.parameters]))
        f.write(');\n')

    f.write(f'{depth * '\t'}}}\n')


def generate_cpp_method(f: typing.IO, depth: int, function_index: int, scriptable_class: reflection_classes.ScriptableClass, method: reflection_classes.Method, code_structure: reflection_classes.CodeStructure):
    return_type_lib = make_correct_type_for_library(code_structure, method.return_type, True)
    return_type_api = make_correct_type_for_api(code_structure, method.return_type)

    f.write(f'{depth * '\t'}{return_type_lib} {'::'.join(scriptable_class.namespaces)}::{scriptable_class.alias}::{method.name}(')
    f.write(', '.join([f'{make_correct_type_for_library(code_structure, parameter.cpp_type)} {parameter.name}' for parameter in method.parameters]))
    f.write(f') {'const ' if method.is_const else ''}{{\n')

    method_func_args = f'{script_codegen_utils.SCRIPT_HANDLE_TYPE_NAME}' + ''.join([f', {make_correct_type_for_api(code_structure, parameter.cpp_type)}' for parameter in method.parameters])

    f.write(f'{depth * '\t'}\tauto&& pMethodFunc = ({return_type_api} (*)({method_func_args}))CoreAPI::Instance().GetFunction({function_index});\n')

    f.write(f'{depth * '\t'}\treturn pMethodFunc(m_handle')
    f.write(''.join([(f', {parameter.name}' + ('.GetScriptHandle()' if not parameter.cpp_type.is_trivial else ''))
                     for parameter in method.parameters]))
    f.write(');\n')

    f.write(f'{depth * '\t'}}}\n')


def generate_header_file(logger: logger_utils.Logger, f: typing.IO, function_index: int, scriptable_class: reflection_classes.ScriptableClass, code_structure: reflection_classes.CodeStructure):
    namespace_str = '::'.join(scriptable_class.namespaces)

    depth = 0

    f.write(f'{depth * '\t'}#include <CoreAPI.h>\n')
    f.write(f'{depth * '\t'}#include <CoreAPIFwd.h>\n\n')

    f.write(f'{depth * '\t'}namespace SpaRcleAPI::{namespace_str} {{\n')

    depth += 1

    # 0 - delete function
    # 1 - increment function
    # 2 - copy function
    delete_function_index = function_index
    increment_function_index = function_index + 1
    copy_function_index = function_index + 2

    function_index += 1 # increment function

    f.write(f'{depth * '\t'}class {scriptable_class.alias} {{\n')
    #f.write(f'{depth * '\t'}\tfriend class UnsafeRef<{scriptable_class.alias}>;\n')
    f.write(f'{depth * '\t'}public:\n')
    f.write(f'{depth * '\t'}\tstatic constexpr uint32_t API_DELETE_FUNCTION_INDEX = {delete_function_index};\n')
    f.write(f'{depth * '\t'}\tstatic constexpr uint32_t API_INCREMENT_FUNCTION_INDEX = {increment_function_index};\n')
    f.write(f'{depth * '\t'}\tstatic constexpr uint32_t API_COPY_FUNCTION_INDEX = {copy_function_index};\n\n')
    f.write(f'{depth * '\t'}public:\n')
    f.write(f'{depth * '\t'}\t{scriptable_class.alias}(const ScriptHandle& handle) /** NOLINT **/ \n')
    f.write(f'{depth * '\t'}\t\t: m_handle(handle)\n')
    f.write(f'{depth * '\t'}\t{{\n')
    f.write(f'{depth * '\t'}\t\tauto&& pIncrementFunc = (void (*)(ScriptHandle))CoreAPI::Instance().GetFunction(API_INCREMENT_FUNCTION_INDEX);\n')
    f.write(f'{depth * '\t'}\t\tpIncrementFunc(m_handle);\n')
    f.write(f'{depth * '\t'}\t}}\n\n')
    #f.write(f'{depth * '\t'}\t{scriptable_class.alias}(const ScriptHandle& handle, ScriptablePassKey<UnsafeRef<{scriptable_class.alias}>>)\n')
    #f.write(f'{depth * '\t'}\t\t: m_handle(handle) {{ }}\n\n')

    f.write(f'{depth * '\t'}\t{scriptable_class.alias}(const ScriptHandle& handle, SharedPtrUnmanagedPassKey) \n')
    f.write(f'{depth * '\t'}\t\t: m_handle(handle)\n')
    f.write(f'{depth * '\t'}\t{{ }}\n\n')

    f.write(f'{depth * '\t'}\t~{scriptable_class.alias}() {{\n')
    f.write(f'{depth * '\t'}\t\tauto&& pDeleteFunc = (void (*)(ScriptHandle))CoreAPI::Instance().GetFunction(API_DELETE_FUNCTION_INDEX);\n')
    f.write(f'{depth * '\t'}\t\tpDeleteFunc(m_handle);\n')
    f.write(f'{depth * '\t'}\t}}\n\n')
    f.write(f'{depth * '\t'}public:\n\n')

    if scriptable_class.has_copy_constructor:
        function_index += 1 # copy function

        f.write(f'{depth * '\t'}\t{scriptable_class.alias}(const {scriptable_class.alias}& other) {{\n')
        f.write(f'{depth * '\t'}\t\tauto&& pDeleteFunc = (void (*)(ScriptHandle))CoreAPI::Instance().GetFunction(API_DELETE_FUNCTION_INDEX);\n')
        f.write(f'{depth * '\t'}\t\tauto&& pIncrementFunc = (void (*)(ScriptHandle))CoreAPI::Instance().GetFunction(API_INCREMENT_FUNCTION_INDEX);\n')
        f.write(f'{depth * '\t'}\t\tauto&& pCopyFunc = (ScriptHandle (*)(ScriptHandle))CoreAPI::Instance().GetFunction(API_COPY_FUNCTION_INDEX);\n')
        f.write(f'{depth * '\t'}\t\tpDeleteFunc(m_handle);\n')
        f.write(f'{depth * '\t'}\t\tm_handle = pCopyFunc(other.m_handle);\n')
        f.write(f'{depth * '\t'}\t\tpIncrementFunc(m_handle);\n')
        f.write(f'{depth * '\t'}\t}}\n')

        f.write(f'{depth * '\t'}\t{scriptable_class.alias}& operator=(const {scriptable_class.alias}& other) {{\n')
        f.write(f'{depth * '\t'}\t\tauto&& pDeleteFunc = (void (*)(ScriptHandle))CoreAPI::Instance().GetFunction(API_DELETE_FUNCTION_INDEX);\n')
        f.write(f'{depth * '\t'}\t\tauto&& pIncrementFunc = (void (*)(ScriptHandle))CoreAPI::Instance().GetFunction(API_INCREMENT_FUNCTION_INDEX);\n')
        f.write(f'{depth * '\t'}\t\tauto&& pCopyFunc = (ScriptHandle (*)(ScriptHandle))CoreAPI::Instance().GetFunction(API_COPY_FUNCTION_INDEX);\n')
        f.write(f'{depth * '\t'}\t\tpDeleteFunc(m_handle);\n')
        f.write(f'{depth * '\t'}\t\tm_handle = pCopyFunc(other.m_handle);\n')
        f.write(f'{depth * '\t'}\t\tpIncrementFunc(m_handle);\n')
        f.write(f'{depth * '\t'}\t\treturn *this;\n')
        f.write(f'{depth * '\t'}\t}}\n')
    else:
        f.write(f'{depth * '\t'}\t{scriptable_class.alias}& operator=(const {scriptable_class.alias}&) = delete;\n')
        f.write(f'{depth * '\t'}\t{scriptable_class.alias}(const {scriptable_class.alias}&&) = delete;\n')

    function_index += len(scriptable_class.constructors) + len(scriptable_class.operators) + len(scriptable_class.methods)

    for i, constructor in enumerate(scriptable_class.constructors):
        generate_header_constructor(f, depth, scriptable_class, constructor, code_structure)

    for operator in scriptable_class.operators:
        generate_header_operator(f, depth, scriptable_class, operator, code_structure)

    for method in scriptable_class.methods:
        generate_header_method(f, depth, scriptable_class, method, code_structure)

    f.write(f'{depth * '\t'}public:\n')
    f.write(f'{depth * '\t'}\t[[nodiscard]] const ScriptHandle& GetScriptHandle() const {{ return m_handle; }}\n')
    f.write(f'{depth * '\t'}\tScriptHandle& GetScriptHandle() {{ return m_handle; }}\n\n')

    f.write(f'{depth * '\t'}private:\n')
    f.write(f'{depth * '\t'}\tScriptHandle m_handle;\n\n')

    f.write(f'\n{depth * '\t'}}};\n')

    depth -= 1

    f.write(f'{depth * '\t'}}}\n')


def generate_core_api_fwd_decl(logger: logger_utils.Logger, library_dir: str, code_structure: reflection_classes.CodeStructure):
    with open(library_dir + '/CoreAPIFwd.h', 'w', encoding='utf-8') as f:
        f.write(f'{clang_utils.codegen_cpp_header_comment}')

        f.write(f'#ifndef SR_ENGINE_SPARCLE_API_FWD_H\n')
        f.write(f'#define SR_ENGINE_SPARCLE_API_FWD_H\n\n')

        for scriptable_class in code_structure.scriptable_classes:
            f.write(f'namespace SpaRcleAPI::{'::'.join(scriptable_class.namespaces)} {{\n')
            f.write(f'\tclass {scriptable_class.alias};\n')
            f.write(f'}}\n\n')

        f.write(f'\n#endif /// SR_ENGINE_SPARCLE_API_FWD_H\n')


def generate_impl_cpp(logger: logger_utils.Logger, library_dir: str, code_structure: reflection_classes.CodeStructure):
    logger.log_info(f'Generating core library cpp file: {library_dir}/CoreAPIImpl.cpp')

    with open(library_dir + '/CoreAPIImpl.cpp', 'w', encoding='utf-8') as f:
        f.write(f'{clang_utils.codegen_cpp_header_comment}')

        f.write(f'#include <CppBehaviour.h>\n\n')

        function_index = 0

        for scriptable_class in code_structure.scriptable_classes:
            f.write(f'#include <{"/".join([namespace for namespace in scriptable_class.namespaces])}/{scriptable_class.alias}.h>\n')

        f.write('''
void FreeScriptBehaviour(void* pBehaviour) { delete reinterpret_cast<CppBehaviour*>(pBehaviour); }

void ScriptModuleSetBehaviourSceneObject(void* pInstance, ScriptHandle handle) {
    reinterpret_cast<CppBehaviour*>(pInstance)->sceneObject = handle;
}

void ScriptModuleBehaviourAwake(void* pInstance) { reinterpret_cast<CppBehaviour*>(pInstance)->Awake(); }
void ScriptModuleBehaviourOnEnable(void* pInstance) { reinterpret_cast<CppBehaviour*>(pInstance)->OnEnable(); }
void ScriptModuleBehaviourOnDisable(void* pInstance) { reinterpret_cast<CppBehaviour*>(pInstance)->OnDisable(); }
void ScriptModuleBehaviourOnAttached(void* pInstance) { reinterpret_cast<CppBehaviour*>(pInstance)->OnAttached(); }
void ScriptModuleBehaviourOnDetached(void* pInstance) { reinterpret_cast<CppBehaviour*>(pInstance)->OnDetached(); }
void ScriptModuleBehaviourOnDestroy(void* pInstance) { reinterpret_cast<CppBehaviour*>(pInstance)->OnDestroy(); }
void ScriptModuleBehaviourStart(void* pInstance) { reinterpret_cast<CppBehaviour*>(pInstance)->Start(); }
void ScriptModuleBehaviourFixedUpdate(void* pInstance) { reinterpret_cast<CppBehaviour*>(pInstance)->FixedUpdate(); }
void ScriptModuleBehaviourUpdate(void* pInstance, float_t dt) { reinterpret_cast<CppBehaviour*>(pInstance)->Update(dt); }
        \n''')

        f.write('namespace SpaRcleAPI {\n')

        f.write('''\tSR_NODISCARD CppBehaviour* CoreAPI::AllocateBehaviour(const char* behaviourName) {
        for (auto& module : m_scriptModules) {
            for (auto& behaviour : module.behaviours) {
                if (strcmp(behaviour.name, behaviourName) == 0) {
                    return reinterpret_cast<CppBehaviour*>(behaviour.allocateFunc());
                }
            }
        }
        return nullptr;
    }
    \n''')

        for scriptable_class in code_structure.scriptable_classes:
            increment_function_index = function_index + 1

            function_index += 1 # delete function
            function_index += 1 # increment function

            if scriptable_class.has_copy_constructor:
                function_index += 1 # copy function

            for constructor in scriptable_class.constructors:
                generate_cpp_constructor(f, 1, function_index, increment_function_index, scriptable_class, constructor, code_structure)
                function_index += 1

            for operator in scriptable_class.operators:
                generate_cpp_operator(f, 1, function_index, scriptable_class, operator, code_structure)
                function_index += 1

            for method in scriptable_class.methods:
                generate_cpp_method(f, 1, function_index, scriptable_class, method, code_structure)
                function_index += 1

        f.write('}\n')


def generate_behaviour_header(logger: logger_utils.Logger, repo_dir: str, library_dir: str):
    header_file_path = f'{library_dir}/CppBehaviour.h'
    logger.log_info(f'Generating core library file: {header_file_path}')

    with open(header_file_path, 'w', encoding='utf-8') as f:
        f.write(f'{clang_utils.codegen_cpp_header_comment}')

        f.write(f'#ifndef SR_ENGINE_SPARCLE_API_CPP_BEHAVIOUR_H\n')
        f.write(f'#define SR_ENGINE_SPARCLE_API_CPP_BEHAVIOUR_H\n\n')

        f.write(f'#include <CoreAPI.h>\n')
        f.write(f'#include <SpaRcle/Utils/SceneObject.h>\n\n')

        f.write('namespace SpaRcleAPI {\n')

        f.write('''\tclass CppBehaviour {
    public:
        CppBehaviour() = default;
        virtual ~CppBehaviour() = default;

        CppBehaviour(const CppBehaviour&) = delete;
        CppBehaviour(CppBehaviour&&) = delete;

        CppBehaviour& operator=(const CppBehaviour&) = delete;
        CppBehaviour& operator=(CppBehaviour&&) = delete;

    public:
        virtual void Awake() { }
        virtual void OnEnable() { }
        virtual void OnDisable() { }
        virtual void OnAttached() { }
        virtual void OnDetached() { }
        virtual void OnDestroy() { }
        virtual void Start() { }
        virtual void Update(float_t dt) { }
        virtual void FixedUpdate() { }

    public:
        SharedPtr<SpaRcle::Utils::SceneObject> sceneObject;

    };\n''')

        f.write('}\n\n')

        f.write(f'#endif /// SR_ENGINE_SPARCLE_API_CPP_BEHAVIOUR_H\n\n')


def generate_library(logger: logger_utils.Logger, repo_dir: str, library_dir: str, code_structure: reflection_classes.CodeStructure):
    logger.log_info('Start generating script library...')
    logger.log_info(f'Library directory: {library_dir}')

    # check if library_dir inside repo_dir
    if not library_dir.startswith(repo_dir):
        logger.log_fatal_error(f'Library directory "{library_dir}" is not inside repo directory "{repo_dir}". Destructive operation!')
        return
    else:
        logger.log_check(f'Library directory "{library_dir}" is inside repo directory "{repo_dir}".')

    delete_old_library(logger, library_dir)

    os.makedirs(library_dir + '/SpaRcle', exist_ok=True)

    generate_behaviour_header(logger, repo_dir, library_dir)
    generate_core_api_fwd_decl(logger, library_dir, code_structure)

    with open(repo_dir + '/CI/Codegen/ScriptHandle.h', 'r', encoding='utf-8') as core_api_header:
        with open(library_dir + '/ScriptHandle.h', 'w', encoding='utf-8') as f:
            logger.log_info(f'Generating core library file: {library_dir}/SpaRcle/ScriptHandle.h')
            f.write(f'{clang_utils.codegen_cpp_header_comment}')
            for line in core_api_header:
                f.write(line)

    with open(library_dir + '/CoreAPI.h', 'w', encoding='utf-8') as f:
        logger.log_info(f'Generating core library file: {library_dir}/CoreAPI.h')
        f.write(f'{clang_utils.codegen_cpp_header_comment}')

        include_guard_name = 'SR_ENGINE_SPARCLE_API_' + re.sub(r'(?<!^)(?=[A-Z])', '_', 'CoreAPI').upper() + '_H'

        f.write(f'#ifndef {include_guard_name}\n')
        f.write(f'#define {include_guard_name}\n\n')

        with open(repo_dir + '/CI/Codegen/SpaRcleAPI.h', 'r', encoding='utf-8') as core_api_header:
            for line in core_api_header:
                f.write(line)

        f.write(f'\n\n')
        f.write(f'#endif /// {include_guard_name}\n')

    function_index = 0

    for scriptable_class in code_structure.scriptable_classes:
        logger.log_info(f'Generating script library for class: {scriptable_class.alias}')

        file_path = f'{library_dir}/{'/'.join([namespace for namespace in scriptable_class.namespaces])}/{scriptable_class.alias}'
        logger.log_info(f'Library file path: {file_path}')

        os.makedirs(os.path.dirname(file_path), exist_ok=True)

        with open(file_path + '.h', 'w', encoding='utf-8') as f:
            f.write(f'{clang_utils.codegen_cpp_header_comment}')

            # upper string and split words by '_' (For example: source StringAtom -> SR_ENGINE_SPARCLE_API_STRING_ATOM_H)
            include_guard_name = 'SR_ENGINE_SPARCLE_API_' + re.sub(r'(?<!^)(?=[A-Z])', '_', scriptable_class.alias).upper() + '_H'

            f.write(f'#ifndef {include_guard_name}\n')
            f.write(f'#define {include_guard_name}\n\n')

            generate_header_file(logger, f, function_index, scriptable_class, code_structure)

            function_index += 1 # delete function
            function_index += 1 # increment function

            if scriptable_class.has_copy_constructor:
                function_index += 1 # copy function

            function_index += len(scriptable_class.constructors)
            function_index += len(scriptable_class.operators)
            function_index += len(scriptable_class.methods)

            f.write(f'\n')
            f.write(f'#endif /// {include_guard_name}\n')

    generate_impl_cpp(logger, library_dir, code_structure)



