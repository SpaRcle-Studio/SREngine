import typing, os, re
import reflection_classes, clang_utils, logger_utils, cpp_operator, script_api_code_generator, script_codegen_utils


def delete_old_library(logger: logger_utils.Logger, library_dir: str):
    if os.path.isdir(library_dir):
        logger.log_info(f'Delete old library directory: {library_dir}')

        files_to_delete = []
        for root, dirs, files in os.walk(library_dir):
            for file in files:
                if file.endswith('.h'):
                    files_to_delete.append(os.path.join(root, file))
                else:
                    logger.log_fatal_error(f'File "{file}" is not a header file. Destructive operation!')
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


def generate_header_file(logger: logger_utils.Logger, f: typing.IO, function_index: int, scriptable_class: reflection_classes.ScriptableClass, code_structure: reflection_classes.CodeStructure):
    namespace_str = '::'.join(scriptable_class.namespaces)

    depth = 0

    f.write(f'{depth * '\t'}#include <CoreAPI.h>\n\n')
    f.write(f'{depth * '\t'}namespace SpaRcleAPI::{namespace_str} {{\n')

    depth += 1

    f.write(f'{depth * '\t'}class {scriptable_class.alias} {{\n')
    f.write(f'{depth * '\t'}public:\n')

    f.write(f'{depth * '\t'}\t~{scriptable_class.alias}() {{\n')
    f.write(f'{depth * '\t'}\t\tauto&& pDeleteFunc = (void (*)(ScriptHandle))CoreAPI::Instance().GetFunction({function_index});\n')
    f.write(f'{depth * '\t'}\t\tpDeleteFunc(m_handle);\n')
    f.write(f'{depth * '\t'}\t}}\n')

    function_index += 1

    f.write(f'{depth * '\t'}\t{scriptable_class.alias}(const {scriptable_class.alias}& other) {{\n')
    f.write(f'{depth * '\t'}\t\tauto&& pDeleteFunc = (void (*)(ScriptHandle))CoreAPI::Instance().GetFunction({function_index});\n')
    f.write(f'{depth * '\t'}\t\tpDeleteFunc(m_handle);\n')
    f.write(f'{depth * '\t'}\t\tm_handle = other.m_handle;\n')
    f.write(f'{depth * '\t'}\t\t(*m_handle.pRefCount)++;\n')
    f.write(f'{depth * '\t'}\t}}\n')

    f.write(f'{depth * '\t'}\t{scriptable_class.alias}& operator=(const {scriptable_class.alias}& other) {{\n')
    f.write(f'{depth * '\t'}\t\tauto&& pDeleteFunc = (void (*)(ScriptHandle))CoreAPI::Instance().GetFunction({function_index});\n')
    f.write(f'{depth * '\t'}\t\tpDeleteFunc(m_handle);\n')
    f.write(f'{depth * '\t'}\t\tm_handle = other.m_handle;\n')
    f.write(f'{depth * '\t'}\t\t(*m_handle.pRefCount)++;\n')
    f.write(f'{depth * '\t'}\t\treturn *this;\n')
    f.write(f'{depth * '\t'}\t}}\n')

    for i, constructor in enumerate(scriptable_class.constructors):
        f.write(f'{depth * '\t'}\t{scriptable_class.alias}(')
        f.write(', '.join([f'{parameter.type_name} {parameter.name}' for parameter in constructor.parameters]))
        f.write(') {\n')

        f.write(f'{depth * '\t'}\t\tusing ConstructorFunc = {script_codegen_utils.SCRIPT_HANDLE_TYPE_NAME} (*)(')
        f.write(', '.join([f'{parameter.type_name}' for parameter in constructor.parameters]))
        f.write(');\n')

        f.write(f'{depth * '\t'}\t\tauto&& pConstructorFunc = (ConstructorFunc)CoreAPI::Instance().GetFunction({function_index});\n')
        f.write(f'{depth * '\t'}\t\tm_handle = pConstructorFunc(')
        f.write(', '.join([parameter.name for parameter in constructor.parameters]))
        f.write(');\n')
        f.write(f'{depth * '\t'}\t\t(*m_handle.pRefCount) = 1;\n')

        f.write(f'{depth * '\t'}\t}}\n')

        function_index += 1

    # TODO: add operator overloads
    function_index += len(scriptable_class.operators)

    for method in scriptable_class.methods:
        is_return_type_trivial, return_type = clang_utils.correct_return_type(method.return_type, code_structure)

        f.write(f'{depth * '\t'}\t{return_type} {method.name}(')
        f.write(', '.join([f'{parameter.type_name} {parameter.name}' for parameter in method.parameters]))
        f.write(') {\n')
        f.write(f'{depth * '\t'}\t\tusing MethodFunc = {return_type} (*)({script_codegen_utils.SCRIPT_HANDLE_TYPE_NAME}')
        f.write(''.join([f', {parameter.type_name}' for parameter in method.parameters]))
        f.write(');\n')
        f.write(f'{depth * '\t'}\t\tauto&& pMethodFunc = (MethodFunc)CoreAPI::Instance().GetFunction({function_index});\n')
        f.write(f'{depth * '\t'}\t\treturn pMethodFunc(m_handle')
        f.write(''.join([f', {parameter.name}' for parameter in method.parameters]))
        f.write(');\n')
        f.write(f'{depth * '\t'}\t}}\n')

        function_index += 1

    f.write(f'{depth * '\t'}private:\n')
    f.write(f'{depth * '\t'}\tScriptHandle m_handle;\n')

    f.write(f'\n{depth * '\t'}}};\n')

    depth -= 1

    f.write(f'{depth * '\t'}}}\n')


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
            function_index += len(scriptable_class.constructors)
            function_index += len(scriptable_class.operators)
            function_index += len(scriptable_class.methods)

            f.write(f'\n')
            f.write(f'#endif /// {include_guard_name}\n')




