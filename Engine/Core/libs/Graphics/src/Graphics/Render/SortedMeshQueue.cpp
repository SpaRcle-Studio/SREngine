//
// Created by Monika on 31.07.2022.
//

#include <Graphics/Utils/MeshQuickSort.h>
#include <Graphics/Render/SortedMeshQueue.h>
#include <Graphics/Types/Mesh.h>

namespace SR_GRAPH_NS {
    SortedMeshQueue::SortedMeshQueue()
        : m_queue()
    {
        m_queue.reserve(1024);
    }

    bool SortedMeshQueue::Sort() {
        if (m_queue.size() < 2) {
            return false;
        }

        m_data = m_queue.data();

        SortInternal(0, m_queue.size() - 1);

        if (m_dirty) {
            m_dirty = false;
            return true;
        }

        return false;
    }

    bool SortedMeshQueue::Add(SortedMeshQueue::MeshPtr pMesh) {
        m_queue.emplace_back(pMesh);
        return true;
    }

    bool SortedMeshQueue::Remove(SortedMeshQueue::MeshPtr pMesh) {
        for (auto pIt = std::begin(m_queue); pIt != std::end(m_queue); ) {
            if (*pIt == pMesh) {
                pIt = m_queue.erase(pIt);
                return true;
            }
            else
                ++pIt;
        }

        SRHalt("SortedMeshQueue::Remove() : mesh not found!");

        return false;
    }

    void SortedMeshQueue::SetTarget(const SR_MATH_NS::FVector3& target) {
        m_target = target;
    }

    void SortedMeshQueue::Clear() {
        auto&& size = m_queue.size();
        m_queue.clear();
        m_queue.reserve(size);
    }

    void SortedMeshQueue::SortInternal(uint32_t lowestIndex, uint32_t higherIndex) {
        int32_t i = lowestIndex, j = higherIndex;
       // SR_GTYPES_NS::Mesh* x = m_data[(lowestIndex + higherIndex) / 2];

        ///  partition
        do
        {
            //while (static_cast<int32_t>(m_data[i]->Distance(m_target)) < static_cast<int32_t>(x->Distance(m_target)))
            //    i++;
//
            //while (static_cast<int32_t>(x->Distance(m_target)) < static_cast<int32_t>(m_data[j]->Distance(m_target)))
            //    j--;

            if (i <= j)
            {
                /// swap(i, j);
                //if (static_cast<int32_t>(m_data[i]->Distance(m_target)) > static_cast<int32_t>(m_data[j]->Distance(m_target))) {
                //    SR_GTYPES_NS::Mesh *temp = m_data[i];
                //    m_data[i] = m_data[j];
                //    m_data[j] = temp;
//
                //    m_dirty = true;
                //}

                i++;
                j--;
            }
        }
        while (i <= j);

        ///  recursion
        if (static_cast<int32_t>(lowestIndex) < j)
            SortInternal(lowestIndex, j);

        if (i < static_cast<int32_t>(higherIndex))
            SortInternal(i, higherIndex);
    }
}