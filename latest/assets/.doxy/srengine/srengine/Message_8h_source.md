

# File Message.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Utils**](dir_f3d6dc6978aa78088efd06c6b2710310.md) **>** [**inc**](dir_e0f1b8570fc577fb78354cd460e9e760.md) **>** [**Utils**](dir_06a42b3e946fb631201a76a22d1aab06.md) **>** [**Network**](dir_c7b83f1df097df65b63198ef53f0d275.md) **>** [**Message.h**](Message_8h.md)

[Go to the documentation of this file](Message_8h.md)


```C++
// 
// Created by innerviewer on 2025-03-30.
//

#ifndef SR_COMMON_NETWORK_MESSAGE_H
#define SR_COMMON_NETWORK_MESSAGE_H

namespace SR_NETWORK_NS {
    class IMessage {
    public:
        virtual ~IMessage() = default;

        // For type-safe message identification
        template<typename T>
        SR_NODISCARD bool is() const {
            static_assert(std::is_enum_v<T>, "Message ID must be an enum type");
            return getTypeID() == typeid(T);
        }

        // For getting the actual message ID value
        template<typename T>
        T getID() const {
            static_assert(std::is_enum_v<T>, "Message ID must be an enum type");
            return static_cast<T>(getRawID());
        }

    protected:
        SR_NODISCARD virtual std::size_t getTypeID() const = 0;
        SR_NODISCARD virtual int64_t getRawID() const = 0;
    };

    // Message data interface
    class IMessageData {
    public:
        virtual ~IMessageData() = default;
        SR_NODISCARD virtual std::unique_ptr<IMessageData> clone() const = 0;
    };

    // Concrete message implementation
    template<typename T, typename DataT = void>
    class Message final : public IMessage {
        static_assert(std::is_enum_v<T>, "Message ID must be an enum type");

    public:
        explicit Message(T id) : m_id(id) {}

        Message(T id, DataT data) : m_id(id), m_data(std::move(data)) {}

        // Type identification
        SR_NODISCARD std::size_t getTypeID() const override {
            return typeid(T).hash_code();
        }

        // Get the raw message ID
        SR_NODISCARD int64_t getRawID() const override {
            return static_cast<int64_t>(m_id);
        }

        // Check if message has data
        SR_NODISCARD bool hasData() const {
            return !std::is_same_v<DataT, void>;
        }

        // Get message data (only if DataT is not void)
        template<typename U = DataT>
        std::enable_if_t<!std::is_same_v<U, void>, const U&> getData() const {
            return m_data;
        }

    private:
        T m_id;
        DataT m_data;
    };

    // Message handler interface
    class IMessageHandler {
    public:
        virtual ~IMessageHandler() = default;
        virtual void handleMessage(const IMessage& message) = 0;
    };
}

#endif //SR_COMMON_NETWORK_MESSAGE_H
```


