message(STATUS "Utils source directory: ${SR_UTILS_SOURCE_DIR}")
message(STATUS "Utils binary directory: ${SR_UTILS_BINARY_DIR}")

list(APPEND SR_UTILS_ALL_HEADERS ${SR_UTILS_SOURCE_DIR}/inc/Utils)

foreach(SR_UTILS_HEADER ${SR_UTILS_ALL_HEADERS})
   file(COPY ${SR_UTILS_HEADER} DESTINATION ${SR_UTILS_BINARY_DIR}/include)
endforeach()

# --------------------------------------------------------------------------------------

if (SR_ICU)
    list(APPEND SR_UTILS_ICU_ALL_HEADERS ${SR_UTILS_SOURCE_DIR}/libs/icu)

    foreach(SR_UTILS_ICU_HEADER ${SR_UTILS_ICU_ALL_HEADERS})
        file(COPY ${SR_UTILS_ICU_HEADER} DESTINATION ${SR_UTILS_BINARY_DIR}/include)
    endforeach()
endif()

# --------------------------------------------------------------------------------------

if (SR_TRACY_ENABLE)
    list(APPEND SR_UTILS_TRACY_ALL_HEADERS ${SR_UTILS_SOURCE_DIR}/libs/tracy)

    foreach(SR_UTILS_TRACY_HEADER ${SR_UTILS_TRACY_ALL_HEADERS})
        file(COPY ${SR_UTILS_TRACY_HEADER} DESTINATION ${SR_UTILS_BINARY_DIR}/include)
    endforeach()
endif()
