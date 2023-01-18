//
// Created by Monika on 12.03.2022.
//

#include <Utils/Types/Marshal.h>
#include <Utils/ResourceManager/ResourceManager.h>

namespace SR_HTYPES_NS {
    Marshal::Marshal(std::ifstream& ifs)
        : Super(ifs)
    { }

    Marshal::Marshal(const std::string& str)
        : Super(str)
    { }

    Marshal::Marshal(const char *pData, uint64_t size)
        : Super(pData, size)
    { }

    void Marshal::Append(Marshal&& marshal) {
        if (marshal) {
            Super::Write(marshal.Super::View(), marshal.Size());
        }
    }

    void Marshal::Append(Marshal::Ptr& pMarshal) {
        if (pMarshal && *pMarshal) {
            Super::Write(pMarshal->Super::View(), pMarshal->Size());
        }

        SR_SAFE_DELETE_PTR(pMarshal);
    }

    bool Marshal::Save(const Path &path) const {
        if (!path.Make()) {
            return false;
        }

        std::ofstream file;
        file.open(path.ToString(), std::ios::binary);
        if (!file.is_open()) {
            return false;
        }

        file.write(Super::View(), Size());
        file.close();

        return true;
    }

    Marshal::Ptr Marshal::LoadPtr(const Path& path) {
        std::ifstream file(path.ToString(), std::ios::binary);
        if (!file.is_open()) {
            return nullptr;
        }

        auto&& pMarshal = new Marshal(file);

        if (!pMarshal->Valid()) {
            delete pMarshal;
            pMarshal = nullptr;
        }

        file.close();

        return pMarshal;
    }

    Marshal Marshal::Load(const Path &path) {
        std::ifstream file(path.ToString(), std::ios::binary);
        if (!file.is_open()) {
            return Marshal();
        }

        Marshal marshal(file);
        file.close();

        return marshal;
    }

    Marshal Marshal::Copy() const {
        return *this;
    }

    Marshal::Ptr Marshal::CopyPtr() const {
        return new Marshal(*this);
    }

    Marshal Marshal::LoadFromMemory(const std::string& data) {
        return Marshal(data);
    }

    Marshal Marshal::LoadFromBase64(const std::string& base64) {
        return LoadFromMemory(SR_UTILS_NS::StringUtils::Base64Decode(base64));
    }

    Marshal Marshal::ReadBytes(uint64_t count) const noexcept {
        return Marshal(Super::View(), count);
    }

    Marshal::Ptr Marshal::ReadBytesPtr(uint64_t count) const noexcept {
        return new Marshal(Super::View() + GetPosition(), count);
    }
}