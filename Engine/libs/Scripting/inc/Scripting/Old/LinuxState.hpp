//
// Created by innerviewer on 2024-05-28.
//

#ifndef EVO_SCRIPT_LINUX_STATE_HPP
#define EVO_SCRIPT_LINUX_STATE_HPP

#include <dlfcn.h>
#include <errno.h>

#include <EvoScript/Tools/FileSystem.h>
#include <EvoScript/IState.h>

namespace EvoScript {
        static std::string GetLastErrorAsString() {
        if(errno == 0) {
            return std::string();
        }

        // Shall we use thread-safe strerror_r() instead of strerror()?
        std::string message(strerror(errno));
        return message;
    }

    class LinuxState : public IState {
    public:
        LinuxState(const LinuxState&) = delete;
        explicit LinuxState(const std::string& path) : IState(path) { }
    private:
        ~LinuxState() override = default;
    public:
        void* GetFunctionImpl(const char* name) override {
            return dlsym(m_handle, name);;
        }

        bool Unload() override {
            if (!m_handle) {
                ES_ERROR("Win32State::Unload() : dll isn't loaded!");
                return false;
            }

            if (dlclose(m_handle) != 0) {
                ES_ERROR("LinuxState::Unload() : failed to unload dll!");
                return false;
            }

            return true;
        }

        bool Load() override {
            if (m_handle) {
                ES_ERROR("LinuxState::Load() : dll is already loaded!");
                return false;
            }

            if (!Tools::ESFileSystem::IsExists(m_path)) {
                ES_ERROR("LinuxState::Load() : file is not exists! \n\tPath: " + m_path)
                return false;
            }

            if (m_handle = dlopen(m_path.c_str(), RTLD_LAZY); !m_handle) {
                ES_ERROR("LinuxState::Load() : failed to load dll!"
                         "\n\tPath: " + m_path +
                         "\n\tDescription: " + dlerror());
                return false;
            }

            return true;
        }

        bool Exists() override {
            return false;
        }

    private:
        void* m_handle = nullptr;
    };
}

#endif //EVO_SCRIPT_LINUX_STATE_HPP
