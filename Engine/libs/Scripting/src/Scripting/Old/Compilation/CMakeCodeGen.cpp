//
// Created by innerviewer on 10/10/2023.
//

#include <EvoScript/Compilation/CMakeCodeGen.h>

#include <EvoScript/Tools/StringUtils.h>
#include <EvoScript/Tools/Debug.h>
#include <EvoScript/Tools/FileSystem.h>

namespace EvoScript {
    bool CMakeCodeGen::GenerateCMakeLists(const std::string& resourcesPath) {
        std::string cmakePath = resourcesPath + "/Cache/Scripts/CMakeLists.txt";
        std::ofstream cmakeFile(cmakePath);
        if (!cmakeFile.is_open()) {
            ES_ERROR("CMakeCodeGen::GenerateCMakeLists() : failed to create CMake file! \n\tPath: " + cmakePath);
            return false;
        }

        cmakeFile <<
                  "# Created by Evo Script code generator on " + Tools::GetDate() + " | Author - innerviewer\n\n" +

                  "cmake_minimum_required(VERSION 3.16...3.16.2)\n" +
                  "project(CMakeScripts)\n" +
                  "\nset(CMAKE_CXX_STANDARD 20)\n\n" +
                  "add_library(Scripts STATIC Scripts.cxx)\n\n" +
                  "target_include_directories(Scripts PUBLIC .)\n" +
                  "target_include_directories(Scripts PUBLIC ../../)\n";

        cmakeFile.close();

        return true;
    }

    bool CMakeCodeGen::GenerateCxxFile(const std::string& resourcesPath) {
        std::string cxxPath = resourcesPath + "/Cache/Scripts/Scripts.cxx";
        std::ofstream cxxFile(cxxPath);
        if (!cxxFile.is_open()) {
            ES_ERROR("CMakeCodeGen::GenerateCxxFile() : failed to create CXX file! \n\tPath: " + cxxPath);
            return false;
        }

        cxxFile << "//\n// Created by Evo Script code generator on " + Tools::GetDate() + " | Author - innerviewer\n//\n\n";

        Tools::ForEachInDirWithExtRecursive(resourcesPath, ".cpp", [&cxxFile](const std::string& path){
            cxxFile << "#include \"" + path + "\"\n";
        });

        cxxFile.close();

        return true;
    }

    bool CMakeCodeGen::Generate(const std::string& resourcesPath) {
        if (!GenerateCxxFile(resourcesPath)) {
            return false;
        }

        if (!GenerateCMakeLists(resourcesPath)) {
            return false;
        }

        return true;
    }
}