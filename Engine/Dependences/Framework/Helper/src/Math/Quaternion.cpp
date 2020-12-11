//
// Created by kiper220 on 16.05.2020.
//

#include <Math/Quaternion.h>
#include <cmath>
#include <string>

#include <Math/Mathematics.h>

//#define DegreesToRad(angle) angle*M_PI/180
//#define RadToDegrees(angle) angle*180/M_PI

using namespace Framework::Helper::Math;

Quaternion::Quaternion(): s(0), v(0,0,0)
{ }

Quaternion::Quaternion(float uS, const Vector3& uV): s(uS), v(uV)
{ }

Quaternion::Quaternion(const Quaternion& quaternion): s(quaternion.s), v(quaternion.v)
{ }

Quaternion& Quaternion::operator=(const Quaternion& quaternion) {
    this->s = quaternion.s;
    this->v = quaternion.v;

    return *this;
}

Quaternion Quaternion::operator +(const Quaternion& quaternion) const {
    Quaternion returnValue = *this;

    returnValue += quaternion;
    return returnValue;
}

Quaternion Quaternion::operator -(const Quaternion& quaternion) const {
    Quaternion returnValue = *this;

    returnValue -= quaternion;
    return returnValue;
}

Quaternion Quaternion::operator *(const Quaternion& quaternion) const {
    Quaternion returnValue = *this;

    returnValue *= quaternion;
    return returnValue;
}

Quaternion Quaternion::operator*(float value) const {
    Quaternion returnValue = *this;
    returnValue.s *= value;
    returnValue.v *= value;
    return returnValue;
}

void Quaternion::operator +=(const Quaternion& quaternion) {
    this->s += quaternion.s;
    this->v += quaternion.v;
}

void Quaternion::operator -=(const Quaternion& quaternion) {
    this->s -= quaternion.s;
    this->v -= quaternion.v;
}

void Quaternion::operator *=(const Quaternion& quaternion) {
    (*this) = multiply(quaternion);
}

void Quaternion::operator*=(float value) {
    this->s *= value;
    this->v *= value;
}

Quaternion Quaternion::multiply(const Quaternion& quaternion) const {
    float scalar = this->s * quaternion.s - this->v * quaternion.v;
    Vector3 imaginary = quaternion.v * this->s + this->v * quaternion.s + this->v.cross(quaternion.v);
    return Quaternion(scalar, imaginary);
}

float Quaternion::norm() const {
    float scalar=s*s;
    float imaginary=v*v;

    return sqrtf(scalar+imaginary);
}

void Quaternion::normalize() {
    if (norm()!=0) {
        float normValue=1/norm();
        s*=normValue;
        v*=normValue;
    }
}

void Quaternion::convertToUnitNormQuaternion() {
    float angle = DegreesToRad(this->s);

    v.normalize();
    s = cosf(angle*0.5);
    v = v * sinf(angle*0.5);
}

Quaternion Quaternion::conjugate() const {
    float scalar = this->s;
    Vector3 imaginary = this->v * (-1);

    return Quaternion(scalar, imaginary);
}

Quaternion Quaternion::inverse() const {
    float absoluteValue=norm();
    absoluteValue*=absoluteValue;
    absoluteValue=1/absoluteValue;

    Quaternion conjugateValue=conjugate();

    float scalar=conjugateValue.s*(absoluteValue);
    Vector3 imaginary=conjugateValue.v*(absoluteValue);

    return Quaternion(scalar,imaginary);
}

Quaternion::operator std::string() {
    return std::string("S: ") + std::to_string(this->s) + ", " + static_cast<std::string>(this->v);
}

Quaternion::~Quaternion()
{ }
