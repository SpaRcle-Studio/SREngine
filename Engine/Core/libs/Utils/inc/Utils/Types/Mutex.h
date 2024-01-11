//
// Created by Monika on 22.05.2023.
//

#ifndef SR_ENGINE_MUTEX_H
#define SR_ENGINE_MUTEX_H

#include <Utils/Common/NonCopyable.h>

namespace SR_HTYPES_NS {
    #define SR_SHARED_RECURSIVE_MUTEX_ERROR(msg) \
        std::cout << msg << std::endl;           \
        throw std::logic_error(msg);             \

    class SharedRecursiveMutex : public SR_UTILS_NS::NonCopyable {
    public:
        SharedRecursiveMutex() = default;
        ~SharedRecursiveMutex() override = default;

    public:
        void lock();
        bool try_lock();
        void unlock();

        void lock_shared();
        bool try_lock_shared();
        void unlock_shared();

    private:
        SR_NODISCARD SR_INLINE bool is_exclusive_locked() const {
            return m_exclusive_count > 0;
        }

        SR_NODISCARD SR_INLINE bool is_shared_locked() const {
            return !m_shared_locks.empty();
        }

        SR_NODISCARD SR_INLINE bool can_exclusively_lock() const {
            return can_start_exclusive_lock() || can_increment_exclusive_lock();
        }

        SR_NODISCARD SR_INLINE bool can_start_exclusive_lock() const {
            return !is_exclusive_locked() && (!is_shared_locked() || is_shared_locked_only_on_this_thread());
        }

        SR_NODISCARD SR_INLINE bool can_increment_exclusive_lock() const {
            return is_exclusive_locked_on_this_thread();
        }

        SR_NODISCARD SR_INLINE bool can_lock_shared() const {
            return !is_exclusive_locked() || is_exclusive_locked_on_this_thread();
        }

        SR_NODISCARD SR_INLINE bool is_shared_locked_only_on_this_thread() const {
            return is_shared_locked_only_on_thread(std::this_thread::get_id());
        }

        SR_NODISCARD SR_INLINE bool is_shared_locked_only_on_thread(std::thread::id id) const {
            return m_shared_locks.size() == 1 && m_shared_locks.find(id) != m_shared_locks.end();
        }

        SR_NODISCARD SR_INLINE bool is_exclusive_locked_on_this_thread() const {
            return is_exclusive_locked_on_thread(std::this_thread::get_id());
        }

        SR_NODISCARD SR_INLINE bool is_exclusive_locked_on_thread(std::thread::id id) const {
            return m_exclusive_count > 0 && m_exclusive_thread_id == id;
        }

        SR_INLINE void start_exclusive_lock() {
            m_exclusive_thread_id = std::this_thread::get_id();
            m_exclusive_count++;
        }

        SR_INLINE void increment_exclusive_lock() {
            m_exclusive_count++;
        }

        SR_INLINE void decrement_exclusive_lock() {
            if (m_exclusive_count == 0) {
                SR_SHARED_RECURSIVE_MUTEX_ERROR("Not exclusively locked, cannot exclusively unlock");
            }

            if (m_exclusive_thread_id == std::this_thread::get_id()) {
                m_exclusive_count--;
            }
            else {
                SR_SHARED_RECURSIVE_MUTEX_ERROR("Calling exclusively unlock from the wrong thread");
            }
        }

        SR_INLINE void increment_shared_lock() {
            increment_shared_lock(std::this_thread::get_id());
        }

        SR_INLINE void increment_shared_lock(std::thread::id id)  {
            if (m_shared_locks.find(id) == m_shared_locks.end()) {
                m_shared_locks[id] = 1;
            }
            else {
                m_shared_locks[id] += 1;
            }
        }

        SR_INLINE void decrement_shared_lock() {
            decrement_shared_lock(std::this_thread::get_id());
        }

        SR_INLINE void decrement_shared_lock(std::thread::id id) {
            if (m_shared_locks.empty()) {
                SR_SHARED_RECURSIVE_MUTEX_ERROR("Not shared locked, cannot shared unlock");
            }

            if (m_shared_locks.find(id) == m_shared_locks.end()) {
                SR_SHARED_RECURSIVE_MUTEX_ERROR("Calling shared unlock from the wrong thread");
            }

            if (m_shared_locks[id] == 1) {
                m_shared_locks.erase(id);
            }
            else {
                m_shared_locks[id] -= 1;
            }
        }

    private:
        std::mutex m_mtx;
        std::thread::id m_exclusive_thread_id;
        size_t m_exclusive_count = 0;
        std::map<std::thread::id, size_t> m_shared_locks;
        std::condition_variable m_cond_var;

    };
}

#endif //SR_ENGINE_MUTEX_H
