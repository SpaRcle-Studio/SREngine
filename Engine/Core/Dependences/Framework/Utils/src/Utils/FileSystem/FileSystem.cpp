//
// Created by Nikita on 16.11.2020.
//

#include <Utils/FileSystem/FileSystem.h>
#include <Utils/Debug.h>
#include <Utils/FileSystem/Path.h>
#include <Utils/Common/Hashes.h>
#include <Utils/Common/StringUtils.h>

namespace SR_UTILS_NS {
    void FileSystem::UnmapFile(const char *str) {

    }

    const char *FileSystem::FileMapView(std::string path) {
        const char *data = nullptr;

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

    std::vector<uint8_t> FileSystem::ReadFileAsVector(const std::string &path) {
        std::ifstream file(path, std::ifstream::binary | std::ios::in);

        if (file.fail()) {
            return std::vector<uint8_t>();
        }

        file.seekg(0, std::ios::end);
        std::streampos end = file.tellg();
        file.seekg(0, std::ios::beg);
        std::streampos start = file.tellg();
        size_t size = static_cast<size_t>(end - start);

        std::vector<uint8_t> result(size);

        file.read(reinterpret_cast<char*>(result.data()), size);

        return result;
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

    bool FileSystem::CreatePath(std::string path, uint32_t offset) {
        if (path.empty())
            return false;

        if (path.back() != '/')
            path.append("/");

        auto pos = path.find('/', offset);
        if (pos != std::string::npos) {
            auto dir = path.substr(0, pos);

            Platform::CreateFolder(dir);
            CreatePath(path, pos + 1);
        }

        return true;
    }

    //std::string FileSystem::GetFullPath(const std::string& path) {
    //#ifdef SR_WIN32
    //    char fullFilename[MAX_PATH];
    //    GetFullPathName(path.c_str(), MAX_PATH, fullFilename, nullptr);
    //    return std::string(fullFilename);
    //#else
    //    return std::string();
    //#endif
    //}

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

        for (auto&& subPath : Platform::GetInDirectory(path, Path::Type::Undefined)) {
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

    std::shared_ptr<std::vector<uint8_t>> FileSystem::ReadFileAsBlob(const std::string &path) {
        return std::make_shared<std::vector<uint8_t>>(std::move(ReadFileAsVector(path)));
    }
}