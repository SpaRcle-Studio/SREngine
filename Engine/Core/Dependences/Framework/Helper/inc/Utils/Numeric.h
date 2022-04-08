//
// Created by Monika on 22.09.2021.
//

#ifndef GAMEENGINE_NUMERIC_H
#define GAMEENGINE_NUMERIC_H

#include <Utils/Singleton.h>

namespace SR_UTILS_NS {
    class Random : public Singleton<Random> {
        friend class Singleton<Random>;
    private:
        Random()
            : m_e2(m_randomDevice())
            , m_dist(std::llround(std::pow(2,61))
            , std::llround(std::pow(2,62)))
        { }

    public:
        int64_t Int64() {
            return m_dist(m_e2);
        }

    private:
        std::random_device m_randomDevice;
        std::mt19937_64 m_e2;
        std::uniform_int_distribution<int64_t> m_dist;

    };
}

#endif //GAMEENGINE_NUMERIC_H
