//
// Created by Kiper220 on 21.11.2020.
//

#ifndef GAMEENGINE_FILESYSTEM_H
#define GAMEENGINE_FILESYSTEM_H

#include <string>

namespace Framework::Helper::FS {
class FileSystem {
private:
    /** \brief This constructor can call only in this class */
    FileSystem() = delete;

    /** \brief Copy protection \warning This constructor is delete */
    FileSystem(const FileSystem &fileSystem) = delete;

    /** \brief Platform get application directory */
    static std::string PlatformGetApplicationDirectory();

        public:
    /** \brief Initialize global filesystem variables */
    static void Init();

    /** \brief Get string of application directory */
    static const std::string &GetApplicationDirectory();

    /** \brief Get information of file exists \return true if file exists, else false */
    static bool FileExists(const std::string& filePath);

    /** \brief Get information of directory exists \return true if file exists, else false */
    static bool DirectoryExists(const std::string& filePath);

        private:
    inline static std::string g_applicationDirectory = "FUCK YOU. I EMPTY";

};
}

#endif //GAMEENGINE_FILESYSTEM_H
