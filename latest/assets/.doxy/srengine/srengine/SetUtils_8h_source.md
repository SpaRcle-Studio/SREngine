

# File SetUtils.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Scripting**](dir_5986759bc4f73c4edd437f1c9a37190d.md) **>** [**inc**](dir_4119b3a7205d9e389f51f0e00ee95b80.md) **>** [**Scripting**](dir_b374709534ecc2762456a7a7dcb6760c.md) **>** [**Old**](dir_b244a4bff51c9cedd445e3d7c2557c90.md) **>** [**Tools**](dir_34b1643912c4d8f0022f3f30c24098db.md) **>** [**SetUtils.h**](SetUtils_8h.md)

[Go to the documentation of this file](SetUtils_8h.md)


```C++
//
// Created by Nikita on 10.07.2021.
//

#ifndef SR_ENGINE_SCRIPTING_SET_UTILS_H
#define SR_ENGINE_SCRIPTING_SET_UTILS_H

#include <set>
#include <iostream>

namespace EvoScript::Tools {
    template<typename T> std::set<T> Merge(const std::set<T>& s1, const std::set<T>& s2) {
        std::set<T> s3 = s1;
        s3.insert(s2.begin(), s2.end());
        return s3;
    }

    template<typename T> void PrintSet(const std::set<T>& s) {
        for (auto it = s.begin(); it != s.end(); ++it)
            std::cout << *it << ' ';
        std::cout << std::endl;
    }
}

#endif //SR_ENGINE_SCRIPTING_SET_UTILS_H
```


