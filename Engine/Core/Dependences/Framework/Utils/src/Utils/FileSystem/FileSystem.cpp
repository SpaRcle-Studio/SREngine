//
// Created by Nikita on 16.11.2020.
//

#include <Utils/FileSystem/FileSystem.h>
#include <Utils/Debug.h>
#include <Utils/FileSystem/Path.h>
#include <Utils/Common/Hashes.h>
#include <Utils/Common/StringUtils.h>

/// TODO: move to platform class!

#ifdef SR_WIN32
    #include <Windows.h>
    #include <tchar.h>
    #include <shellapi.h>
    #include <commdlg.h>
    #include <shlobj.h>

    #ifdef SR_MINGW
        #include <ShObjIdl.h>
    #endif
#endif

namespace SR_UTILS_NS {
    bool FileSystem::Delete(const char *file) { return remove(file); }

    bool FileSystem::FileExists(const std::string& path) {
    #ifdef WIN32
        if (FILE* f = fopen(path.c_str(), "r")) {
            fclose(f);
            return true;
        }
        else
            return false;
    #else
        SR_ERROR("FileSystem::FileExists() : engine not support this function!");
        return false;
    #endif
    }

    std::string FileSystem::GetPathToExe() {
    #ifdef SR_WIN32
        const std::size_t buf_len = 260;
        auto s = new TCHAR[buf_len];
        auto path_len = GetModuleFileName(GetModuleHandle(nullptr), s, buf_len);
        return StringUtils::GetDirToFileFromFullPath(s);
    #else
        SR_ERROR("FileSystem::GetPathToExe() : linux not support this function!");
        return "NoDirectory";
    #endif
    }

    std::string FileSystem::GetFullPathToExe() {
    #ifdef SR_WIN32
        const std::size_t buf_len = 260;
        auto s = new TCHAR[buf_len];
        auto path_len = GetModuleFileName(GetModuleHandle(nullptr), s, buf_len);
        return s;
    #else
        Debug::Error("FileSystem::GetPathToExe() : linux not support this function!");
        return "NoDirectory";
    #endif
    }

    void FileSystem::UnmapFile(const char *str) {

    }

    const char *FileSystem::FileMapView(std::string path) {
        const char *data = nullptr;

    #ifdef WIN32

    #else

    #endif

        return data;
    }

    char* FileSystem::Load(std::string path) {
        /// open file
        std::ifstream infile(path);
        if (!infile.is_open()) {
            SR_ERROR("FileSystem::Load() : failed open file!\n\tPath: "+path);
            return nullptr;
        }


        /// get length of file
        infile.seekg(0, std::ios::end);
        size_t length = infile.tellg();
        infile.seekg(0, std::ios::beg);

        char* buffer = new char[length];

        /// read file
        infile.read(buffer, length);

        return buffer;
    }

    std::string FileSystem::GetExecutableFileName() {
    #ifdef SR_WIN32
        const std::size_t buf_len = 260;
        auto s = new TCHAR[buf_len];
        auto path_len = GetModuleFileName(GetModuleHandle(nullptr), s, buf_len);
        return StringUtils::GetFileNameFromFullPath(s);
    #else
        return "Unsupported function";
    #endif
    }

    void FileSystem::Reload() {
    #ifdef SR_WIN32
        std::string exe = GetFullPathToExe();
        ShellExecute(NULL, "open", exe.c_str(), NULL, NULL, SW_SHOWDEFAULT);
    #endif
    }

    std::string FileSystem::ReadAllText(const std::string &path) {
        std::string data = std::string();
        std::ifstream stream(path, std::ios::in);
        if (stream.is_open()) {
            std::string line;
            bool first = false;
            while (getline(stream, line)) {
                if (!first) {
                    first = true;
                    data += line;
                }
                else
                    data += "\n" + line;
            }
            stream.close();
        }
        return data;
    }

