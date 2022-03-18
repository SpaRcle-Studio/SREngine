//
// Created by Monika on 12.03.2022.
//

#include <Types/Marshal.h>
#include <ResourceManager/ResourceManager.h>

namespace Framework::RuntimeTest {
    bool MarshalRunRuntimeTest() {
        /*MarshalEncodeNode node("Root node");
        MarshalEncodeNode child("Some child");

        child.Append("One", 1)
               .Append("Two", 2)
               .Append("String", "1234567890");

        node.Append(
                MarshalEncodeNode("Child 1")
                    .Append("Value 1", 50)
                    .Append("Value 2", 100)
                    .Append(child)
        );

       node.Append(
               MarshalEncodeNode("Child 2")
                    .Append("Value N", 0.15)
                    .Append("Value 3", -50)
                    .Append("Value 4", -100)
                    .Append("Value 5", "Aboba")

                    .Append(MarshalEncodeNode("Empty"))
        );

        std::cout << node.Decode().Dump() << std::endl;

        const auto path = ResourceManager::Instance().GetCachePath().Concat("RuntimeTest");
        path.Make();

        node.Save(path.Concat("Marshal.bin"));
        auto decode = MarshalDecodeNode::Load(path.Concat("Marshal.bin"));
        std::cout << decode.Dump() << std::endl;

        decode.Encode().Save(path.Concat("Marshal2.bin"));
        decode = MarshalDecodeNode::Load(path.Concat("Marshal.bin"));
        std::cout << decode.Dump() << std::endl;*/

        return true;
    }
}

std::string MarshalEncodeNode::ToString() const {
    return Save().str();
}

MarshalDecodeNode MarshalDecodeNode::Load(const Path &path) {
    MarshalDecodeNode node;

    std::ifstream file(path.ToString(), std::ios::binary);
    if (!file.is_open())
        return node;

    if (MarshalUtils::LoadValue<std::ifstream, MARSHAL_TYPE>(file) != MARSHAL_TYPE::Node) {
        file.close();
        return node;
    }

    node = std::move(MarshalUtils::LoadNode(file));
    file.close();
    return node;
}

MarshalDecodeNode &MarshalDecodeNode::AppendNode(MarshalDecodeNode&& node) {
#if SR_MARSHAL_USE_LIST
    m_nodes.emplace_back(std::move(node));
#else
    std::string name = node.m_name;

    if (auto&& pIt = m_nodes.find(name); pIt != m_nodes.end()) {
        pIt->second.emplace_back(std::move(node));
    }
    else {
        m_nodes.insert(std::make_pair(std::move(name), std::list{ std::move(node) }));
    }
#endif

    return *this;
}

std::string MarshalDecodeNode::ToJson(uint32_t tab, bool root) const {
    std::string json;

    if (root) {
        json = "{\n";
        tab += 3;
    }

    const bool emptyNode = m_attributes.empty() && m_nodes.empty();
    json.append(std::string(tab, ' ')).append("\"").append(m_name).append("\"");
    json.append(emptyNode ? ": { " : ": {\n");

    uint32_t index = 0;

#if SR_MARSHAL_USE_LIST
#else
    for (const auto& [name, attribute] : m_attributes) {
        ++index;

        if (attribute.m_data.empty())
            continue;

        json.append(std::string(tab + 3, ' '));
        json.append("\"").append(name).append("\": ");

        if (attribute.m_type == MARSHAL_TYPE::Bool) {
            if (attribute.m_data == "1")
                json.append("true");
            else
                json.append("false");
        }
        else if (MarshalUtils::IsNumber(attribute.m_type)) {
            json.append(attribute.m_data);
        }
        else if (attribute.m_type == MARSHAL_TYPE::String) {
            json.append("\"").append(attribute.m_data).append("\"");
        }

        if (index != m_attributes.size() || !m_nodes.empty())
            json.append(",");
        json.append("\n");
    }

    for (auto&& pGroupIt = std::begin(m_nodes); pGroupIt != std::end(m_nodes); ++pGroupIt) {
        for (auto&& pNodeIt = std::begin(pGroupIt->second); pNodeIt != std::end(pGroupIt->second); ++pNodeIt) {
            if (pNodeIt->m_name.empty())
                continue;

            json.append(pNodeIt->ToJson(tab + 3, false));

            if (std::next(pGroupIt) != std::end(m_nodes) || std::next(pNodeIt) != std::end(pGroupIt->second)) {
                json.append(",");
            }
            json.append("\n");
        }
    }
#endif

    json.append(emptyNode ? 0 : tab, ' ').append("}");
    if (root)
        json.append("\n}");

    return json;
}

