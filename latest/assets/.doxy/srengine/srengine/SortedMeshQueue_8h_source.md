

# File SortedMeshQueue.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Graphics**](dir_e4e4141e409277d12c2a4a311178ca74.md) **>** [**inc**](dir_e1be8c5e555e7ce65ff70a2ea1591de9.md) **>** [**Graphics**](dir_2a8d6e7cc5d2cb552d53ce15e1eac7f0.md) **>** [**Render**](dir_043f3e6d57945a3feea385b5c8b9609d.md) **>** [**SortedMeshQueue.h**](SortedMeshQueue_8h.md)

[Go to the documentation of this file](SortedMeshQueue_8h.md)


```C++
//
// Created by Monika on 31.07.2022.
//

#ifndef SR_ENGINE_SORTEDMESHQUEUE_H
#define SR_ENGINE_SORTEDMESHQUEUE_H

#include <Graphics/macros.h>

#include <Utils/Debug.h>
#include <Utils/Math/Vector3.h>
#include <Utils/Types/Map.h>

namespace SR_GTYPES_NS {
    class Mesh;
    class Shader;
}

namespace SR_GRAPH_NS {
    class SortedMeshQueue : public SR_UTILS_NS::NonCopyable {
    public:
        using MeshPtr = SR_GTYPES_NS::Mesh*;
        using ShaderPtr = SR_GTYPES_NS::Shader*;

        using Iterator = std::vector<MeshPtr>::iterator;
        using ConstIterator = std::vector<MeshPtr>::const_iterator;
        using ReverseIterator = std::vector<MeshPtr>::reverse_iterator;
        using ReverseConstIterator = std::vector<MeshPtr>::const_reverse_iterator;

        SortedMeshQueue();
        ~SortedMeshQueue() override = default;

    public:
        SR_NODISCARD Iterator begin() noexcept { return m_queue.begin(); }
        SR_NODISCARD Iterator end() noexcept { return m_queue.end(); }

        SR_NODISCARD ConstIterator begin() const noexcept { return m_queue.begin(); }
        SR_NODISCARD ConstIterator end() const noexcept { return m_queue.end(); }

        SR_NODISCARD bool empty() const noexcept { return m_queue.empty(); }

        SR_NODISCARD const std::vector<MeshPtr>& GetQueue() const { return m_queue; }

        void SetTarget(const SR_MATH_NS::FVector3& target);

        bool Add(MeshPtr pMesh);
        bool Remove(MeshPtr pMesh);

        void Clear();

        bool Sort();

    protected:
        void SortInternal(uint32_t lowestIndex, uint32_t higherIndex);

    protected:
        bool m_dirty = false;
        SR_MATH_NS::FVector3 m_target;
        std::vector<MeshPtr> m_queue;
        MeshPtr* m_data = nullptr;

    };

    class SortedOpaqueMeshQueue : public SortedMeshQueue {
    public:
        ~SortedOpaqueMeshQueue() override = default;

    };

    class SortedTransparentMeshQueue : public SortedMeshQueue {
    public:
        ~SortedTransparentMeshQueue() override = default;

    };
}

#endif //SR_ENGINE_SORTEDMESHQUEUE_H
```


