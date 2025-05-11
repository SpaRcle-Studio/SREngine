

# File Serializable.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Utils**](dir_3df27e53d7cc6cea988e3644dbf87b98.md) **>** [**inc**](dir_27b05de82864f3a1e6ade431259242d5.md) **>** [**Utils**](dir_800651e705081dade93279ddf25689e7.md) **>** [**Serialization**](dir_1c3f3ba47f77e74f680b6bcf664148dc.md) **>** [**Serializable.h**](Serializable_8h.md)

[Go to the documentation of this file](Serializable_8h.md)


```C++
//
// Created by Monika on 21.09.2021.
//

#ifndef SR_ENGINE_UTILS_SERIALIZABLE_H
#define SR_ENGINE_UTILS_SERIALIZABLE_H

#include <Utils/TypeTraits/SRClass.h>
#include <Utils/TypeTraits/Factory.h>

#include <Utils/Serialization/Serialization.h>

namespace SR_UTILS_NS {
    class Serializable : public SRClass {
        SR_CLASS()
    public:
        using OriginType = Serializable;

    public:
        virtual void Save(ISerializer& serializer) const;
        virtual bool Load(IDeserializer& deserializer);

        virtual void VerifyAfterLoad(SerializableVerifyContext& context) const noexcept { }

        virtual void OnPreSave() { }
        virtual void OnPostSave() { }

        virtual void OnPreLoad() { }
        virtual void OnPostLoad() { }

        void AddSerializationFlags(SerializationFlags flags) noexcept { m_flags |= flags; }
        void RemoveSerializationFlags(SerializationFlags flags) noexcept { m_flags &= ~flags; }

        SR_NODISCARD bool HasSerializationFlags(SerializationFlags flags) const noexcept;

    private:
        SerializationFlags m_flags = SerializationFlags::None;

    };

    template<typename T>
    struct ObjectDataAccessor<T, typename std::enable_if<SerializationTraits<T>::IsSerializable>::type> {
        static void Save(ISerializer& serializer, const T& value, const SerializationId& id) {
            serializer.BeginObject(id);
            static_cast<const Serializable&>(value).Save(serializer);
            serializer.EndObject();
        }

        static void Load(IDeserializer& deserializer, T& value, const SerializationId& id) {
            if (!deserializer.BeginObject(id)) {
                return;
            }
            static_cast<Serializable&>(value).Load(deserializer);
            deserializer.EndObject();
        }
    };
}

#endif //SR_ENGINE_UTILS_SERIALIZABLE_H
```