std::string MarshalDecodeNode::Dump(uint32_t tab) const {
    std::string dump;

    dump.append(std::string(tab, ' ').append(m_name).append("\n"));

#if SR_MARSHAL_USE_LIST
#else
    for (auto&& [name, value] : m_attributes) {
        dump.append(std::string(tab + 3, ' ').append("\"").append(name).append("\"=").append(value.m_data).append("\n"));
    }

    for (auto&& [name, nodes] : m_nodes) {
        for (auto&& node : nodes)
            dump.append(node.Dump(tab + 3));
    }
#endif


    return dump;
}

std::list<MarshalDecodeNode> MarshalDecodeNode::GetNodes() const {
#if SR_MARSHAL_USE_LIST
    return m_nodes;
#else
    std::list<MarshalDecodeNode> merged;

    for (auto& [name, group] : m_nodes) {
        merged.insert(merged.end(), group.begin(), group.end());
    }

    return merged;
#endif
}

const MarshalDecodeNode& MarshalDecodeNode::GetNodeRef(const std::string &name) const {
#if SR_MARSHAL_USE_LIST
    for (const auto& node : m_nodes)
        if (node.m_name == name)
            return node;

    SRAssert(false);

    static MarshalDecodeNode def;
    return def;
#else
    auto&& pIt = m_nodes.find(name);

    if (pIt == m_nodes.end()) {
        static MarshalDecodeNode def;
        return def;
    }

    return pIt->second.front();
#endif
}

MarshalDecodeNode MarshalDecodeNode::GetNode(const std::string &name) const {
#if SR_MARSHAL_USE_LIST
    for (const auto& node : m_nodes)
        if (node.m_name == name)
            return node;

    SRAssert(false);

    return MarshalDecodeNode();
#else
    auto&& pIt = m_nodes.find(name);

    if (pIt == m_nodes.end()) {
        SRAssert(false);
        return MarshalDecodeNode();
    }

    return pIt->second.front();
#endif
}

void MarshalDecodeNode::Encode(std::stringstream& stream) const {
    uint16_t count = m_attributes.size();
#if SR_MARSHAL_USE_LIST
    count += m_nodes.size();
#else
    for (auto&& [name, group] : m_nodes) {
        count += group.size();
    }
#endif

    MarshalUtils::SaveValue(stream, MARSHAL_TYPE::Node);
    MarshalUtils::SaveShortString(stream, m_name);
    MarshalUtils::SaveValue(stream, count);

#if SR_MARSHAL_USE_LIST
    for (auto&& attribute : m_attributes) {
        MarshalUtils::SaveValue(stream, attribute.m_type);
        MarshalUtils::SaveShortString(stream, attribute.m_name);
        MarshalUtils::Encode(stream, attribute.m_data, attribute.m_type);
    }
#else
    for (auto&& [name, attribute] : m_attributes) {
        MarshalUtils::SaveValue(stream, attribute.m_type);
        MarshalUtils::SaveShortString(stream, name);
        MarshalUtils::Encode(stream, attribute.m_data, attribute.m_type);
    }
#endif

#if SR_MARSHAL_USE_LIST
    for (const auto& node : m_nodes) {
        node.Encode(stream);
    }
#else
    for (auto&& [name, group] : m_nodes) {
        for (auto &&node : group) {
            node.Encode(stream);
        }
    }
#endif
}

