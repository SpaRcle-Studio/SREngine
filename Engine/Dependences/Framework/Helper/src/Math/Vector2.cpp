//
// Created by kiper220 on 16.05.2020.
//

#include <Math/Vector2.h>
#include <string>

#include <Math/Mathematics.h>

using namespace Framework::Helper::Math;

Vector2::Vector2(): x(0), y(0){}
Vector2::Vector2(float uX, float uY): x(uX), y(uY){}
Vector2::Vector2(const Vector2& vector2): x(vector2.x), y(vector2.y){}

Vector2& Vector2::operator()(float uX, float uY) {
    this->x = uX;
    this->y = uY;
    return *this;
}

Vector2& Vector2::operator()(const Vector2& vector2) {
    this->x = vector2.x;
    this->y = vector2.y;
    return *this;
}

Vector2& Vector2::operator =(const Vector2& vector2) {
    this->x = vector2.x;
    this->y = vector2.y;
    return *this;
}

Vector2& Vector2::operator+=(const Vector2& vector2) {
    this->x += vector2.x;
    this->y += vector2.x;
    return *this;
}

Vector2& Vector2::operator-=(const Vector2& vector2) {
    this->x -= vector2.x;
    this->y -= vector2.y;
    return *this;
}

void Vector2::operator*=(float s) {
    this->x *= s;
    this->y *= s;
}

void Vector2::operator /=(float s) {
    this->x /= s;
    this->y /= s;
}

Vector2 Vector2::operator +(const Vector2& vector2) {
    return {this->x + vector2.x,this->x + vector2.y};
}

Vector2 Vector2::operator -(const Vector2& vector2) {
    return {this->x - vector2.x,this->y - vector2.y};
}

float Vector2::operator *(const Vector2& vector2) const {
    return this->x * vector2.x + this->y * vector2.y;
}

Vector2 Vector2::operator*(float s) const {
    return {this->x / s, this->y / s};
}

float Vector2::operator %(const Vector2& vector2) {
    return vector2.cross(vector2);
}

Vector2 Vector2::operator /(float s){
    return {this->x / s, this->y / s};
}

Vector2 Vector2::RotateVectorAboutAngle(float uAngle) const {
    return {
        cosf(DegreesToRad(uAngle)) * this->x -
        cosf(DegreesToRad(uAngle)) * this->y,

        sinf(DegreesToRad(uAngle)) * this->x +
        cosf(DegreesToRad(uAngle)) * this->y
    };
}

float Vector2::cross(const Vector2& vector2) const {
    return this->x * vector2.y - this->y * vector2.x;
}

float Vector2::magnitude() const {
    return sqrtf(this->x * this->x + this->y * this->y);
}

void Vector2::normalize(){
    float magnitude = this->magnitude();

    if(magnitude > 0.0f){
    float oneOverMagnitude= 1.0f / magnitude;

    this->x = this->x * oneOverMagnitude;
    this->y = this->y * oneOverMagnitude;
    }
}

bool Vector2::operator ==(const Vector2& vector2) const {
    float r = this->x - vector2.x + this->y - vector2.y;
    return fabsf(r) < 0.0001;
}

bool Vector2::operator !=(const Vector2& vector2) const {
    float r = this->x - vector2.x + this->y - vector2.y;
    return fabsf(r) < 0.0001;
}

Vector2::operator std::string() {
    return std::string("X: ") + std::to_string(this->x) + std::string(", Y: ") + std::to_string(this->y) + ";";
}

Vector2::~Vector2() = default;
//    }
//}
