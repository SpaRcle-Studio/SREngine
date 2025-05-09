

# File SubscriptionHolder.h

[**File List**](files.md) **>** [**Common**](dir_964cfbb3f15edef5ecfb3ae3bc01626c.md) **>** [**SubscriptionHolder.h**](SubscriptionHolder_8h.md)

[Go to the documentation of this file](SubscriptionHolder_8h.md)


```C++
//
// Created by Monika on 27.05.2024.
//

#ifndef SR_ENGINE_UTILS_SUBSCRIPTION_HOLDER_H
#define SR_ENGINE_UTILS_SUBSCRIPTION_HOLDER_H

#include <Utils/Common/NonCopyable.h>
#include <Utils/Types/StringAtom.h>
#include <Utils/Types/ObjectPool.h>
#include <Utils/Types/Function.h>

namespace SR_UTILS_NS {
    class SubscriptionHolder;

    class SR_COMMON_DLL_API SubscriptionMessage final : SR_UTILS_NS::NonCopyable {
    public:
        SubscriptionMessage();
        ~SubscriptionMessage() override;

        void SetInt(StringAtom id, uint64_t value);
        void SetBool(StringAtom id, bool value);
        void SetString(StringAtom id, const std::string& value);
        void SetPath(StringAtom id, const SR_UTILS_NS::Path& value);

        SR_NODISCARD uint64_t GetInt(StringAtom id, const std::optional<uint64_t>& def = std::nullopt) const;
        SR_NODISCARD bool GetBool(StringAtom id, const std::optional<bool>& def = std::nullopt) const;
        SR_NODISCARD std::string GetString(StringAtom id, const std::optional<std::string>& def = std::nullopt) const;
        SR_NODISCARD SR_UTILS_NS::Path GetPath(StringAtom id, const std::optional<SR_UTILS_NS::Path>& def = std::nullopt) const;
        SR_NODISCARD const SR_UTILS_NS::Path& GetPathRef(StringAtom id) const;

    private:
        template<typename T, typename Container> SR_NODISCARD T GetValue(const StringAtom id, const Container& container, const std::optional<T> def) const {
            if (const auto it = container.find(id); it != container.end()) {
                return it->second;
            }
            if (def.has_value()) {
                return def.value();
            }
            SRHalt("SubscriptionMessage::GetValue() : id \"{}\" not found!", id);
            return T();
        }

        template<typename T, typename Container> SR_NODISCARD const T& GetValueRef(const StringAtom id, const Container& container) const {
            if (const auto it = container.find(id); it != container.end()) {
                return it->second;
            }
            SRHalt("SubscriptionMessage::GetValueRef() : id \"{}\" not found!", id);
            static T defaultValue;
            return defaultValue;
        }

    private:
        std::map<StringAtom, uint64_t> m_ints;
        std::map<StringAtom, bool> m_bools;
        std::map<StringAtom, std::string> m_strings;
        std::map<StringAtom, SR_UTILS_NS::Path> m_paths;

    };

    class SR_COMMON_DLL_API SubscriptionInternalInfo : SR_UTILS_NS::NonCopyable {
    public:
        explicit SubscriptionInternalInfo(SR_HTYPES_NS::Function<void(const SubscriptionMessage&)>&& callback, SubscriptionHolder* pHolder);

        uint32_t index = SR_ID_INVALID;
        SR_HTYPES_NS::Function<void(const SubscriptionMessage&)> callback;
        SubscriptionHolder* pHolder = nullptr;
        StringAtom id;
    };

    class SR_COMMON_DLL_API Subscription final : SR_UTILS_NS::NonCopyable {
    public:
        Subscription();
        ~Subscription() override;
        explicit Subscription(SubscriptionInternalInfo* pInternalInfo);
        Subscription(Subscription&& other) noexcept;
        Subscription& operator=(Subscription&& other) noexcept;

        void Reset();

    private:
        SubscriptionInternalInfo* m_internalInfo = nullptr;

    };

    class SR_COMMON_DLL_API SubscriptionHolder {
    public:
        SubscriptionHolder();
        SubscriptionHolder(SubscriptionHolder& other) = delete;
        SubscriptionHolder(SubscriptionHolder&& other) = delete;
        SubscriptionHolder& operator=(SubscriptionHolder& other) = delete;
        SubscriptionHolder& operator=(SubscriptionHolder&& other) = delete;
        virtual ~SubscriptionHolder();

        SR_NODISCARD Subscription Subscribe(StringAtom id, SR_HTYPES_NS::Function<void(const SubscriptionMessage&)>&& callback);
        SR_NODISCARD bool HasSubscriptions() const noexcept;

        void Unsubscribe(const SubscriptionInternalInfo* pSubscription);

        void Broadcast(StringAtom id);
        void Broadcast(StringAtom id, const SubscriptionMessage& message);

    private:
        std::map<StringAtom, SR_HTYPES_NS::ObjectPool<SubscriptionInternalInfo*, uint32_t>> m_subscriptions;
        uint32_t m_count = 0;

    };
}

#endif //SR_ENGINE_UTILS_SUBSCRIPTION_HOLDER_H
```