MarshalEncodeNode MarshalDecodeNode::Encode() const {
    MarshalEncodeNode marshal(m_name);

#if SR_MARSHAL_USE_LIST
    marshal.m_count = m_attributes.size() + m_nodes.size();

    for (const auto& attribute : m_attributes) {
        MarshalUtils::SaveValue(marshal.m_stream, attribute.m_type);
        MarshalUtils::SaveShortString(marshal.m_stream, attribute.m_name);
        MarshalUtils::Encode(marshal.m_stream, attribute.m_data, attribute.m_type);
    }

    for (const auto& node : m_nodes) {
        node.Encode(marshal.m_stream);
    }
#else
    marshal.m_count = m_attributes.size();
    for (auto&& [name, group] : m_nodes) {
        marshal.m_count = marshal.m_count + group.size();
    }

    for (auto&& [name, attribute] : m_attributes) {
        MarshalUtils::SaveValue(marshal.m_stream, attribute.m_type);
        MarshalUtils::SaveShortString(marshal.m_stream, name);
        MarshalUtils::Encode(marshal.m_stream, attribute.m_data, attribute.m_type);
    }

    for (auto&& [name, group] : m_nodes) {
        for (auto&& node : group) {
            node.Encode(marshal.m_stream);
        }
    }
#endif

    return marshal;
}

MarshalDecodeNode MarshalDecodeNode::TryGetNode(const std::string &name) const  {
#if SR_MARSHAL_USE_LIST
    for (const auto& node : m_nodes)
        if (node.m_name == name)
            return node;

    return MarshalDecodeNode();
#else
    auto&& pIt = m_nodes.find(name);

    if (pIt == m_nodes.end())
        return MarshalDecodeNode();

    return pIt->second.front();
#endif
}

MarshalDecodeNode MarshalDecodeNode::LoadFromMemory(const std::string &data) {
    MarshalDecodeNode node;

    if (data.empty() || data.size() < sizeof(MARSHAL_TYPE))
        return node;

    std::stringstream stream(data);
    if (MarshalUtils::LoadValue<std::stringstream, MARSHAL_TYPE>(stream) != MARSHAL_TYPE::Node) {
        return node;
    }

    return MarshalUtils::LoadNode(stream);
}

namespace SR_UTILS_NS {
    MarshalEncodeNode::MarshalEncodeNode() {
        m_count = 0;
    }

    MarshalEncodeNode::MarshalEncodeNode(const std::string &name)
        : m_name(name)
    {
        m_count = 0;
    }

    bool MarshalEncodeNode::Save(const Path& path, MarshalSaveMode mode) const {
        std::ofstream file;

        switch (mode) {
            case MarshalSaveMode::Binary:
                file.open(path.ToString(), std::ios::binary);
                break;
            case MarshalSaveMode::Json:
                file.open(path.ToString());
                break;
            default:
                SRAssert(false);
        }

        if (!file.is_open())
            return false;

        switch (mode) {
            case MarshalSaveMode::Binary: file << Save().rdbuf(); break;
            case MarshalSaveMode::Json: file << Decode().ToJson(); break;
        }

        file.close();
        return true;
    }

    std::stringstream MarshalEncodeNode::Save() const  {
        std::stringstream stream;

        MarshalUtils::SaveValue(stream, MARSHAL_TYPE::Node);
        MarshalUtils::SaveShortString(stream, m_name);

        MarshalUtils::SaveValue(stream, m_count);
        if (m_count) {
            /// copy buffer
            stream << m_stream.str();
        }

        return stream;
    }

