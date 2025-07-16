

# File ObjectDataAccessors.inl.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Utils**](dir_3df27e53d7cc6cea988e3644dbf87b98.md) **>** [**inc**](dir_27b05de82864f3a1e6ade431259242d5.md) **>** [**Utils**](dir_800651e705081dade93279ddf25689e7.md) **>** [**Serialization**](dir_1c3f3ba47f77e74f680b6bcf664148dc.md) **>** [**ObjectDataAccessors.inl.h**](ObjectDataAccessors_8inl_8h.md)

[Go to the documentation of this file](ObjectDataAccessors_8inl_8h.md)


```C++
//
// Created by Monika on 17.10.2024.
//

template<> struct ObjectDataAccessor<std::string> {
    static void Save(ISerializer& serializer, const std::string& value, const SerializationId& id) {
        serializer.WriteString(value, id);
    }

    static void Load(IDeserializer& deserializer, std::string& value, const SerializationId& id) {
        deserializer.ReadString(value, id);
    }
};

template<> struct ObjectDataAccessor<SR_UTILS_NS::StringAtom> {
    static void Save(ISerializer& serializer, const SR_UTILS_NS::StringAtom& value, const SerializationId& id) {
        serializer.WriteString(value.ToStringView(), id);
    }

    static void Load(IDeserializer& deserializer, SR_UTILS_NS::StringAtom& value, const SerializationId& id) {
        deserializer.ReadString(value, id);
    }
};

template<> struct ObjectDataAccessor<SR_HTYPES_NS::UnicodeString> {
    static void Save(ISerializer& serializer, const SR_HTYPES_NS::UnicodeString& value, const SerializationId& id) {
        serializer.WriteString(value, id);
    }

    static void Load(IDeserializer& deserializer, SR_HTYPES_NS::UnicodeString& value, const SerializationId& id) {
        deserializer.ReadString(value, id);
    }
};

template<> struct ObjectDataAccessor<bool> {
    static void Save(ISerializer& serializer, const bool value, const SerializationId& id) {
        serializer.WriteBool(value, id);
    }

    static void Load(IDeserializer& deserializer, bool& value, const SerializationId& id) {
        deserializer.ReadBool(value, id);
    }
};

template<> struct ObjectDataAccessor<float_t> {
    static void Save(ISerializer& serializer, const float_t value, const SerializationId& id) {
        serializer.WriteFloat(value, id);
    }

    static void Load(IDeserializer& deserializer, float_t& value, const SerializationId& id) {
        deserializer.ReadFloat(value, id);
    }
};

template<> struct ObjectDataAccessor<double_t> {
    static void Save(ISerializer& serializer, const double_t value, const SerializationId& id) {
        serializer.WriteDouble(value, id);
    }

    static void Load(IDeserializer& deserializer, double& value, const SerializationId& id) {
        deserializer.ReadDouble(value, id);
    }
};

template<> struct ObjectDataAccessor<std::int8_t> {
    static void Save(ISerializer& serializer, const std::int8_t value, const SerializationId& id) {
        serializer.WriteInt(value, id);
    }

    static void Load(IDeserializer& deserializer, std::int8_t& value, const SerializationId& id) {
        deserializer.ReadInt(value, id);
    }
};

template<> struct ObjectDataAccessor<std::int16_t> {
    static void Save(ISerializer& serializer, const std::int16_t value, const SerializationId& id) {
        serializer.WriteInt(value, id);
    }

    static void Load(IDeserializer& deserializer, std::int16_t& value, const SerializationId& id) {
        deserializer.ReadInt(value, id);
    }
};

template<> struct ObjectDataAccessor<std::int32_t> {
    static void Save(ISerializer& serializer, const std::int32_t value, const SerializationId& id) {
        serializer.WriteInt(value, id);
    }

    static void Load(IDeserializer& deserializer, std::int32_t& value, const SerializationId& id) {
        deserializer.ReadInt(value, id);
    }
};

template<> struct ObjectDataAccessor<std::int64_t> {
    static void Save(ISerializer& serializer, const std::int64_t value, const SerializationId& id) {
        serializer.WriteInt(value, id);
    }

    static void Load(IDeserializer& deserializer, std::int64_t& value, const SerializationId& id) {
        deserializer.ReadInt(value, id);
    }
};

template<> struct ObjectDataAccessor<SR_MATH_NS::FSize> {
    static void Save(ISerializer& serializer, const SR_MATH_NS::FSize& value, const SerializationId& id) {
        serializer.BeginObject(id);
        Serialization::SaveCheckDefault(serializer, value.v, SerializationId::Create("v"));
        Serialization::SaveCheckDefault(serializer, value.metric, SerializationId::Create("metric"));
        serializer.EndObject();
    }

    static void Load(IDeserializer& deserializer, SR_MATH_NS::FSize& value, const SerializationId& id) {
        if (!deserializer.BeginObject(id)) {
            return;
        }

        Serialization::Load(deserializer, value.v, SerializationId::Create("v"));
        Serialization::Load(deserializer, value.metric, SerializationId::Create("metric"));

        deserializer.EndObject();
    }
};

template<> struct ObjectDataAccessor<SR_MATH_NS::FSize2> {
    static void Save(ISerializer& serializer, const SR_MATH_NS::FSize2& value, const SerializationId& id) {
        serializer.BeginObject(id);
        Serialization::SaveCheckDefault(serializer, value.width, SerializationId::Create("width"));
        Serialization::SaveCheckDefault(serializer, value.height, SerializationId::Create("height"));
        serializer.EndObject();
    }
    static void Load(IDeserializer& deserializer, SR_MATH_NS::FSize2& value, const SerializationId& id) {
        if (!deserializer.BeginObject(id)) {
            return;
        }
        Serialization::Load(deserializer, value.width, SerializationId::Create("width"));
        Serialization::Load(deserializer, value.height, SerializationId::Create("height"));
        deserializer.EndObject();
    }
};

template<> struct ObjectDataAccessor<std::uint8_t> {
    static void Save(ISerializer& serializer, std::uint8_t value, const SerializationId& id) {
        serializer.WriteUInt(value, id);
    }

    static void Load(IDeserializer& deserializer, std::uint8_t& value, const SerializationId& id) {
        deserializer.ReadUInt(value, id);
    }
};

template<> struct ObjectDataAccessor<std::uint16_t> {
    static void Save(ISerializer& serializer, std::uint16_t value, const SerializationId& id) {
        serializer.WriteUInt(value, id);
    }

    static void Load(IDeserializer& deserializer, std::uint16_t& value, const SerializationId& id) {
        deserializer.ReadUInt(value, id);
    }
};

template<> struct ObjectDataAccessor<std::uint32_t> {
    static void Save(ISerializer& serializer, std::uint32_t value, const SerializationId& id) {
        serializer.WriteUInt(value, id);
    }

    static void Load(IDeserializer& deserializer, std::uint32_t& value, const SerializationId& id) {
        deserializer.ReadUInt(value, id);
    }
};

template<> struct ObjectDataAccessor<std::uint64_t> {
    static void Save(ISerializer& serializer, std::uint64_t value, const SerializationId& id) {
        serializer.WriteUInt(value, id);
    }

    static void Load(IDeserializer& deserializer, std::uint64_t& value, const SerializationId& id) {
        deserializer.ReadUInt(value, id);
    }
};

template<class T> struct ObjectDataAccessorVector {
private:
    SR_CONSTEXPR static SerializationId itemId = SerializationId::Create("i");
    SR_CONSTEXPR static SerializationId dataId = SerializationId::Create("d");

public:
    static void Save(ISerializer& serializer, const T& value, const SerializationId& id) {
        uint64_t count = 0;

        for (auto&& item : value) {
            if (SR_UTILS_NS::Serialization::CanBeSaved(item)) {
                ++count;
            }
        }

        serializer.BeginArray(count, id);

        if constexpr (std::is_same_v<T, std::vector<bool>>) {
            for (uint32_t i = 0; i < value.size(); ++i) {
                serializer.BeginItem(itemId);
                const bool b = value[i];
                Serialization::Save(serializer, b, dataId);
                serializer.EndItem();
            }
        }
        else {
            for (auto &&item: value) {
                if (!SR_UTILS_NS::Serialization::CanBeSaved(item)) {
                    continue;
                }
                serializer.BeginItem(itemId);
                Serialization::Save(serializer, item, dataId);
                serializer.EndItem();
            }
        }

        serializer.EndArray();
    }

    static void Load(IDeserializer& deserializer, T& value, const SerializationId& id) {
        const uint64_t size = deserializer.BeginArray(id);
        if (size == 0) {
            return;
        }

        if (!deserializer.IsPreserveMode()) {
            value.clear();
        }
        else if (deserializer.ShouldSetDefaults()) {
            auto it = value.end();
            uint32_t i = static_cast<uint32_t>(value.size());
            while (it != value.begin()) {
                --it;
                --i;

                const fmt::format_int index(i);
                if (deserializer.ShouldSetDefaults(SerializationId::CreateFromCStr(index.c_str()))) {
                    it = value.erase(it);
                }
            }
        }

        if (SRVerify2(size != static_cast<size_t>(-1), "IDeserializer mustn't ever return -1 as number of elements!")) {
            value.reserve(size);
        }

        uint64_t index = 0;

        while (deserializer.BeginItem(itemId, index)) {
            if (deserializer.IsPreserveMode() && index < value.size()) {
                if constexpr (std::is_same_v<T, std::vector<bool>>) {
                    bool item = false;
                    Serialization::Load(deserializer, item, dataId);
                    value[index] = item;
                }
                else {
                    Serialization::Load(deserializer, value[index], dataId);
                }
            }
            else {
                if constexpr (std::is_same_v<T, std::vector<bool>>) {
                    value.emplace_back();
                    bool item = false;
                    Serialization::Load(deserializer, item, dataId);
                    value[index] = item;
                }
                else {
                    auto&& item = value.emplace_back();
                    Serialization::Load(deserializer, item, dataId);
                    if (!SR_UTILS_NS::Serialization::IsValidValue(item)) {
                        value.pop_back();
                    }
                }
            }

            deserializer.EndItem();
            index++;
        }

        deserializer.EndArray();
    }
};

template<typename T, class... TOther>
struct ObjectDataAccessor<std::vector<T, TOther...>> : ObjectDataAccessorVector<std::vector<T, TOther...>>
{
};

template<typename T, size_t N> struct ObjectDataAccessor<std::array<T, N>> {
    static void Save(ISerializer& serializer, const std::array<T, N>& value, const SerializationId& id) {
        uint64_t count = 0;

        for (auto&& item : value) {
            if (SR_UTILS_NS::Serialization::CanBeSaved(item)) {
                ++count;
            }
        }

        serializer.BeginArray(count, id);

        for (uint64_t i = 0; i < value.size(); ++i) {
            const auto& item = value[i];

            if (!SR_UTILS_NS::Serialization::CanBeSaved(item)) {
                continue;
            }

            if (IsValidValue(item) && (serializer.IsWriteDefaults() || !IsDefault(item))) {
                constexpr auto itemId = SerializationId::Create("item");
                constexpr auto dataId = SerializationId::Create("data");

                serializer.BeginItem(itemId);

                Serialization::Save(serializer, item, dataId);

                serializer.EndItem();
            }
        }

        serializer.EndArray();
    }

    static void Load(IDeserializer& deserializer, std::array<T, N>& value, const SerializationId& id) {
        deserializer.BeginArray(id);

        if (deserializer.IsPreserveMode() && deserializer.ShouldSetDefaults()) {
            for (size_t i = 0; i < value.size(); ++i) {
                const fmt::format_int index(i);
                if (deserializer.ShouldSetDefaults(SerializationId::CreateFromCStr(index.c_str()))) {
                    if constexpr (DefaultObjectMaker<T>::value) {
                        DefaultObjectMaker<T>::MakeDefault(value[i]);
                    }
                    else if constexpr (std::is_default_constructible_v<T>) {
                        value[i] = T();
                    }
                }
            }
        }

        std::uint64_t index = 0;

        /*while (deserializer.NextItem(id)) {
            deserializer.BeginObject(id);

            if (index < N) {
                Serialization::Load(deserializer, value[index], SerializationId::Create("item"));
                ++index;
            }
            else {
                SRHalt("Array index out of range!");
            }
            deserializer.EndObject();
        }*/

        deserializer.EndArray();
    }
};

template<typename T, typename U, typename Compare, typename Allocator>
struct ObjectDataAccessor<std::map<T, U, Compare, Allocator>> {
    using MapType = std::map<T, U, Compare, Allocator>;
    using ValueType = typename MapType::value_type;

    static_assert(std::is_arithmetic_v<T> || IsSREnumV<T> || std::is_same_v<T, std::string> || std::is_same_v<T, SR_UTILS_NS::StringAtom>, "Custom types and structs are not supported as id of map");

    static void Save(ISerializer& serializer, const MapType& value, const SerializationId& id) {
        serializer.BeginArray(value.size(), id);

        for (auto&& item : value) {
            SR_CONSTEXPR SerializationId itemId = SerializationId::Create("item");
            serializer.BeginObject(itemId);

            Serialization::Save(serializer, item.first, SerializationId::Create("first"));
            Serialization::Save(serializer, item.second, SerializationId::Create("second"));

            serializer.EndObject();
        }

        serializer.EndArray();
    }

    template<typename MapT>
    static void Load(IDeserializer& deserializer, MapT& value, const SerializationId& id) {
        const uint64_t size = deserializer.BeginArray(id);

        if (!deserializer.IsPreserveMode()) {
            value.clear();
        }
        else if (deserializer.ShouldSetDefaults()) {
            for (auto it = value.begin(); it != value.end();) {
                if (deserializer.ShouldSetDefaults(SerializationId(it->first.c_str(), 0))) {
                    it = value.erase(it);
                }
                else {
                    ++it;
                }
            }
        }

        if constexpr (SR_UTILS_NS::IsDetectedV<Details::ReserveMethodT, MapT>) {
            value.reserve(size + value.size());
        }

        /*while (deserializer.NextItem(id)) {
            if (deserializer.IsPreserveMode()) {
                deserializer.BeginObject(id);
                T element = {};
                Serialization::Load(deserializer, element, SerializationId::Create("first"));
                auto&& it = value.find(element);
                if (it != value.end()) {
                    Serialization::Load(deserializer, it->second, SerializationId::Create("second"));
                }
                else if (deserializer.AllowNewMapKeys()) {
                    U itemValue = {};
                    Serialization::Load(deserializer, itemValue, SerializationId::Create("second"));
                    if (IsValidValue(element) && IsValidValue(itemValue)) {
                        value.emplace(std::move(element), std::move(itemValue));
                    }
                }
                deserializer.EndObject();
            }
            else {
                std::pair<T, U> pair;

                Serialization::Load(deserializer, pair, id);

                if (IsValidValue(pair.first) && IsValidValue(pair.second)) {
                    value.insert(std::move(pair));
                }
            }
        }*/

        deserializer.EndArray();
    }
};

template<typename T, typename Less, typename Allocator>
struct ObjectDataAccessor<std::set<T, Less, Allocator>> {
private:
    SR_CONSTEXPR static SerializationId itemId = SerializationId::Create("i");
    SR_CONSTEXPR static SerializationId dataId = SerializationId::Create("d");

public:
    using SetType = std::set<T, Less, Allocator>;
    using ValueType = typename SetType::value_type;

    static void Save(ISerializer& serializer, const SetType& value, const SerializationId& id) {
        uint64_t count = 0;

        for (auto&& item : value) {
            if (SR_UTILS_NS::Serialization::CanBeSaved(item)) {
                ++count;
            }
        }

        serializer.BeginArray(count, id);

        for (auto&& item : value) {
            if (!SR_UTILS_NS::Serialization::CanBeSaved(item)) {
                continue;
            }
            serializer.BeginItem(itemId);
            Serialization::Save(serializer, item, dataId);
            serializer.EndItem();
        }

        serializer.EndArray();
    }

    static void Load(IDeserializer& deserializer, SetType& value, const SerializationId& id) {
        const uint64_t size = deserializer.BeginArray(id);
        if (size == 0) {
            return;
        }

        value.clear();

        uint64_t index = 0;

        while (deserializer.BeginItem(itemId, index)) {
            auto&& item = T();
            Serialization::Load(deserializer, item, dataId);
            if (SR_UTILS_NS::Serialization::IsValidValue(item)) {
                value.insert(std::move(item));
            }

            deserializer.EndItem();
            index++;
        }

        deserializer.EndArray();
    }
};

template<typename T, typename U> struct ObjectDataAccessor<std::pair<T, U>> {
    static void Save(ISerializer& serializer, const std::pair<T, U>& value, const SerializationId& id) {
        serializer.BeginObject(id);
        Serialization::Save(serializer, value.first, SerializationId::Create("first"));
        Serialization::Save(serializer, value.second, SerializationId::Create("second"));
        serializer.EndObject();
    }

    static void Load(IDeserializer& deserializer, std::pair<T, U>& value, const SerializationId& id) {
        if (!deserializer.BeginObject(id)) {
            return;
        }

        Serialization::Load(deserializer, value.first, SerializationId::Create("first"));
        Serialization::Load(deserializer, value.second, SerializationId::Create("second"));

        deserializer.EndObject();
    }
};

template<typename Type, uint64_t dim> struct ObjectDataAccessorMathVector {
    static void Save(ISerializer& serializer, const Type& value, const SerializationId& id) {
        serializer.BeginObject(id);
        if constexpr (dim >= 1) { Serialization::SaveCheckDefault(serializer, value.x, SerializationId::Create("x")); }
        if constexpr (dim >= 2) { Serialization::SaveCheckDefault(serializer, value.y, SerializationId::Create("y")); }
        if constexpr (dim >= 3) { Serialization::SaveCheckDefault(serializer, value.z, SerializationId::Create("z")); }
        if constexpr (dim >= 4) { Serialization::SaveCheckDefault(serializer, value.w, SerializationId::Create("w")); }
        if constexpr (dim >= 5) { Serialization::SaveCheckDefault(serializer, value.v, SerializationId::Create("v")); }
        if constexpr (dim >= 6) { Serialization::SaveCheckDefault(serializer, value.u, SerializationId::Create("u")); }
        serializer.EndObject();
    }

    static void Load(IDeserializer& deserializer, Type& value, const SerializationId& id) {
        if (!deserializer.BeginObject(id)) {
            return;
        }
        if constexpr (dim >= 1) { Serialization::Load(deserializer, value.x, SerializationId::Create("x")); }
        if constexpr (dim >= 2) { Serialization::Load(deserializer, value.y, SerializationId::Create("y")); }
        if constexpr (dim >= 3) { Serialization::Load(deserializer, value.z, SerializationId::Create("z")); }
        if constexpr (dim >= 4) { Serialization::Load(deserializer, value.w, SerializationId::Create("w")); }
        if constexpr (dim >= 5) { Serialization::Load(deserializer, value.v, SerializationId::Create("v")); }
        if constexpr (dim >= 6) { Serialization::Load(deserializer, value.u, SerializationId::Create("u")); }
        deserializer.EndObject();
    }
};

template<> struct ObjectDataAccessor<SR_MATH_NS::FVector2> : ObjectDataAccessorMathVector<SR_MATH_NS::FVector2, 2> {};
template<> struct ObjectDataAccessor<SR_MATH_NS::IVector2> : ObjectDataAccessorMathVector<SR_MATH_NS::IVector2, 2> {};
template<> struct ObjectDataAccessor<SR_MATH_NS::UVector2> : ObjectDataAccessorMathVector<SR_MATH_NS::UVector2, 2> {};

template<> struct ObjectDataAccessor<SR_MATH_NS::FVector3> : ObjectDataAccessorMathVector<SR_MATH_NS::FVector3, 3> {};
template<> struct ObjectDataAccessor<SR_MATH_NS::BVector3> : ObjectDataAccessorMathVector<SR_MATH_NS::BVector3, 3> {};
template<> struct ObjectDataAccessor<SR_MATH_NS::IVector3> : ObjectDataAccessorMathVector<SR_MATH_NS::IVector3, 3> {};
template<> struct ObjectDataAccessor<SR_MATH_NS::UVector3> : ObjectDataAccessorMathVector<SR_MATH_NS::UVector3, 3> {};

template<> struct ObjectDataAccessor<SR_MATH_NS::FVector4> : ObjectDataAccessorMathVector<SR_MATH_NS::FVector4, 4> {};
template<> struct ObjectDataAccessor<SR_MATH_NS::BVector4> : ObjectDataAccessorMathVector<SR_MATH_NS::BVector4, 4> {};
template<> struct ObjectDataAccessor<SR_MATH_NS::IVector4> : ObjectDataAccessorMathVector<SR_MATH_NS::IVector4, 4> {};
template<> struct ObjectDataAccessor<SR_MATH_NS::UVector4> : ObjectDataAccessorMathVector<SR_MATH_NS::UVector4, 4> {};

template<> struct ObjectDataAccessor<SR_MATH_NS::FVector6> : ObjectDataAccessorMathVector<SR_MATH_NS::FVector6, 6> {};
template<> struct ObjectDataAccessor<SR_MATH_NS::IVector6> : ObjectDataAccessorMathVector<SR_MATH_NS::IVector6, 6> {};
template<> struct ObjectDataAccessor<SR_MATH_NS::UVector6> : ObjectDataAccessorMathVector<SR_MATH_NS::UVector6, 6> {};

template<> struct ObjectDataAccessor<SR_MATH_NS::Quaternion> {
    static void Save(ISerializer& serializer, const SR_MATH_NS::Quaternion& value, const SerializationId& id) {
        serializer.BeginObject(id);
        Serialization::SaveCheckDefault(serializer, value.x, SerializationId::Create("x"));
        Serialization::SaveCheckDefault(serializer, value.y, SerializationId::Create("y"));
        Serialization::SaveCheckDefault(serializer, value.z, SerializationId::Create("z"));
        Serialization::SaveCheckDefault(serializer, value.w, SerializationId::Create("w"));
        serializer.EndObject();
    }

    static void Load(IDeserializer& deserializer, SR_MATH_NS::Quaternion& value, const SerializationId& id) {
        if (!deserializer.BeginObject(id)) {
            return;
        }
        Serialization::Load(deserializer, value.x, SerializationId::Create("x"));
        Serialization::Load(deserializer, value.y, SerializationId::Create("y"));
        Serialization::Load(deserializer, value.z, SerializationId::Create("z"));
        Serialization::Load(deserializer, value.w, SerializationId::Create("w"));
        deserializer.EndObject();
    }
};

template<> struct ObjectDataAccessor<SR_MATH_NS::FRect> {
    static void Save(ISerializer& serializer, const SR_MATH_NS::FRect& value, const SerializationId& id) {
        serializer.BeginObject(id);
        Serialization::SaveCheckDefault(serializer, value.x, SerializationId::Create("x"));
        Serialization::SaveCheckDefault(serializer, value.y, SerializationId::Create("y"));
        Serialization::SaveCheckDefault(serializer, value.w, SerializationId::Create("w"));
        Serialization::SaveCheckDefault(serializer, value.h, SerializationId::Create("h"));
        serializer.EndObject();
    }

    static void Load(IDeserializer& deserializer, SR_MATH_NS::FRect& value, const SerializationId& id) {
        if (!deserializer.BeginObject(id)) {
            return;
        }
        Serialization::Load(deserializer, value.x, SerializationId::Create("x"));
        Serialization::Load(deserializer, value.y, SerializationId::Create("y"));
        Serialization::Load(deserializer, value.w, SerializationId::Create("w"));
        Serialization::Load(deserializer, value.h, SerializationId::Create("h"));
        deserializer.EndObject();
    }
};

template<> struct ObjectDataAccessor<SR_MATH_NS::IRect> {
    static void Save(ISerializer& serializer, const SR_MATH_NS::IRect& value, const SerializationId& id) {
        serializer.BeginObject(id);
        Serialization::SaveCheckDefault(serializer, value.x, SerializationId::Create("x"));
        Serialization::SaveCheckDefault(serializer, value.y, SerializationId::Create("y"));
        Serialization::SaveCheckDefault(serializer, value.w, SerializationId::Create("w"));
        Serialization::SaveCheckDefault(serializer, value.h, SerializationId::Create("h"));
        serializer.EndObject();
    }

    static void Load(IDeserializer& deserializer, SR_MATH_NS::IRect& value, const SerializationId& id) {
        if (!deserializer.BeginObject(id)) {
            return;
        }
        Serialization::Load(deserializer, value.x, SerializationId::Create("x"));
        Serialization::Load(deserializer, value.y, SerializationId::Create("y"));
        Serialization::Load(deserializer, value.w, SerializationId::Create("w"));
        Serialization::Load(deserializer, value.h, SerializationId::Create("h"));
        deserializer.EndObject();
    }
};

template<> struct ObjectDataAccessor<SR_MATH_NS::URect> {
    static void Save(ISerializer& serializer, const SR_MATH_NS::URect& value, const SerializationId& id) {
        serializer.BeginObject(id);
        Serialization::SaveCheckDefault(serializer, value.x, SerializationId::Create("x"));
        Serialization::SaveCheckDefault(serializer, value.y, SerializationId::Create("y"));
        Serialization::SaveCheckDefault(serializer, value.w, SerializationId::Create("w"));
        Serialization::SaveCheckDefault(serializer, value.h, SerializationId::Create("h"));
        serializer.EndObject();
    }

    static void Load(IDeserializer& deserializer, SR_MATH_NS::URect& value, const SerializationId& id) {
        if (!deserializer.BeginObject(id)) {
            return;
        }
        Serialization::Load(deserializer, value.x, SerializationId::Create("x"));
        Serialization::Load(deserializer, value.y, SerializationId::Create("y"));
        Serialization::Load(deserializer, value.w, SerializationId::Create("w"));
        Serialization::Load(deserializer, value.h, SerializationId::Create("h"));
        deserializer.EndObject();
    }
};

template<typename T> struct ObjectDataAccessor<std::optional<T>> {
    static void Save(ISerializer& serializer, const std::optional<T>& value, const SerializationId& id) {
        if (value.is_initialized()) {
            Serialization::Save(serializer, value.get(), id);
        }
    }
    static void Load(IDeserializer& deserializer, std::optional<T>& value, const SerializationId& id) {
        if (!value.is_initialized()) {
            value = T();
        }
        Serialization::Load(deserializer, value.get(), id);
    }
};

template<typename T>
struct ObjectDataAccessor<T, typename std::enable_if<IsSREnumV<T>>::type> {
    static void Save(ISerializer& serializer, T value, const SerializationId& id) {
        serializer.WriteString(SR_UTILS_NS::EnumReflector::ToStringAtom<T>(value).ToStringView(), id);
    }

    static void Load(IDeserializer& deserializer, T& value, const SerializationId& id) {
        std::string enumName;
        deserializer.ReadString(enumName, id);
        if (enumName.empty()) {
            return; // Default value
        }
        if (!SR_UTILS_NS::EnumReflector::FromString<T>(enumName.c_str(), value)) {
            deserializer.ReportError("Invalid enum value \"" + enumName + " for type: {}, id: {}"_format(typeid(T).name(), id.GetName()));
        }
    }
};

template<typename T>
struct ObjectDataAccessor<SR_HTYPES_NS::SharedPtr<T>, std::enable_if_t<SerializationTraits<T>::IsSerializable>> {
    static constexpr SerializationId TYPE_ID = SerializationId::Create("type");
    static constexpr SerializationId PTR_ID = SerializationId::Create("ptr");

    static void Save(ISerializer& serializer, const SR_HTYPES_NS::SharedPtr<T>& value, const SerializationId& id) {
        if (!value) {
            return;
        }

        if (value->GetMeta()->IsEditorOnly()) {
            if (!serializer.IsEditorAllowed()) {
                return;
            }
        }

        const SRClassMeta* pMeta = value->GetMeta();
        auto&& typeName = pMeta->GetFactoryName();

        if (pMeta->IsAbstract()) {
            SR_ERROR("ObjectDataAccessor::Save() : abstract class can't be saved! Factory name: {}", typeName);
            return;
        }

        serializer.BeginObject(id);

        serializer.WriteString(typeName, TYPE_ID);

        Serialization::Save(serializer, *value, PTR_ID);

        serializer.EndObject();
    }

    static void Load(IDeserializer& deserializer, SR_HTYPES_NS::SharedPtr<T>& value, const SerializationId& id) {
        if (!deserializer.BeginObject(id)) {
            return;
        }

        std::string type;
        deserializer.ReadString(type, TYPE_ID);

        if (deserializer.IsDefault(PTR_ID)) {
            deserializer.EndObject();
            return;
        }

        if (!type.empty()) {
            if (!deserializer.IsPreserveMode()) {
                value = SR_UTILS_NS::Factory::Instance().Create<T>(type);
                if (!value) {
                    SR_ERROR("ObjectDataAccessor::Load() : unknown object's type: {}", type);
                }
            }
            else {
                const bool isNeedReAlloc = !value || type != SR_UTILS_NS::Factory::Instance().GetName(value.Get());
                if (isNeedReAlloc && deserializer.AllowReAllocPointer(value ? IDeserializer::ReAllocPointerReason::HasDifferentType : IDeserializer::ReAllocPointerReason::IsNull)) {
                    value = SR_UTILS_NS::Factory::Instance().Create<T>(type);
                    if (!value) {
                        SR_ERROR("ObjectDataAccessor::Load() : unknown object's type: {}", type);
                    }
                }
            }
        }

        if (value) {
            Serialization::Load(deserializer, *value, PTR_ID);

            SR_UTILS_NS::SerializableVerifyContext context;
            value->VerifyAfterLoad(context);

            for (auto&& warning : context.GetWarnings()) {
                SR_WARN("ObjectDataAccessor::Load() : warning: {}", warning);
            }
            for (auto&& error : context.GetErrors()) {
                SR_ERROR("ObjectDataAccessor::Load() : error: {}", error);
            }
        }

        deserializer.EndObject();
    }
};

template<typename T>
struct ObjectDataAccessor<SR_HTYPES_NS::SharedPtr<T>, std::enable_if_t<!SerializationTraits<T>::HasOriginType>> {
    static void Load(ISerializer&, SR_HTYPES_NS::SharedPtr<T>&, const SerializationId&) {
        static_assert(std::is_same_v<void, T>, "Serialization of pointers without T::OriginType error prone and forbidden!");
    }

    static void Save(IDeserializer&, const SR_HTYPES_NS::SharedPtr<T>&, const SerializationId&) {
        static_assert(std::is_same_v<void, T>, "Serialization of pointers without T::OriginType error prone and forbidden!");
    }
};
```


