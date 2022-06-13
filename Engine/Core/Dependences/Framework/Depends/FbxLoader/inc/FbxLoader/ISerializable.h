//
// Created by Monika on 31.01.2022.
//

#ifndef SRENGINE_ISERIALIZABLE_H
#define SRENGINE_ISERIALIZABLE_H

#include <fstream>
#include <iostream>

namespace FbxLoader::Tools {
    class ISerializable {
    protected:
        ISerializable() = default;
        virtual ~ISerializable() = default;

    public:
        bool SaveTo(const std::string& path) {
            std::ofstream file(path, std::ios::binary);
            if (!file.is_open())
                return false;

            Save(file);

            file.close();
            return true;
        }

        bool LoadFrom(const std::string& path) {
            std::ifstream file(path, std::ios::binary);
            if (!file.is_open())
                return false;

            Load(file);

            file.close();
            return true;
        }

    protected:
        virtual void Save(std::ofstream& file) const { }
        virtual void Load(std::ifstream& file) { }
    };
}

#endif //SRENGINE_ISERIALIZABLE_H
