message(STATUS "Post build script: ${CMAKE_BINARY_DIR}")

macro(SRCopyFileToAppInternal dir file)
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

    if(EXISTS "${CMAKE_BINARY_DIR}/lib/${file}")
        message(STATUS "Copy file ${CMAKE_BINARY_DIR}/lib/${file}")

        file(COPY ${CMAKE_BINARY_DIR}/lib/${file} DESTINATION ${CMAKE_BINARY_DIR}/Engine/Debug)
        file(COPY ${CMAKE_BINARY_DIR}/lib/${file} DESTINATION ${CMAKE_BINARY_DIR}/Engine/Release)
        file(COPY ${CMAKE_BINARY_DIR}/lib/${file} DESTINATION ${CMAKE_BINARY_DIR}/Engine)
    endif()

    if(EXISTS "${CMAKE_BINARY_DIR}/lib/Release/${file}")
        message(STATUS "Copy file ${CMAKE_BINARY_DIR}/lib/${file}")

        file(COPY ${CMAKE_BINARY_DIR}/lib/Release/${file} DESTINATION ${CMAKE_BINARY_DIR}/Engine/Debug)
        file(COPY ${CMAKE_BINARY_DIR}/lib/Release/${file} DESTINATION ${CMAKE_BINARY_DIR}/Engine/Release)
        file(COPY ${CMAKE_BINARY_DIR}/lib/Release/${file} DESTINATION ${CMAKE_BINARY_DIR}/Engine)
    endif()

    if(EXISTS "${CMAKE_BINARY_DIR}/lib/Debug/${file}")
        message(STATUS "Copy file ${CMAKE_BINARY_DIR}/lib/${file}")

        file(COPY ${CMAKE_BINARY_DIR}/lib/Debug/${file} DESTINATION ${CMAKE_BINARY_DIR}/Engine/Debug)
        file(COPY ${CMAKE_BINARY_DIR}/lib/Debug/${file} DESTINATION ${CMAKE_BINARY_DIR}/Engine/Release)
        file(COPY ${CMAKE_BINARY_DIR}/lib/Debug/${file} DESTINATION ${CMAKE_BINARY_DIR}/Engine)
    endif()
endmacro()

macro(SRCopyFileToApp dir file)
    SRCopyFileToAppInternal(${dir} ${file})
    SRCopyFileToAppInternal(${dir} lib${file})
endmacro()

SRCopyFileToApp("Engine/Core/libs/Graphics/EvoVulkan/Core" "EvoVulkan.dll")
SRCopyFileToApp("Engine/Core/libs/Graphics/EvoVulkan/Core" "EvoVulkand.dll")

SRCopyFileToApp("Engine/Core/libs/Utils/libs/assimp/bin" "assimp-vc142-mtd.dll")
SRCopyFileToApp("Engine/Core/libs/Utils/libs/assimp/bin" "assimp-vc142-mtdd.dll")

SRCopyFileToApp("Engine/Core/libs/Physics/extern/physx/bin/win.x86_64.vc142.md/debug" "PhysXd.dll")
SRCopyFileToApp("Engine/Core/libs/Physics/extern/physx/bin/win.x86_64.vc142.md/debug" "PhysXCookingd.dll")
SRCopyFileToApp("Engine/Core/libs/Physics/extern/physx/bin/win.x86_64.vc142.md/debug" "PhysXCommond.dll")
SRCopyFileToApp("Engine/Core/libs/Physics/extern/physx/bin/win.x86_64.vc142.md/debug" "PhysXFoundationd.dll")

SRCopyFileToApp("Engine/Core/libs/Utils" "Utils.dll")
SRCopyFileToApp("Engine/Core/libs/Utils" "Utilsd.dll")

SRCopyFileToApp("Engine/Core/libs/Audio/libs/OpenAL" "OpenAL32.dll")
SRCopyFileToApp("Engine/Core/libs/Audio/libs/OpenAL" "OpenAL64.dll")
SRCopyFileToApp("Engine/Core/libs/Audio/libs/OpenAL" "OpenAL32d.dll")
SRCopyFileToApp("Engine/Core/libs/Audio/libs/OpenAL" "OpenAL64d.dll")

SRCopyFileToApp("lib" "freetype.dll")
SRCopyFileToApp("lib" "freetyped.dll")

SRCopyFileToApp("bin" "glew32.dll")
SRCopyFileToApp("bin" "glew32d.dll")
