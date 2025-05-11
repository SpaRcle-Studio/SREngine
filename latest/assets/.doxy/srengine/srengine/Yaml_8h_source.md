

# File Yaml.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Utils**](dir_3df27e53d7cc6cea988e3644dbf87b98.md) **>** [**inc**](dir_27b05de82864f3a1e6ade431259242d5.md) **>** [**Utils**](dir_800651e705081dade93279ddf25689e7.md) **>** [**Resources**](dir_97f93f5c84d133c6e09e46b256597939.md) **>** [**Yaml.h**](Yaml_8h.md)

[Go to the documentation of this file](Yaml_8h.md)


```C++
//
// Created by innerviewer on 2024-06-08.
//

#ifndef SR_COMMON_YAML_H
#define SR_COMMON_YAML_H

#include <Utils/Common/NonCopyable.h>

namespace SR_UTILS_NS::Yaml {
    class SR_COMMON_DLL_API Node {
        friend class Document;

    public:
        Node() = default;

        explicit Node(void const* pTreeImpl, const size_t id)
            : m_constTreeImpl(pTreeImpl)
            , m_id(id)
        { }

        explicit Node(void* pTreeImpl, const size_t id)
            : m_treeImpl(pTreeImpl)
            , m_id(id)
        { }

    public:
        static Node Empty() { return Node(); }

        explicit operator bool() const { return IsValid(); }
        SR_NODISCARD bool IsValid() const { return (m_treeImpl || m_constTreeImpl) && m_id != -1; }

        SR_NODISCARD std::string Name() const;
        SR_NODISCARD std::string_view NameView() const;

        SR_NODISCARD void SetValue(const std::string_view& value);
        SR_NODISCARD std::string GetValue() const;
        SR_NODISCARD std::string_view GetValueView() const;
        SR_NODISCARD std::string GetKey() const;
        SR_NODISCARD std::string_view GetKeyView() const;
        SR_NODISCARD std::vector<Node> GetChildren() const;
        SR_NODISCARD uint16_t GetId() const;
        SR_NODISCARD Node GetChild(const std::string_view& name) const;
        SR_NODISCARD Node AppendChild(const std::string_view& name);

    private:
        void* GetTreeImpl() { return m_treeImpl; }
        void const* GetTreeImpl() const { return m_constTreeImpl ? m_constTreeImpl : m_treeImpl; }

    private:
        void const* m_constTreeImpl = nullptr;
        void* m_treeImpl = nullptr;
        size_t m_id = -1;
    };

    class SR_COMMON_DLL_API Document final : public NonCopyable {
    public:
        Document() = default;
        ~Document() override;

        Document(Document&& document) noexcept;
        Document& operator=(Document&& document) noexcept;
        explicit operator bool() const { return IsValid(); }

    public:
        static Document Empty();
        static Document New();
        static Document Load(const SR_UTILS_NS::Path &path);

    public:
        Node AppendChild(const std::string_view& name);

        SR_NODISCARD bool Save(const SR_UTILS_NS::Path& path) const;
        SR_NODISCARD std::string Dump() const;

        SR_NODISCARD Node GetRoot() const;
        SR_NODISCARD Node GetRoot();
        SR_NODISCARD bool IsValid() const { return m_pImpl; }

    private:
        void* m_pImpl = nullptr;
        SR_UTILS_NS::Path m_path;
    };
}

#endif //SR_COMMON_YAML_H
```


