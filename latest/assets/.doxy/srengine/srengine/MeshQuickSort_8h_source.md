

# File MeshQuickSort.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Graphics**](dir_3963f30637b7260601ed2fee5486623e.md) **>** [**inc**](dir_cf695446dee09d9ecb81ac3a708470c3.md) **>** [**Graphics**](dir_7d904954ae4eb5028070508fad42280f.md) **>** [**Utils**](dir_08379350d528ecfd47c79c18ec259ee8.md) **>** [**MeshQuickSort.h**](MeshQuickSort_8h.md)

[Go to the documentation of this file](MeshQuickSort_8h.md)


```C++
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


