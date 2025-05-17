set(SR_CODEGEN_SCRIPT_PATH "${SR_CMAKE_ROOT_SOURCE_DIRECTORY}/CI/scripts/codegen.py")
set(SR_COPY_LIBCLANG_SCRIPT_PATH "${SR_CMAKE_ROOT_SOURCE_DIRECTORY}/CI/scripts/copy_libclang_to_resources.py")

macro(SRCodegen)
    message(STATUS "Copy libclang to ${SR_CMAKE_RESOURCES_DIRECTORY}/Engine/Utilities")

    execute_process(
        COMMAND ${SR_PYTHON_EXECUTABLE} ${SR_COPY_LIBCLANG_SCRIPT_PATH}
        --repo_dir "${SR_CMAKE_ROOT_SOURCE_DIRECTORY}"
        RESULT_VARIABLE result
        OUTPUT_VARIABLE output
        ERROR_VARIABLE error_output
    )

    if (result EQUAL "0")
        message(STATUS "Libclang copied successfully:\n${output}")
    else()
        message(FATAL_ERROR "Libclang copy failed with error:\n${error_output}")
    endif()

    # compile codegen script

    message(STATUS "Compiling codegen script: ${SR_CODEGEN_SCRIPT_PATH}")

    execute_process(
        COMMAND ${SR_PYTHON_EXECUTABLE} -m PyInstaller --onefile ${SR_CODEGEN_SCRIPT_PATH}
        --distpath "${SR_CMAKE_RESOURCES_DIRECTORY}/Engine/Utilities"
        --paths "${SR_CMAKE_ROOT_SOURCE_DIRECTORY}/CI/scripts"
        RESULT_VARIABLE result
        OUTPUT_VARIABLE output
        ERROR_VARIABLE error_output
    )

    if (result EQUAL "0")
        message(STATUS "Codegen script compiled successfully:\n${output}")
    else()
        message(FATAL_ERROR "Codegen script compilation failed with error:\n${error_output}")
    endif()

    if (SR_HOST_SYSTEM_UNIX)
        set(SR_CODEGEN_EXECUTABLE_SCRIPT "${SR_CMAKE_RESOURCES_DIRECTORY}/Engine/Utilities/codegen")
    else()
        set(SR_CODEGEN_EXECUTABLE_SCRIPT "${SR_CMAKE_RESOURCES_DIRECTORY}/Engine/Utilities/codegen.exe")
    endif()

    if (NOT EXISTS "${SR_CODEGEN_EXECUTABLE_SCRIPT}")
        message(FATAL_ERROR "Codegen script not found at: ${SR_CODEGEN_EXECUTABLE_SCRIPT}")
    endif()

    # code generation script

    message(STATUS "Running codegen script: ${SR_CODEGEN_EXECUTABLE_SCRIPT}")
    message(STATUS "Codegen script args: ${SR_CODEGEN_EXECUTABLE_SCRIPT}
        --codegen_dir ${SR_CMAKE_ROOT_BUILD_DIRECTORY}
        --root_build_dir ${SR_CMAKE_ROOT_BUILD_DIRECTORY}
        --repo_dir ${SR_CMAKE_ROOT_SOURCE_DIRECTORY}
        --config_dir ${SR_CMAKE_RESOURCES_DIRECTORY}/Engine/Utilities
        --module_name \"Application\"")

    execute_process(
        COMMAND ${SR_CODEGEN_EXECUTABLE_SCRIPT}
        --codegen_dir "${SR_CMAKE_ROOT_BUILD_DIRECTORY}"
        --root_build_dir "${SR_CMAKE_ROOT_BUILD_DIRECTORY}"
        --repo_dir "${SR_CMAKE_ROOT_SOURCE_DIRECTORY}"
        --config_dir "${SR_CMAKE_RESOURCES_DIRECTORY}/Engine/Utilities"
        --module_name "Application"
        RESULT_VARIABLE result
        OUTPUT_VARIABLE output
        ERROR_VARIABLE error_output
    )

    if (result EQUAL "0")
        message(STATUS "Codegen script executed successfully:\n${output}")
    else()
        message(FATAL_ERROR "Codegen script execution failed with error:\n${error_output}")
    endif()
endmacro()
