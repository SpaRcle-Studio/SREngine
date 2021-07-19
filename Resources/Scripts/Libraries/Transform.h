//
// Created by Evo Script code generator on Mon Jul 19 20:12:25 2021 | Author - Monika
//

#ifndef EVOSCRIPTLIB_TRANSFORM_H
#define EVOSCRIPTLIB_TRANSFORM_H

#include "Math/Vector3.h"
#include "Standard/Addresses.h"

class GameObject;

class Transform {
private:
	Vector3 m_localPosition;
	Vector3 m_localRotation;
	Vector3 m_localScale;
	Vector3 m_globalPosition;
	Vector3 m_globalRotation;
	Vector3 m_globalScale;
	GameObject* m_gameObject;
	Transform* m_parent;
public:
	Vector3 Forward() {
		void* voidPtr = g_methodPointers[93];
		typedef Vector3 (Transform::*ClassPtr)();
		auto origPtr = *reinterpret_cast<ClassPtr*>(&voidPtr);
		return (*this.*origPtr)();
	}
	Vector3 Right() {
		void* voidPtr = g_methodPointers[94];
		typedef Vector3 (Transform::*ClassPtr)();
		auto origPtr = *reinterpret_cast<ClassPtr*>(&voidPtr);
		return (*this.*origPtr)();
	}
	Vector3 Up() {
		void* voidPtr = g_methodPointers[95];
		typedef Vector3 (Transform::*ClassPtr)();
		auto origPtr = *reinterpret_cast<ClassPtr*>(&voidPtr);
		return (*this.*origPtr)();
	}
	void Translate(Vector3 arg0) {
		void* voidPtr = g_methodPointers[96];
		typedef void (Transform::*ClassPtr)(Vector3 arg0);
		auto origPtr = *reinterpret_cast<ClassPtr*>(&voidPtr);
		return (*this.*origPtr)(arg0);
	}
	void Rotate(Vector3 arg0) {
		void* voidPtr = g_methodPointers[97];
		typedef void (Transform::*ClassPtr)(Vector3 arg0);
		auto origPtr = *reinterpret_cast<ClassPtr*>(&voidPtr);
		return (*this.*origPtr)(arg0);
	}
};

#endif