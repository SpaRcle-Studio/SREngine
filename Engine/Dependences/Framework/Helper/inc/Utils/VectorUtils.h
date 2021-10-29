//
// Created by Monika on 01.09.2021.
//

#ifndef GAMEENGINE_VECTORUTILS_H
#define GAMEENGINE_VECTORUTILS_H

namespace Framework::Helper {
    class VectorUtils {
    public:
        VectorUtils() = delete;
        VectorUtils(VectorUtils &) = delete;
        ~VectorUtils() = delete;
        VectorUtils operator=(VectorUtils&) = delete;
    public:
        template<typename T> static std::vector<T> Combine(const std::vector<T>& A, const std::vector<T>& B) {
            std::vector<T> AB(A.size() + B.size()); // preallocate memory
            AB.insert(AB.end(), A.begin(), A.end());
            AB.insert(AB.end(), B.begin(), B.end());
            return AB;
        }
    };
}

#endif //GAMEENGINE_VECTORUTILS_H
