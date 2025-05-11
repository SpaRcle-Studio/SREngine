

# File ClassDB.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Utils**](dir_3df27e53d7cc6cea988e3644dbf87b98.md) **>** [**inc**](dir_27b05de82864f3a1e6ade431259242d5.md) **>** [**Utils**](dir_800651e705081dade93279ddf25689e7.md) **>** [**TypeTraits**](dir_ff18ecc11fc9e76cd78ef60ea36d3728.md) **>** [**ClassDB.h**](ClassDB_8h.md)

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


