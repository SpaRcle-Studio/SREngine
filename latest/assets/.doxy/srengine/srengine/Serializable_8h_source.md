

# File Serializable.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Utils**](dir_f3d6dc6978aa78088efd06c6b2710310.md) **>** [**inc**](dir_e0f1b8570fc577fb78354cd460e9e760.md) **>** [**Utils**](dir_06a42b3e946fb631201a76a22d1aab06.md) **>** [**Serialization**](dir_ffec67008ecd4ba04c0216def73faaef.md) **>** [**Serializable.h**](Serializable_8h.md)

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


