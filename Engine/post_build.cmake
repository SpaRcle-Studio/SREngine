message(STATUS "Post build script: ${CMAKE_BINARY_DIR}")

macro(SRCopyFileToApp dir file)
    message(STATUS "SRCopyFileToApp: target = ${file}")

    if(EXISTS "${CMAKE_BINARY_DIR}/${dir}/${file}")
        message(STATUS "Copy file ${CMAKE_BINARY_DIR}/${dir}/${file}")

        file(COPY ${CMAKE_BINARY_DIR}/${dir}/${file} DESTINATION ${CMAKE_BINARY_DIR}/Engine/Debug)
        file(COPY ${CMAKE_BINARY_DIR}/${dir}/${file} DESTINATION ${CMAKE_BINARY_DIR}/Engine/Release)
        file(COPY ${CMAKE_BINARY_DIR}/${dir}/${file} DESTINATION ${CMAKE_BINARY_DIR}/Engine)
    endif()

    if(EXISTS "${CMAKE_BINARY_DIR}/${dir}/Debug/${file}")
        message(STATUS "Copy file ${CMAKE_BINARY_DIR}/${dir}/Debug/${file}")

        file(COPY ${CMAKE_BINARY_DIR}/${dir}/Debug/${file} DESTINATION ${CMAKE_BINARY_DIR}/Engine/Debug)
        file(COPY ${CMAKE_BINARY_DIR}/${dir}/Debug/${file} DESTINATION ${CMAKE_BINARY_DIR}/Engine/Release)
        file(COPY ${CMAKE_BINARY_DIR}/${dir}/Debug/${file} DESTINATION ${CMAKE_BINARY_DIR}/Engine)
    endif()

    if(EXISTS "${CMAKE_BINARY_DIR}/${dir}/Release/${file}")
        message(STATUS "Copy file ${CMAKE_BINARY_DIR}/${dir}/Release/${file}")

        file(COPY ${CMAKE_BINARY_DIR}/${dir}/Release/${file} DESTINATION ${CMAKE_BINARY_DIR}/Engine/Debug)
        file(COPY ${CMAKE_BINARY_DIR}/${dir}/Release/${file} DESTINATION ${CMAKE_BINARY_DIR}/Engine/Release)
        file(COPY ${CMAKE_BINARY_DIR}/${dir}/Release/${file} DESTINATION ${CMAKE_BINARY_DIR}/Engine)
    endif()
endmacro()

SRCopyFileToApp("Engine/Core/Dependences/Framework/Depends/EvoVulkan/Core" "libEvoVulkan.dll")
SRCopyFileToApp("Engine/Core/Dependences/Framework/Depends/EvoVulkan/Core" "libEvoVulkand.dll")
SRCopyFileToApp("Engine/Core/Dependences/Framework/Depends/EvoVulkan/Core" "EvoVulkan.dll")
SRCopyFileToApp("Engine/Core/Dependences/Framework/Depends/EvoVulkan/Core" "EvoVulkand.dll")

SRCopyFileToApp("Engine/Core/Dependences/Framework/Utils" "Utils.dll")
SRCopyFileToApp("Engine/Core/Dependences/Framework/Utils" "Utilsd.dll")
SRCopyFileToApp("Engine/Core/Dependences/Framework/Utils" "libUtils.dll")
SRCopyFileToApp("Engine/Core/Dependences/Framework/Utils" "libUtilsd.dll")

SRCopyFileToApp("Engine/Core/Dependences/Framework/Depends/OpenAL" "OpenAL32.dll")
SRCopyFileToApp("Engine/Core/Dependences/Framework/Depends/OpenAL" "OpenAL64.dll")
SRCopyFileToApp("Engine/Core/Dependences/Framework/Depends/OpenAL" "OpenAL32d.dll")
SRCopyFileToApp("Engine/Core/Dependences/Framework/Depends/OpenAL" "OpenAL64d.dll")

SRCopyFileToApp("bin" "glew32.dll")
SRCopyFileToApp("bin" "glew32d.dll")
