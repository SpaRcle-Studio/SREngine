

# File NonCopyable.h

[**File List**](files.md) **>** [**Common**](dir_964cfbb3f15edef5ecfb3ae3bc01626c.md) **>** [**NonCopyable.h**](NonCopyable_8h.md)

[Go to the documentation of this file](NonCopyable_8h.md)


```C++
//
// Created by Monika on 16.01.2022.
//

#ifndef SR_ENGINE_NONCOPYABLE_H
#define SR_ENGINE_NONCOPYABLE_H

#include <Utils/stdInclude.h>

namespace SR_UTILS_NS {
    class SR_COMMON_DLL_API NonCopyable {
    protected:
        NonCopyable();
        virtual ~NonCopyable();

    public:
        NonCopyable(const NonCopyable&) = delete;
        virtual NonCopyable& operator=(const NonCopyable&) = delete;

    };

    class SR_COMMON_DLL_API NonMovable {
    protected:
        NonMovable();
        virtual ~NonMovable();

    public:
        NonMovable(NonMovable&&) = delete;
        virtual NonMovable& operator=(NonMovable&&) = delete;

    };

    class SR_COMMON_DLL_API ICloneable {
    protected:
        ICloneable();
        virtual void OnCloned();

    public:
        virtual ~ICloneable();
        SR_NODISCARD virtual ICloneable* Clone() const = 0;

    };
}

#endif //SR_ENGINE_NONCOPYABLE_H
```


