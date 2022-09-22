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

SRCopyFileToApp("Engine/Core/libs/Graphics/EvoVulkan/Core" "libEvoVulkan.dll")
SRCopyFileToApp("Engine/Core/libs/Graphics/EvoVulkan/Core" "libEvoVulkand.dll")
SRCopyFileToApp("Engine/Core/libs/Graphics/EvoVulkan/Core" "EvoVulkan.dll")
SRCopyFileToApp("Engine/Core/libs/Graphics/EvoVulkan/Core" "EvoVulkand.dll")

SRCopyFileToApp("Engine/Core/libs/Utils/libs/assimp/bin" "libassimp-vc142-mtd.dll")
SRCopyFileToApp("Engine/Core/libs/Utils/libs/assimp/bin" "libassimp-vc142-mtdd.dll")
SRCopyFileToApp("Engine/Core/libs/Utils/libs/assimp/bin" "assimp-vc142-mtd.dll")
SRCopyFileToApp("Engine/Core/libs/Utils/libs/assimp/bin" "assimp-vc142-mtdd.dll")

SRCopyFileToApp("Engine/Core/libs/Utils" "Utils.dll")
SRCopyFileToApp("Engine/Core/libs/Utils" "Utilsd.dll")
SRCopyFileToApp("Engine/Core/libs/Utils" "libUtils.dll")
SRCopyFileToApp("Engine/Core/libs/Utils" "libUtilsd.dll")

SRCopyFileToApp("Engine/Core/libs/Audio/libs/OpenAL" "OpenAL32.dll")
SRCopyFileToApp("Engine/Core/libs/Audio/libs/OpenAL" "OpenAL64.dll")
SRCopyFileToApp("Engine/Core/libs/Audio/libs/OpenAL" "OpenAL32d.dll")
SRCopyFileToApp("Engine/Core/libs/Audio/libs/OpenAL" "OpenAL64d.dll")

SRCopyFileToApp("bin" "glew32.dll")
SRCopyFileToApp("bin" "glew32d.dll")
