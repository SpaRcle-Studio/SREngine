

# File Numeric.h

[**File List**](files.md) **>** [**Common**](dir_3494e32b0a79d085f92ff9f3955f97da.md) **>** [**Numeric.h**](Numeric_8h.md)

[Go to the documentation of this file](Numeric_8h.md)


```C++
//
// Created by Monika on 22.09.2021.
//

#ifndef SR_ENGINE_NUMERIC_H
#define SR_ENGINE_NUMERIC_H

#include <Utils/Common/Singleton.h>

namespace SR_UTILS_NS {
    class Random : public Singleton<Random> {
        SR_REGISTER_SINGLETON(Random)
    private:
        Random();
        ~Random() override = default;

    public:
        static void Initialize();

        template<typename T> void Shuffle(std::vector<T>& vector);

        SR_NODISCARD float_t Float(float_t minimum, float_t maximum);
        SR_NODISCARD int32_t Int32Range(int32_t minimum, int32_t maximum);
        SR_NODISCARD int64_t Int64();
        SR_NODISCARD uint64_t UInt64();
        SR_NODISCARD int32_t Int32();
        SR_NODISCARD uint32_t UInt32();

    private:
        std::default_random_engine m_generator;

        std::random_device m_randomDevice;
        std::mt19937_64 m_e2;
        std::uniform_int_distribution<int64_t> m_dist;

    };

    template<typename T> void Random::Shuffle(std::vector<T>& vector) {
        std::shuffle(std::begin(vector), std::end(vector), m_randomDevice);
    }
}

#endif //SR_ENGINE_NUMERIC_H
```


