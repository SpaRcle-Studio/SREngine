//
// Created by Nikita on 03.07.2021.
//

#ifndef SR_ENGINE_SCRIPTING_I_STATE_H
#define SR_ENGINE_SCRIPTING_I_STATE_H

#include <Utils/Common/NonCopyable.h>

namespace EvoScript {
    class IState : private SR_UTILS_NS::NonCopyable {
    public:
        ~IState() override = default;

    protected:
        explicit IState(std::string path) : m_path(std::move(path)) {}

    public:
        static IState* Allocate(const std::string& path);

        template<typename Fn> inline Fn GetFunction(const char* name) {
            return reinterpret_cast<Fn>(GetFunctionImpl(name));
        }

    public:
        SR_NODISCARD std::string GetPath() const { return m_path; }

        virtual bool Exists() = 0;
        virtual bool Load() = 0;
        virtual bool Unload() = 0;

    protected:
        virtual void* GetFunctionImpl(const char* name) = 0;

    public:
#ifdef SR_WIN32
        static const inline std::string Extension = ".dll";
#elif defined(SR_LINUX)
        static const inline std::string Extension = ".so";
#else
        static const inline std::string Extension = ".UNKNOWN";
#endif

    protected:
        //! path to local module copy
        std::string m_path;
    };
} // namespace EvoScript

#endif // SR_ENGINE_SCRIPTING_I_STATE_H
