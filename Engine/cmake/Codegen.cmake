set(SR_CODEGEN_SCRIPT_PATH "${PROJECT_SOURCE_DIR}/../CI/scripts/codegen.py")

macro(SRCodegen)
message(STATUS "Running codegen script: ${SR_CODEGEN_SCRIPT_PATH}")
message(STATUS "Codegen script args: \"${SR_PYTHON_EXECUTABLE} ${SR_CODEGEN_SCRIPT_PATH} ${SR_CMAKE_ROOT_BUILD_DIRECTORY} ${SR_CMAKE_ROOT_SOURCE_DIRECTORY}\"")

execute_process(
    COMMAND ${SR_PYTHON_EXECUTABLE} ${SR_CODEGEN_SCRIPT_PATH} ${SR_CMAKE_ROOT_BUILD_DIRECTORY} ${SR_CMAKE_ROOT_SOURCE_DIRECTORY}
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
