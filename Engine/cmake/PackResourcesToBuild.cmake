function(SRPackResourcesToBuild)
    file(GLOB_RECURSE SR_BROWSER_RESOURCE_INPUTS CONFIGURE_DEPENDS
        "${SR_CMAKE_RESOURCES_DIRECTORY}/*")
    set(SR_BROWSER_RESOURCE_STAMP "${SR_CMAKE_ROOT_BUILD_DIRECTORY}/PackedResources.stamp")
    set(SR_BROWSER_RESOURCE_MANIFEST "${CMAKE_CURRENT_BINARY_DIR}/BrowserResourceInputs.txt")
    string(REPLACE ";" "\n" SR_BROWSER_RESOURCE_INPUT_TEXT "${SR_BROWSER_RESOURCE_INPUTS}")
    file(GENERATE OUTPUT "${SR_BROWSER_RESOURCE_MANIFEST}" CONTENT "${SR_BROWSER_RESOURCE_INPUT_TEXT}\n")
    add_custom_command(OUTPUT "${SR_BROWSER_RESOURCE_STAMP}"
        COMMAND "${SR_PYTHON_EXECUTABLE}" "${SR_CMAKE_ROOT_SOURCE_DIRECTORY}/CI/scripts/pack_resources.py"
            --root_build_dir "${SR_CMAKE_ROOT_BUILD_DIRECTORY}"
            --repo_dir "${SR_CMAKE_ROOT_SOURCE_DIRECTORY}"
            --platform "${SR_ENGINE_PLATFORM}"
        COMMAND ${CMAKE_COMMAND} -E touch "${SR_BROWSER_RESOURCE_STAMP}"
        DEPENDS ${SR_BROWSER_RESOURCE_INPUTS}
            "${SR_BROWSER_RESOURCE_MANIFEST}"
            "${SR_CMAKE_ROOT_SOURCE_DIRECTORY}/CI/scripts/pack_resources.py"
            "${SR_CMAKE_ROOT_SOURCE_DIRECTORY}/CI/scripts/create_packing_mask_file.py"
            "${SR_CMAKE_ROOT_SOURCE_DIRECTORY}/CI/scripts/logger_utils.py"
        VERBATIM)
    add_custom_target(SRBrowserResources DEPENDS "${SR_BROWSER_RESOURCE_STAMP}")
endfunction()
