

# File NodeDictionary.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Utils**](dir_f3d6dc6978aa78088efd06c6b2710310.md) **>** [**inc**](dir_e0f1b8570fc577fb78354cd460e9e760.md) **>** [**Utils**](dir_06a42b3e946fb631201a76a22d1aab06.md) **>** [**Types**](dir_e2eff6081ed67c5bc03a553ef17d8efc.md) **>** [**NodeDictionary.h**](NodeDictionary_8h.md)

[Go to the documentation of this file](NodeDictionary_8h.md)


```C++
//
// Created by Monika on 19.02.2024.
//

#ifndef SR_UTILS_TYPES_NODE_DICTIONARY_H
#define SR_UTILS_TYPES_NODE_DICTIONARY_H

#include <Utils/Types/LinkedList.h>
#include <Utils/Types/BinarySearchTree.h>

namespace SR_HTYPES_NS {
    template<typename T> class DictionaryEntry : public SR_UTILS_NS::NonCopyable {
        using Super = SR_UTILS_NS::NonCopyable;
    public:
        DictionaryEntry(T* pKey, uint64_t keySize, T* pValue, uint64_t valueSize)
            : Super()
            , m_keySize(keySize)
            , m_valueSize(valueSize)
        {
            m_key = (T*)malloc(keySize);
            memcpy(m_key, pKey, keySize);

            m_value = (T*)malloc(valueSize);
            memcpy(m_value, pValue, valueSize);
        }

        ~DictionaryEntry() override {
            if (m_key != nullptr) {
                free(m_key);
                m_key = nullptr;
            }

            if (m_value != nullptr) {
                free(m_value);
                m_value = nullptr;
            }
        }

        SR_NODISCARD T* GetKey() const { return m_key; }
        SR_NODISCARD uint64_t GetKeySize() const { return m_keySize; }
        SR_NODISCARD T* GetValue() const { return m_value; }
        SR_NODISCARD uint64_t GetValueSize() const { return m_valueSize; }

    private:
        T* m_key = nullptr;
        T* m_value = nullptr;

        uint64_t m_keySize = 0;
        uint64_t m_valueSize = 0;

    };

    template<typename T> class NodeDictionary : public SR_UTILS_NS::NonCopyable {
        using Comparator = std::function<uint32_t(T* pA, T* pB)>;
    public:
        void Insert(T* pKey, uint64_t keySize, T* pValue, uint64_t valueSize);
        SR_NODISCARD T* Search(T* pKey, uint64_t keySize) const;

    private:
        LinkedList<T> m_keys;
        BinarySearchTree<T> m_binarySearchTree;

    };

    template<typename T> T* NodeDictionary<T>::Search(T* pKey, uint64_t keySize) const {
        int32_t dummyValue = 0;
        auto&& entry = DictionaryEntry<T>(pKey, keySize, &dummyValue, sizeof(dummyValue));
        auto* pResult = m_binarySearchTree.Search(&entry);
        return pResult != nullptr ? pResult->GetValue() : nullptr;
    }

    template<typename T> void NodeDictionary<T>::Insert(T* pKey, uint64_t keySize, T* pValue, uint64_t valueSize) {
        auto&& entry = DictionaryEntry<T>(pKey, keySize, pValue, valueSize);
        m_binarySearchTree.Insert(&entry, sizeof(entry));
        m_keys.Insert(m_keys.Length(), pKey, keySize);
    }
}

#endif //SR_UTILS_TYPES_NODE_DICTIONARY_H
```


