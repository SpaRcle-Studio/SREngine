//
// Created by Monika on 19.06.2022.
//

#include <Utils/FileSystem/FileDialog.h>

#include <nfd.h>

namespace SR_UTILS_NS {
    void FileDialog::InitSingleton() {
        Singleton::InitSingleton();
        NFD_Init();
    }

    void FileDialog::OnSingletonDestroy() {
        NFD_Quit();
        Singleton::OnSingletonDestroy();
    }

    Path FileDialog::SaveDialog(const Path &defaultPath, const Filter& filter) const {
        std::string path;

        nfdchar_t *outPath;

        nfdfilteritem_t* pFilterItem = filter.size() > 0 ? new nfdfilteritem_t[filter.size()] : nullptr;

        for (uint32_t i = 0; i < static_cast<uint32_t>(filter.size()); ++i) {
            pFilterItem[i].name = filter[i].first.c_str();
            pFilterItem[i].spec = filter[i].second.c_str();
        }

        nfdresult_t result = NFD_SaveDialog(&outPath, pFilterItem, filter.size(), defaultPath.ToString().c_str(), NULL);
        if (result == NFD_OKAY)
        {
            path = std::string(outPath);
            NFD_FreePath(outPath);
        }
        else if (result == NFD_CANCEL)
        {
            /// ignore
        }
        else
        {
            /// ignore
        }

        return path;
    }

    Path FileDialog::OpenDialog(const Path& defaultPath, const Filter& filter) const {
        std::string path;

        nfdchar_t *outPath;

        nfdfilteritem_t* pFilterItem = filter.size() > 0 ? new nfdfilteritem_t[filter.size()] : nullptr;

        for (uint32_t i = 0; i < static_cast<uint32_t>(filter.size()); ++i) {
            pFilterItem[i].name = filter[i].first.c_str();
            pFilterItem[i].spec = filter[i].second.c_str();
        }

        nfdresult_t result = NFD_OpenDialog(&outPath, pFilterItem, filter.size(), defaultPath.ToString().c_str());
        if (result == NFD_OKAY)
        {
            path = std::string(outPath);
            NFD_FreePath(outPath);
        }
        else if (result == NFD_CANCEL)
        {
            /// ignore
        }
        else
        {
            /// ignore
        }

        return path;
    }
}