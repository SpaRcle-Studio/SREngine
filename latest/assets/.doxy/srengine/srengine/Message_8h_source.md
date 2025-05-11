

# File Message.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Utils**](dir_3df27e53d7cc6cea988e3644dbf87b98.md) **>** [**inc**](dir_27b05de82864f3a1e6ade431259242d5.md) **>** [**Utils**](dir_800651e705081dade93279ddf25689e7.md) **>** [**Network**](dir_fcfa5bace1b3a12e3000ff4cad4809c8.md) **>** [**Message.h**](Message_8h.md)

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


