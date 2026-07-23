//
// Created by Nikita on 03.07.2021.
//

#ifndef EVOSCRIPT_WIN32STATE_HPP
#define EVOSCRIPT_WIN32STATE_HPP

#include <Windows.h>

#include <Scripting/Tools/FileSystem.h>
#include <Scripting/IState.h>

namespace EvoScript {
    //Returns the last Win32 error, in string format. Returns an empty string if there is no error.
    static std::string GetLastErrorAsString() {
        //Get the error message ID, if any.
        DWORD errorMessageID = ::GetLastError();
        if (errorMessageID == 0) {
            return std::string(); //No error message has been recorded
        }

        LPSTR messageBuffer = nullptr;

        //Ask Win32 to give us the string version of that message ID.
        //The parameters we pass in, tell Win32 to create the buffer that holds the message for us (because we don't yet know how long the message string will be).
        size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                                     NULL, errorMessageID, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&messageBuffer, 0, NULL);

        //Copy the error message into a std::string.
        std::string message(messageBuffer, size);

        //Free the Win32's string's buffer.
        LocalFree(messageBuffer);

        return message;
    }

    class Win32State : public IState {
    public:
        Win32State(const Win32State&) = delete;
        explicit Win32State(const std::string& path) : IState(path) { }
    private:
        ~Win32State() override = default;
    private:
        HINSTANCE m_hDLL = nullptr;
    public:
        void* GetFunctionImpl(const char* name) override {
            return reinterpret_cast<void*>(::GetProcAddress(m_hDLL, name));
        }

        bool Unload() override {
            if (!m_hDLL) {
                ES_ERROR("Win32State::Unload() : dll isn't loaded!");
                return false;
            }

            if (!FreeLibrary(m_hDLL)) {
                ES_ERROR("Win32State::Unload() : failed to unload dll!");
                return false;
            }

            return true;
        }
        bool Load() override {
            if (m_hDLL) {
                ES_ERROR("Win32State::Load() : dll is already loaded!");
                return false;
            }

            if (!Tools::ESFileSystem::IsExists(m_path)) {
                ES_ERROR("Win32State::Load() : file is not exists! \n\tPath: " + m_path)
                return false;
            }

            if (m_hDLL = LoadLibrary(m_path.c_str()); !m_hDLL) {
                ES_ERROR("Win32State::Load() : failed to load dll!"
                         "\n\tPath: " + m_path +
                         "\n\tError code: " + std::to_string(GetLastError()) +
                         "\n\tDescription: " + GetLastErrorAsString());
                return false;
            }

            return true;
        }
        bool Exists() override {
            return false;
        }
    };
}

#endif //EVOSCRIPT_WIN32STATE_HPP
