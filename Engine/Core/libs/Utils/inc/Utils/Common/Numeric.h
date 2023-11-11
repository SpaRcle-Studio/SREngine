//
// Created by Monika on 22.09.2021.
//

#ifndef SR_ENGINE_NUMERIC_H
#define SR_ENGINE_NUMERIC_H

#include <Utils/Common/Singleton.h>

namespace SR_UTILS_NS {
    class SR_DLL_EXPORT Random : public Singleton<Random> {
        SR_REGISTER_SINGLETON(Random)
    private:
        Random()
            : m_generator(clock())
            , m_randomDevice()
            , m_e2(m_randomDevice())
            , m_dist(std::llround(std::pow(2, 61))
            , std::llround(std::pow(2, 62)))
        { }

        ~Random() override = default;

    public:
        static void Initialize() {
            srand(time(NULL)); /// NOLINT
        }

        template<typename T> void Shuffle(std::vector<T>& vector) {
            std::shuffle(std::begin(vector), std::end(vector), m_randomDevice);
        }

        SR_NODISCARD float_t Float(float_t minimum, float_t maximum) {
            std::uniform_real_distribution<float_t> distribution(minimum, maximum);
            return distribution(m_generator);
        }

        SR_NODISCARD int32_t Int32Range(int32_t minimum, int32_t maximum) {
            std::uniform_int_distribution<int32_t> distribution(minimum, maximum);
            return distribution(m_generator);
        }

        SR_NODISCARD int64_t Int64() {
            return m_dist(m_e2);
        }

        SR_NODISCARD int32_t Int32() {
            return static_cast<int32_t>(m_dist(m_e2));
        }

        SR_NODISCARD uint32_t UInt32() {
            return static_cast<uint32_t>(m_dist(m_e2));
        }

    private:
        std::default_random_engine m_generator;

        std::random_device m_randomDevice;
        std::mt19937_64 m_e2;
        std::uniform_int_distribution<int64_t> m_dist;

    };
}

#endif //SR_ENGINE_NUMERIC_H
