//
// Created by kiper220 on 16.05.2020.
//
#ifndef EVOENGINE_QUATERNION_H
#define EVOENGINE_QUATERNION_H

#include <Math/Vector3.h>

namespace Framework::Helper::Math {
    class Quaternion {
    public:
        /**
         * \brief Default zero constructor
         */
        Quaternion();

        /**
         * \brief Default data constructor
         */
        Quaternion(float uS, const Vector3 &uV);

        /**
         * \brief Default copy constructor
         */
        Quaternion(const Quaternion &quaternion);

        /**
         * \brief Default copy operator
         */
        Quaternion &operator=(const Quaternion &quaternion);

        /**
         * \brief Default overload operator+(const Quaternion&)(const)
         * \return result of a mathematical operation
         */
        Quaternion operator+(const Quaternion &quaternion) const;

        /**
         * \brief Default overload operator-(const Quaternion&)(const)
         * \return result of a mathematical operation
         */
        Quaternion operator-(const Quaternion &quaternion) const;

        /**
         * \brief Default overload operator*(const Quaternion&)(const)
         * \return result of a mathematical operation
         */
        Quaternion operator*(const Quaternion &quaternion) const;

        /**
         * \brief Default overload operator*(float)(const)
         * \return result of a mathematical operation
         */
        Quaternion operator*(float value) const;

        /**
         * \brief Quaternion overload operator+=(const Quaternion&)
         */
        void operator+=(const Quaternion &quaternion);

        /**
         * \brief Quaternion overload operator-=(const Quaternion&)
         */
        void operator-=(const Quaternion &quaternion);

        /**
         * \brief Quaternion overload operator*=(const Quaternion&)
         */
        void operator*=(const Quaternion &quaternion);

        /**
         * \brief Quaternion overload operator*=(float)
         */
        void operator*=(float value);

        /**
         * \brief Quaternion multiply
         * \arg quaternion - multiply target;
         * \return Multiply result
         */
        Quaternion multiply(const Quaternion &quaternion) const;

        /**
         * \brief Quaternion norm
         * \return Norm result
         */
        float norm() const;

        /**
         * \brief Quaternion normalize
         */
        void normalize();

        /**
         * \brief Quaternion convert to unit norm quaternion function
         */
        void convertToUnitNormQuaternion();

        /**
         * \brief Quaternion conjugate
         * \return Conjugate result
         */
        Quaternion conjugate() const;

        /**
         * \brief Quaternion inverse
         * \return Inverse result
         */
        Quaternion inverse() const;

        /**
         * \brief Overload operator String(const)
         */
        operator std::string();

        /**
         * \brief Standart destructor
         */
        ~Quaternion();

        /**
         * \brief Quaternion Data(s)
         */
        float s;
        /**
         * \brief Quaternion Data(v)
         */
        Vector3 v;
    };
}


#endif //EVOENGINE_QUATERNION_H
