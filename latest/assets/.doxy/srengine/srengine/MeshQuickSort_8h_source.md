

# File MeshQuickSort.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Graphics**](dir_e4e4141e409277d12c2a4a311178ca74.md) **>** [**inc**](dir_e1be8c5e555e7ce65ff70a2ea1591de9.md) **>** [**Graphics**](dir_2a8d6e7cc5d2cb552d53ce15e1eac7f0.md) **>** [**Utils**](dir_1d6f88bd3f47a17aa2fb3667e19494af.md) **>** [**MeshQuickSort.h**](MeshQuickSort_8h.md)

[Go to the documentation of this file](MeshQuickSort_8h.md)


```C++
//
// Created by Monika on 31.07.2022.
//

#ifndef SR_ENGINE_MESHQUICKSORT_H
#define SR_ENGINE_MESHQUICKSORT_H

#include <Graphics/macros.h>

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

        do
        {
            while (cmp(data[i], x, pos))
                i++;

            while (cmp(x, data[j], pos))
                j--;

            if (i <= j)
            {
                SR_GTYPES_NS::Mesh* temp = data[i];
                data[i] = data[j];
                data[j] = temp;

                i++;
                j--;
            }
        }
        while (i <= j);

        if (lowestIndex < j)
            QuickSortInternal(data, pos, cmp, lowestIndex, j);

        if (i < higherIndex)
            QuickSortInternal(data, pos, cmp, i, higherIndex);

        return false;
    }
}

#endif //SR_ENGINE_MESHQUICKSORT_H
```


