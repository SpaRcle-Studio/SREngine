//
// Created by Kiper220 on 16.11.2020.
//

#include <Math/Vector3.h>
#include <Math/Quaternion.h>
#include <cmath>

#include <Math/Mathematics.h>

using namespace Framework::Helper::Math;

Vector3::Vector3(): x(0), y(0), z(0)
{ }

Vector3::Vector3(float uX, float uY, float uZ): x(uX), y(uY), z(uZ)
{ }

Vector3::Vector3(const Vector3& vector3): x(vector3.x), y(vector3.y), z(vector3.z)
{ }

Vector3 &Vector3::operator()(float uX, float uY, float uZ) {
    this->x = uX;
    this->y = uY;
    this->z = uZ;

    return *this;
}

Vector3 &Vector3::operator()(const Vector3 &vector3) {
    this->x = vector3.x;
    this->y = vector3.y;
    this->z = vector3.z;

    return *this;
}

Vector3 &Vector3::operator=(const Vector3 &vector3) {
    this->x = vector3.x;
    this->y = vector3.y;
    this->z = vector3.z;

    return *this;
}

Vector3 &Vector3::operator+=(const Vector3 &vector3) {
    this->x += vector3.x;
    this->y += vector3.y;
    this->z += vector3.z;

    return *this;
}

Vector3 &Vector3::operator-=(const Vector3 &vector3) {
    this->x -= vector3.x;
    this->y -= vector3.y;
    this->z -= vector3.z;

    return *this;
}

void Vector3::operator*=(const float s){
    this->x *= s;
    this->y *= s;
    this->z *= s;
}

Vector3& Vector3::operator %=(const Vector3& vector3){
    *this = vector3.cross(vector3);
    return *this;
}

void Vector3::operator /=(float s){
    this->x /= s;
    this->y /= s;
    this->z /= s;
}

Vector3 Vector3::operator+(const Vector3 &vector3) {
    Vector3 returnValue = *this;

    returnValue += vector3;

    return returnValue;
}

Vector3 Vector3::operator-(const Vector3 &vector3) {
    Vector3 returnValue = *this;

    returnValue -= vector3;

    return returnValue;
}

Vector3 Vector3::operator*(float s) const {
    Vector3 returnValue = *this;

    returnValue.x *= s;
    returnValue.y *= s;
    returnValue.z *= s;
    return returnValue;
}

float Vector3::operator*(const Vector3 &vector3) const {
    return this->x * vector3.x + this->y * vector3.y + this->z * vector3.z;
}

Vector3 Vector3::operator %(const Vector3& vector3) {
    return vector3.cross(vector3);
}

Vector3 Vector3::operator /(float s){
    Vector3 returnValue = *this;

    returnValue.x /= s;
    returnValue.y /= s;
    returnValue.z /= s;
    return returnValue;
}

Vector3 Vector3::RotateVectorAboutAngleAndAxis(float uAngle, Vector3 uAxis) const {
    //convert our vector to a pure quaternion
    Quaternion p(0,(*this));
    //normalize the axis
    uAxis.normalize();
    //create the real quaternion
    Quaternion q(uAngle,uAxis);
    //convert quaternion to unit norm quaternion
    q.convertToUnitNormQuaternion();
    Quaternion qInverse = q.inverse();
    Quaternion rotatedVector = q * p * qInverse;

    return rotatedVector.v;
}

Vector3 Vector3::cross(const Vector3& vector3) const {
    return Vector3( this->y * vector3.z - this->z * vector3.y,
    this->z * vector3.x - this->x * vector3.z,
    this->x * vector3.y - this->y * vector3.x);
}

Vector3 Vector3::scale(const Vector3& vector3) const {
    return Vector3( this->x * vector3.x,
    this->y * vector3.y,
    this->z * vector3.y);
}

float Vector3::magnitude() const {
    return sqrtf(this->x * this->x + this->y * this->y + this->z * this->z);
}

void Vector3::normalize() {
    float magnitude = this->magnitude();

    if(magnitude > 0.0f) {
        float oneOverMagnitude= 1.0f / magnitude;

        this->x = this->x * oneOverMagnitude;
        this->y = this->y * oneOverMagnitude;
        this->z = this->z * oneOverMagnitude;
    }
}

bool Vector3::operator==(const Vector3 &vector3) const {
    float r = this->x - vector3.x + this->y - vector3.y + this->z - vector3.z;
    return fabsf(r) < 0.0001;
}

bool Vector3::operator!=(const Vector3 &vector3) const {
    float r = this->x - vector3.x + this->y - vector3.y + this->z - vector3.z;
    return fabsf(r) >= 0.0001;
}

Vector3::operator std::string() {
    return std::string("X: ") + std::to_string(this->x) + std::string(", Y: ") + std::to_string(this->y) + std::string(", Z: ") + std::to_string(this->z) + ";";
}

Vector3::~Vector3(){}
