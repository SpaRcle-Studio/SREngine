

# File SetUtils.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Scripting**](dir_8d890c1ced0da046da53f80c44d31720.md) **>** [**inc**](dir_7f135c995c1edef3d688ff3261945ab5.md) **>** [**Scripting**](dir_1d502c2700a8bda2469c0cfc127e6ee9.md) **>** [**Old**](dir_7c26f9091b44a892879dd4e8d1d7c144.md) **>** [**Tools**](dir_04907cd073aeacf0a44a00b3a87fc81c.md) **>** [**SetUtils.h**](SetUtils_8h.md)

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