    MarshalDecodeNode MarshalEncodeNode::Decode() const {
        /// copy buffer
        std::stringstream stream(m_stream.str());

        MarshalDecodeNode marshal(m_name);

        for (uint16_t i = 0; i < m_count; ++i) {
            auto&& type = MarshalUtils::LoadValue<std::stringstream, MARSHAL_TYPE>(stream);

            if (type == MARSHAL_TYPE::Node) {
                /// добавляем независимо от валидности
                auto&& node = MarshalUtils::LoadNode<std::stringstream>(stream);
                marshal.AppendNode(std::move(node));
            }
            else {
                std::string name = MarshalUtils::LoadShortStr<std::stringstream>(stream);

                switch (type) {
                    case MARSHAL_TYPE::Double: marshal.Append(std::move(name), MarshalUtils::LoadValue<std::stringstream, double_t>(stream)); break;
                    case MARSHAL_TYPE::String: marshal.Append(std::move(name), MarshalUtils::LoadStr<std::stringstream>(stream)); break;
                    case MARSHAL_TYPE::Bool:   marshal.Append(std::move(name), MarshalUtils::LoadValue<std::stringstream, bool>(stream)); break;
                    case MARSHAL_TYPE::Int8:   marshal.Append(std::move(name), MarshalUtils::LoadValue<std::stringstream, int8_t>(stream)); break;
                    case MARSHAL_TYPE::UInt8:  marshal.Append(std::move(name), MarshalUtils::LoadValue<std::stringstream, uint8_t>(stream)); break;
                    case MARSHAL_TYPE::Int16:  marshal.Append(std::move(name), MarshalUtils::LoadValue<std::stringstream, int16_t>(stream)); break;
                    case MARSHAL_TYPE::UInt16: marshal.Append(std::move(name), MarshalUtils::LoadValue<std::stringstream, uint16_t>(stream)); break;
                    case MARSHAL_TYPE::Int32:  marshal.Append(std::move(name), MarshalUtils::LoadValue<std::stringstream, int32_t>(stream)); break;
                    case MARSHAL_TYPE::UInt32: marshal.Append(std::move(name), MarshalUtils::LoadValue<std::stringstream, uint32_t>(stream)); break;
                    case MARSHAL_TYPE::Int64:  marshal.Append(std::move(name), MarshalUtils::LoadValue<std::stringstream, int64_t>(stream)); break;
                    case MARSHAL_TYPE::UInt64: marshal.Append(std::move(name), MarshalUtils::LoadValue<std::stringstream, uint64_t>(stream)); break;
                    case MARSHAL_TYPE::Float:  marshal.Append(std::move(name), MarshalUtils::LoadValue<std::stringstream, float_t>(stream)); break;
                    default:
                        break;
                }
            }
        }

        return marshal;
    }

    MarshalEncodeNode MarshalEncodeNode::LoadFromMemory(const std::string &data) {
        MarshalEncodeNode node;

        if (data.size() < sizeof(MARSHAL_TYPE)) {
            return node;
        }

        node.m_stream = std::stringstream(data);

        if (MarshalUtils::LoadValue<std::stringstream, MARSHAL_TYPE>(node.m_stream) != MARSHAL_TYPE::Node) {
            return MarshalEncodeNode();
        }

        node.m_name = MarshalUtils::LoadShortStr(node.m_stream);
        node.m_count = MarshalUtils::LoadValue<std::stringstream, uint16_t>(node.m_stream);

        return node;
    }

    MarshalEncodeNode MarshalEncodeNode::Load(const Path& path) {
        MarshalEncodeNode node;

        std::ifstream file(path.ToString(), std::ios::binary);
        if (!file.is_open())
            return node;

        if (MarshalUtils::LoadValue<std::ifstream, MARSHAL_TYPE>(file) != MARSHAL_TYPE::Node) {
            file.close();
            return node;
        }

        node.m_name = MarshalUtils::LoadShortStr(file);
        node.m_count = MarshalUtils::LoadValue<std::ifstream, uint16_t>(file);
        node.m_stream << file.rdbuf();

        file.close();

        return node;
    }
}