

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

    class SubscriptionMessage final : SR_UTILS_NS::NonCopyable {
    public:
        void SetInt(const StringAtom id, const uint64_t value) {
            m_ints[id] = value;
        }

        void SetBool(const StringAtom id, const bool value) {
            m_bools[id] = value;
        }

        SR_NODISCARD uint64_t GetInt(const StringAtom id, const std::optional<uint64_t> def = std::nullopt) const {
            if (const auto it = m_ints.find(id); it != m_ints.end()) {
                return it->second;
            }
            if (def.has_value()) {
                return def.value();
            }
            SRHalt("SubscriptionMessage::GetInt() : id \"{}\" not found!", id.ToStringView());
            return 0;
        }

        SR_NODISCARD bool GetBool(const StringAtom id, const std::optional<bool> def = std::nullopt) const {
            if (const auto it = m_bools.find(id); it != m_bools.end()) {
                return it->second;
            }
            if (def.has_value()) {
                return def.value();
            }
            SRHalt("SubscriptionMessage::GetBool() : id \"{}\" not found!", id.ToStringView());
            return false;
        }

    private:
        std::map<StringAtom, uint64_t> m_ints;
        std::map<StringAtom, bool> m_bools;

    };

    class SubscriptionInternalInfo : SR_UTILS_NS::NonCopyable {
    public:
        explicit SubscriptionInternalInfo(SR_HTYPES_NS::Function<void(const SubscriptionMessage&)>&& callback, SubscriptionHolder* pHolder)
            : SR_UTILS_NS::NonCopyable()
            , callback(std::move(callback))
            , pHolder(pHolder)
        { }

        uint32_t index = SR_ID_INVALID;
        SR_HTYPES_NS::Function<void(const SubscriptionMessage&)> callback;
        SubscriptionHolder* pHolder = nullptr;
        StringAtom id;
    };

    class Subscription final : SR_UTILS_NS::NonCopyable {
    public:
        Subscription() = default;
        ~Subscription() override;

        explicit Subscription(SubscriptionInternalInfo* pInternalInfo)
            : m_internalInfo(pInternalInfo)
        { }

        Subscription(Subscription&& other) noexcept
            : m_internalInfo(SR_EXCHANGE(other.m_internalInfo, nullptr))
        { }

        Subscription& operator=(Subscription&& other) noexcept {
            Reset();
            m_internalInfo = SR_EXCHANGE(other.m_internalInfo, nullptr);
            return *this;
        }

        void Reset();

    private:
        SubscriptionInternalInfo* m_internalInfo = nullptr;

    };

    class SubscriptionHolder {
    public:
        virtual ~SubscriptionHolder();

        SR_NODISCARD Subscription Subscribe(StringAtom id, SR_HTYPES_NS::Function<void(const SubscriptionMessage&)>&& callback);

        SR_NODISCARD bool HasSubscriptions() const noexcept {
            return m_count > 0;
        }

        void Unsubscribe(const SubscriptionInternalInfo* pSubscription) {
            if (auto it = m_subscriptions.find(pSubscription->id); it != m_subscriptions.end()) {
                auto& pool = it->second;
                pool.RemoveByIndex(pSubscription->index);
                delete pSubscription;
                SRAssert(m_count > 0);
                --m_count;
            }
            else {
                SRHalt("SubscriptionHolder::Unsubscribe() : subscription not found!");
            }
        }

        void Broadcast(const StringAtom id) {
            static SubscriptionMessage message;
            if (const auto it = m_subscriptions.find(id); it != m_subscriptions.end()) {
                it->second.ForEach([](uint32_t, auto&& pSubscription) {
                    pSubscription->callback(message);
                });
            }
        }

        void Broadcast(const StringAtom id, const SubscriptionMessage& message) {
            if (const auto it = m_subscriptions.find(id); it != m_subscriptions.end()) {
                it->second.ForEach([&message](uint32_t, auto&& pSubscription) {
                    pSubscription->callback(message);
                });
            }
        }

    private:
        std::map<StringAtom, SR_HTYPES_NS::ObjectPool<SubscriptionInternalInfo*, uint32_t>> m_subscriptions;
        uint32_t m_count = 0;

    };
}

#endif //SR_ENGINE_UTILS_SUBSCRIPTION_HOLDER_H
```