    std::vector<char> FileSystem::ReadBinary(const std::string &path) {
        /*std::ifstream ifd(path,  std::ios::binary |  std::ios::ate);
        int size = ifd.tellg();
        ifd.seekg(0,  std::ios::beg);
        std::vector<char> buffer;
        buffer.resize(size); // << resize not reserve
        ifd.read(buffer.data(), size);*/

        //std::ifstream input(path, std::ios::binary);
        //std::vector<uint32_t> buffer(std::istreambuf_iterator<char>(input), {});

        std::ifstream file(path, std::ios::ate | std::ios::binary);

        if (!file.is_open()) {
            SR_ERROR("FileSystem::ReadBinary() : failed to open \""+path+"\"file!");
            return std::vector<char>();
        }

        size_t fileSize = (size_t) file.tellg();
        std::vector<char> buffer(fileSize);

        file.seekg(0);
        file.read(buffer.data(), fileSize);

        file.close();

        return buffer;
    }

    bool FileSystem::CreateFolder(const std::string &path) {
    #ifdef SR_MINGW
        return mkdir(path.c_str());
    #else
        return _mkdir(path.c_str());
    #endif
    }

    std::string FileSystem::GetFullPath(const std::string& path) {
    #ifdef SR_WIN32
        char fullFilename[MAX_PATH];
        GetFullPathName(path.c_str(), MAX_PATH, fullFilename, nullptr);
        return std::string(fullFilename);
    #else
        return std::string();
    #endif
    }

    std::string FileSystem::NormalizePath(const std::string &path) {
        auto newPath = StringUtils::MakePath(path);

        do {
            auto pos = newPath.find("/..");
            if (pos == std::string::npos)
                break;

            auto splash = newPath.rfind('/', pos - 1);
            if (splash == std::string::npos)
                break;

            newPath = newPath.erase(splash + 1, (pos - splash) + 3);
        } while(true);

        return newPath;
    }

    std::vector<Path> FileSystem::GetFilesInDir(const std::string& path) {
        std::vector<Path> files;
    #ifdef SR_WIN32
        const std::string search_path = path + "/*.*";
        WIN32_FIND_DATA fd;
        HANDLE hFind = ::FindFirstFile(search_path.c_str(), &fd);
        if(hFind != INVALID_HANDLE_VALUE) {
            do {
                // read all (real) files in current folder
                // , delete '!' read other 2 default folder . and ..
                if (!(static_cast<unsigned>(fd.dwFileAttributes) & static_cast<uint64_t>(FILE_ATTRIBUTE_DIRECTORY))) {
                    files.emplace_back(path + "/" + std::string(fd.cFileName));
                }
            } while(::FindNextFile(hFind, &fd));

            ::FindClose(hFind);
        }
    #endif
        return files;
    }

    std::vector<Path> FileSystem::GetDirectoriesInDir(const std::string &path) {
        std::vector<Path> folders;
    #ifdef SR_WIN32
        const std::string search_path = path + "/*.*";
        WIN32_FIND_DATA fd;
        HANDLE hFind = ::FindFirstFile(search_path.c_str(), &fd);
        if(hFind != INVALID_HANDLE_VALUE) {
            do {
                // read all (real) files in current folder
                // , delete '!' read other 2 default folder . and ..
                if ((fd.dwFileAttributes & static_cast<uint64_t>(FILE_ATTRIBUTE_DIRECTORY))) {
                    const auto filename = std::string(fd.cFileName);
                    const auto folder = path + "/" + filename;
                    if (filename != "." && filename != ".." && !filename.empty())
                        folders.emplace_back(folder);
                }
            } while(::FindNextFile(hFind, &fd));

            ::FindClose(hFind);
        }
    #endif
        return folders;
    }

    std::vector<Path> FileSystem::GetAllInDir(const Path &path) {
        std::vector<Path> folders;
    #ifdef SR_WIN32
        const std::string search_path = path.ToString() + "/*.*";
        WIN32_FIND_DATA fd;
        HANDLE hFind = ::FindFirstFile(search_path.c_str(), &fd);
        if(hFind != INVALID_HANDLE_VALUE) {
            do {
                const auto filename = std::string(fd.cFileName);
                if (filename != "." && filename != ".." && !filename.empty())
                    folders.emplace_back(path.ToString() + "/" + filename);
            }
            while(::FindNextFile(hFind, &fd));

            ::FindClose(hFind);
        }
    #endif
        return folders;
    }

