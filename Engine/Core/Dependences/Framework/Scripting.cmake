

set(SCRIPTING_SRC
        ${FRAMEWORK_ROOT_DIR}/Scripting/src/Base/Script.cpp
        ${FRAMEWORK_ROOT_DIR}/Scripting/src/Base/Compiler.cpp

        ${FRAMEWORK_ROOT_DIR}/Scripting/src/Impl/EvoCompiler.cpp
        ${FRAMEWORK_ROOT_DIR}/Scripting/src/Impl/EvoScriptImpl.cpp
        )

set(SCRIPTING_INC_PUBLIC
        ${FRAMEWORK_ROOT_DIR}/Scripting/inc
        ${FRAMEWORK_ROOT_DIR}/Depends/lua/upstream
        ${FRAMEWORK_ROOT_DIR}/Depends/LuaBridge/Source

        ${FRAMEWORK_ROOT_DIR}/Depends/EvoScript/Core/inc
        )

set(SCRIPTING_INC_PRIVATE

        )

set(SCRIPTING_INC_INSTANCE

        )
