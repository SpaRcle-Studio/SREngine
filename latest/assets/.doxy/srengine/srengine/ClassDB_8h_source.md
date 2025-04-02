

# File ClassDB.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Utils**](dir_f3d6dc6978aa78088efd06c6b2710310.md) **>** [**inc**](dir_e0f1b8570fc577fb78354cd460e9e760.md) **>** [**Utils**](dir_06a42b3e946fb631201a76a22d1aab06.md) **>** [**TypeTraits**](dir_16c2d3fce5275752976e0da6f3af1bdb.md) **>** [**ClassDB.h**](ClassDB_8h.md)

[Go to the documentation of this file](ClassDB_8h.md)


```C++
//
// Created by Monika on 09.10.2024.
//

#ifndef SR_COMMON_CLASS_DB_H
#define SR_COMMON_CLASS_DB_H

#include <Utils/Common/NonCopyable.h>
#include <Utils/Types/StringAtom.h>
#include <Utils/Types/Mutex.h>

namespace SR_UTILS_NS {
    class SRClass;

    struct ClassInfo {
        StringAtom name;
        StringAtom inherits;
        ClassInfo* pInherits = nullptr;
    };

    class ClassDB : public NonCopyable, public NonMovable {
    private:
        ClassDB() = default;
        ~ClassDB() override = default;

    public:
        static ClassDB& Instance();

        void ResolveInheritance();

        bool RegisterNewClass(StringAtom className);
        bool RegisterInheritance(StringAtom className, StringAtom inherits);
        bool RegisterProperty(StringAtom className, StringAtom propertyType, StringAtom propertyName);

    private:
        bool m_inheritanceResolved = false;
        std::shared_mutex m_mutex;
        std::unordered_map<StringAtom, ClassInfo> m_classes;
        std::unordered_map<StringAtom, std::vector<StringAtom>> m_inheritance;

    };
}

#endif //SR_COMMON_CLASS_DB_H
```