    bool FileSystem::FolderExists(const std::string &path) {
    #ifdef SR_WIN32
        DWORD ftyp = GetFileAttributesA(path.c_str());
        if (ftyp == INVALID_FILE_ATTRIBUTES)
            return false;  //something is wrong with your path!

        if (ftyp & FILE_ATTRIBUTE_DIRECTORY)
            return true;   // this is a directory!
    #endif

        return false; // this is not a directory!
    }

    bool FileSystem::WriteToFile(const std::string &path, const std::string &text) {
        std::ofstream stream(path);
        if (!stream.is_open()) {
            return false;
        }
        stream << text;
        stream.close();

        return true;
    }

    std::string FileSystem::ReadBinaryAsString(const std::string &path, bool checkError) {
        std::ifstream file(path, std::ios::ate | std::ios::binary);

        if (!file.is_open()) {
            SRAssert2(!checkError, "FileSystem::ReadBinaryAsString() : failed to open \"" + path + "\" file!");
            return std::string();
        }

        size_t fileSize = (size_t) file.tellg();
        std::string buffer;
        buffer.resize(fileSize);

        file.seekg(0);
        file.read(buffer.data(), fileSize);

        file.close();

        return buffer;
    }

    uint64_t FileSystem::GetFileHash(const std::string &path) {
        const std::string& file = ReadBinaryAsString(path);

        if (file.empty()) {
            return SR_UINT64_MAX;
        }

        auto&& h = std::hash<std::string>();
        return h(file);
    }

    uint64_t FileSystem::GetFolderHash(const Path& path, uint64_t deep) {
        if (deep == 0) {
            return 0;
        }

        uint64_t hash = 0;

        for (auto&& subPath : GetAllInDir(path)) {
            if (subPath.IsHidden()) {
                continue;
            }

            if (subPath.IsFile()) {
                hash = SR_UTILS_NS::HashCombine<std::string>(ReadBinaryAsString(subPath), hash);
            }
            else if (subPath.IsDir()) {
                hash = SR_UTILS_NS::CombineTwoHashes(subPath.GetFolderHash(deep - 1), hash);
            }
        }

        return hash;
    }

    bool FileSystem::IsAbsolutePath(const std::string &path) {
    #ifdef SR_WIN32
        return path.size() >= 2 && path[1] == ':';
    #else
        return false;
    #endif
    }

    SR_UTILS_NS::Path FileSystem::BrowseFolder(const SR_UTILS_NS::Path &path) {
    #if defined(SR_WIN32) and defined(SR_MSVC)
        LPWSTR lPath = NULL;

        IFileDialog *pfd;
        if (SUCCEEDED(CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pfd))))
        {
            DWORD dwOptions;
            if (SUCCEEDED(pfd->GetOptions(&dwOptions)))
            {
                pfd->SetOptions(dwOptions | FOS_PICKFOLDERS);
            }

            IShellItem* psiWinDir;
            std::wstring folder = path.ToWinApiPath();
            HRESULT result = SHCreateItemFromParsingName(folder.c_str(), NULL, IID_PPV_ARGS(&psiWinDir));
            if (result == S_OK)
            {
                pfd->SetDefaultFolder(psiWinDir);
                pfd->SetFolder(psiWinDir);
                psiWinDir->Release();
            }

            if (SUCCEEDED(pfd->Show(NULL)))
            {
                IShellItem *psi;
                if (SUCCEEDED(pfd->GetResult(&psi)))
                {
                    if(!SUCCEEDED(psi->GetDisplayName(SIGDN_DESKTOPABSOLUTEPARSING, &lPath)))
                    {
                        MessageBox(NULL, "GetIDListName() failed", NULL, NULL);
                    }
                    psi->Release();
                }
            }
            pfd->Release();
        }

        return lPath ? std::wstring(lPath) : std::wstring();
    #else
        SRHalt("TODO");
        return std::string();
    #endif
    }

    bool FileSystem::IsHiddenFile(const std::string &path) {
    #ifdef SR_WIN32
        const DWORD attributes = GetFileAttributes(path.c_str());
        if (attributes & FILE_ATTRIBUTE_HIDDEN)
            return true;

        return false;
    #else
        SRHalt0();
        return false;
    #endif
    }
}