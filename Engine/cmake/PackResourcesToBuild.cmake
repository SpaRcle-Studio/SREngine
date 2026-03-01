set(SR_PACK_RESOURCES_SCRIPT_PATH "${SR_CMAKE_ROOT_SOURCE_DIRECTORY}/CI/scripts/pack_resources.py")

macro(SRPackResourcesToBuild)
    message(STATUS "Compiling pack resources script: ${SR_PACK_RESOURCES_SCRIPT_PATH}")

    execute_process(
        COMMAND ${SR_PYTHON_EXECUTABLE} -m PyInstaller --onefile ${SR_PACK_RESOURCES_SCRIPT_PATH}
        --distpath "${SR_CMAKE_RESOURCES_DIRECTORY}/Engine/Utilities"
        --paths "${SR_CMAKE_ROOT_SOURCE_DIRECTORY}/CI/scripts"
        --specpath ${CMAKE_CURRENT_BINARY_DIR}
        --workpath ${CMAKE_CURRENT_BINARY_DIR}/pyi_build
        RESULT_VARIABLE result
        OUTPUT_VARIABLE output
        ERROR_VARIABLE error_output
    )

    if (result EQUAL "0")
        message(STATUS "Pack resources script compiled successfully:\n${output}")
    else()
        message(FATAL_ERROR "Pack resources script compilation failed with error:\n${error_output}")
    endif()

    if (SR_HOST_SYSTEM_UNIX)
        set(SR_PACK_RESOURCES_EXECUTABLE_SCRIPT "${SR_CMAKE_RESOURCES_DIRECTORY}/Engine/Utilities/pack_resources")
    else()
        set(SR_PACK_RESOURCES_EXECUTABLE_SCRIPT "${SR_CMAKE_RESOURCES_DIRECTORY}/Engine/Utilities/pack_resources.exe")
    endif()

    if (NOT EXISTS "${SR_PACK_RESOURCES_EXECUTABLE_SCRIPT}")
        message(FATAL_ERROR "Pack resources script not found at: ${SR_PACK_RESOURCES_EXECUTABLE_SCRIPT}")
    endif()

    message(STATUS "Executing pack resources script: ${SR_PACK_RESOURCES_EXECUTABLE_SCRIPT}")

    execute_process(
        COMMAND ${SR_PACK_RESOURCES_EXECUTABLE_SCRIPT}
        --root_build_dir "${SR_CMAKE_ROOT_BUILD_DIRECTORY}"
        --repo_dir "${SR_CMAKE_ROOT_SOURCE_DIRECTORY}"
        --platform "${SR_ENGINE_PLATFORM}"
        RESULT_VARIABLE result
        OUTPUT_VARIABLE output
        ERROR_VARIABLE error_output
    )

    if (result EQUAL "0")
        message(STATUS "Pack resources script executed successfully:\n${output}")
    else()
        message(FATAL_ERROR "Pack resources script execution failed with error:\n${error_output}\n${result}")
    endif()
endmacro()
