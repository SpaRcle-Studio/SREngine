//
// Created by Kiper220 on 21.11.2020.
//

#include <FileSystem/FileSystem.h>

namespace Framework::Helper::FS {
            void FileSystem::Init(){
                FileSystem::g_applicationDirectory = PlatformGetApplicationDirectory();
            }

            std::string FileSystem::PlatformGetApplicationDirectory() {
                return "TODO: Make this method! From PlatformGetApplicationDirectory();";
            }

            const std::string & FileSystem::GetApplicationDirectory() {


                return FileSystem::g_applicationDirectory;
            }

            bool FileSystem::FileExists(const std::string &filePath) {
                return false;
            }

            bool FileSystem::DirectoryExists(const std::string &filePath) {
                return false;
            }
        }