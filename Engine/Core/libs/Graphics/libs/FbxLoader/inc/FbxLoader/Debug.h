//
// Created by Monika on 27.07.2021.
//

#ifndef FBXLOADER_DEBUG_H
#define FBXLOADER_DEBUG_H

#include <functional>
#include <utility>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>
#include <cmath>

namespace FbxLoader {
    typedef std::function<void(const std::string& msg)> MsgFn;

    class Debug {
    public:
        Debug() = delete;
        Debug(const Debug&) = delete;
        ~Debug() = delete;
    private:
        static inline bool g_init = false;
    public:
        static void Init(const MsgFn& err_fun, const MsgFn& warn_fun) {
            if (!g_init) {
                Error = err_fun;
                Warn  = warn_fun;
            }
            g_init = true;
        }
        static bool IsInit() {
            return g_init;
        }
    public:
        static inline std::function<void(const std::string& msg)> Error = std::function<void(const std::string& msg)>();
        static inline std::function<void(const std::string& msg)> Warn  = std::function<void(const std::string& msg)>();
    };
}

#define FBX_ERROR(msg) Debug::Error(msg);
#define FBX_WARN(msg) Debug::Warn(msg);

#endif //FBXLOADER_DEBUG_H
