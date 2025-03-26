add_library(Scripts STATIC TestScript.cpp)
target_include_directories(Scripts PUBLIC ${SR_CMAKE_ROOT_SOURCE_DIRECTORY}/Resources/SpaRcleAPI)