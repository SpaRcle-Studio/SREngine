set(SR_CODEGEN_SCRIPT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../CI/scripts/codegen.py")

message(STATUS "Running codegen script: ${SR_CODEGEN_SCRIPT_PATH}")

execute_process(
    COMMAND ${SR_PYTHON_EXECUTABLE} ${SR_CODEGEN_SCRIPT_PATH} ${SR_CMAKE_ROOT_BUILD_DIRECTORY}
    RESULT_VARIABLE result
    OUTPUT_VARIABLE output
    ERROR_VARIABLE error_output
)

if (result EQUAL 0)
    message(STATUS "Codegen script executed successfully:\n${output}")
else()
    message(FATAL_ERROR "Codegen script execution failed with error:\n${error_output}")
endif()