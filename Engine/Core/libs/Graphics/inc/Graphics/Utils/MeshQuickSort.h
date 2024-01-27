//
// Created by Monika on 31.07.2022.
//

#ifndef SR_ENGINE_MESHQUICKSORT_H
#define SR_ENGINE_MESHQUICKSORT_H

#include <Utils/stdInclude.h>
#include <Utils/Math/Vector3.h>

namespace SR_GTYPES_NS {
    class Mesh;
}

namespace SR_GRAPH_NS {
    typedef bool(*MeshQSortCmpFn)(const SR_GTYPES_NS::Mesh *left, const SR_GTYPES_NS::Mesh *right, const SR_MATH_NS::FVector3& pos);

   //bool SR_FASTCALL MeshQSortCmpGreater(const SR_GTYPES_NS::Mesh *left, const SR_GTYPES_NS::Mesh *right, const SR_MATH_NS::FVector3& pos) {
   //    return left->Distance(pos) < right->Distance(pos);
   //}

    bool SR_FASTCALL QuickSort(SR_GTYPES_NS::Mesh **data, const SR_MATH_NS::FVector3& pos, MeshQSortCmpFn cmp, uint32_t count);
    bool SR_FASTCALL QuickSortInternal(SR_GTYPES_NS::Mesh **data, const SR_MATH_NS::FVector3& pos, MeshQSortCmpFn cmp, uint32_t lowestIndex, uint32_t higherIndex);
}

namespace SR_GRAPH_NS {
    bool QuickSort(SR_GTYPES_NS::Mesh **data, const SR_MATH_NS::FVector3& pos, MeshQSortCmpFn cmp, uint32_t count) {
        return QuickSortInternal(data, pos, cmp, 0, count - 1);
    }

    bool QuickSortInternal(SR_GTYPES_NS::Mesh **data, const SR_MATH_NS::FVector3& pos, MeshQSortCmpFn cmp, uint32_t lowestIndex, uint32_t higherIndex) {
        int i = lowestIndex, j = higherIndex;
        SR_GTYPES_NS::Mesh* x = data[(lowestIndex + higherIndex) / 2];

        ///  partition
        do
        {
            while (cmp(data[i], x, pos))
                i++;

            while (cmp(x, data[j], pos))
                j--;

            if (i <= j)
            {
                /// swap(i, j);
                SR_GTYPES_NS::Mesh* temp = data[i];
                data[i] = data[j];
                data[j] = temp;

                i++;
                j--;
            }
        }
        while (i <= j);

        ///  recursion
        if (lowestIndex < j)
            QuickSortInternal(data, pos, cmp, lowestIndex, j);

        if (i < higherIndex)
            QuickSortInternal(data, pos, cmp, i, higherIndex);

        return false;
    }
}

#endif //SR_ENGINE_MESHQUICKSORT_H
