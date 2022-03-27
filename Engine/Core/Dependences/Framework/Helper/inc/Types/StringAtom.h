//
// Created by Monika on 29.09.2021.
//

#ifndef GAMEENGINE_STRINGATOM_H
#define GAMEENGINE_STRINGATOM_H

#include <mutex>
#include <string>

namespace Framework::Helper {
    class StringAtom {
    public:
        StringAtom() = default;

        StringAtom(const char* str) {
            m_data = str;
        }
        StringAtom(const std::string& str) {
            m_data = str;
        }
        StringAtom(const StringAtom& str) {
            m_data = str.m_data;
        }
    public:
        operator std::string() const {
            const std::lock_guard<std::mutex> lock(m_mutex);
            return m_data;
        }

        StringAtom& operator=(const std::string& str) {
            const std::lock_guard<std::mutex> lock(m_mutex);
            m_data = str;
            return *this;
        }

        StringAtom& operator=(const char* str) {
            const std::lock_guard<std::mutex> lock(m_mutex);
            m_data = str;
            return *this;
        }

        void operator ()(const char* str) {
            const std::lock_guard<std::mutex> lock(m_mutex);
            m_data = str;
        }

    public:
        [[nodiscard]] uint64_t Size() const {
            const std::lock_guard<std::mutex> lock(m_mutex);
            return static_cast<uint64_t>(m_data.size());
        };

        [[nodiscard]] std::string ToString() const {
            const std::lock_guard<std::mutex> lock(m_mutex);
            return m_data;
        };

    private:
        mutable std::mutex m_mutex;
        std::string m_data;
    };
}

#endif //GAMEENGINE_STRINGATOM_H
