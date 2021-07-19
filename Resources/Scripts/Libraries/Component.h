//
// Created by Evo Script code generator on Mon Jul 19 20:12:25 2021 | Author - Monika
//

#ifndef EVOSCRIPTLIB_COMPONENT_H
#define EVOSCRIPTLIB_COMPONENT_H

#include "Math/Vector3.h"
#include "Standard/Addresses.h"
#include "string"

class GameObject;

class Component {
protected:
	bool m_isSelected;
	bool m_isActive;
	bool m_isEnabled;
	const std::string m_name;
	GameObject* m_parent;
public:
	virtual bool DrawOnInspector() {
		void* voidPtr = g_methodPointers[32];
		typedef bool (Component::*ClassPtr)();
		auto origPtr = *reinterpret_cast<ClassPtr*>(&voidPtr);
		return (*this.*origPtr)();
	}
	Component* BaseComponent() {
		void* voidPtr = g_methodPointers[33];
		typedef Component* (Component::*ClassPtr)();
		auto origPtr = *reinterpret_cast<ClassPtr*>(&voidPtr);
		return (*this.*origPtr)();
	}
	void SetParent(GameObject* arg0) {
		void* voidPtr = g_methodPointers[34];
		typedef void (Component::*ClassPtr)(GameObject* arg0);
		auto origPtr = *reinterpret_cast<ClassPtr*>(&voidPtr);
		return (*this.*origPtr)(arg0);
	}
	GameObject* GetParent() {
		void* voidPtr = g_methodPointers[35];
		typedef GameObject* (Component::*ClassPtr)();
		auto origPtr = *reinterpret_cast<ClassPtr*>(&voidPtr);
		return (*this.*origPtr)();
	}
	virtual void OnRotate(Vector3 arg0) {
		void* voidPtr = g_methodPointers[36];
		typedef void (Component::*ClassPtr)(Vector3 arg0);
		auto origPtr = *reinterpret_cast<ClassPtr*>(&voidPtr);
		return (*this.*origPtr)(arg0);
	}
	virtual void OnMove(Vector3 arg0) {
		void* voidPtr = g_methodPointers[37];
		typedef void (Component::*ClassPtr)(Vector3 arg0);
		auto origPtr = *reinterpret_cast<ClassPtr*>(&voidPtr);
		return (*this.*origPtr)(arg0);
	}
	virtual void OnScaled(Vector3 arg0) {
		void* voidPtr = g_methodPointers[38];
		typedef void (Component::*ClassPtr)(Vector3 arg0);
		auto origPtr = *reinterpret_cast<ClassPtr*>(&voidPtr);
		return (*this.*origPtr)(arg0);
	}
	virtual void OnSelected(bool arg0) {
		void* voidPtr = g_methodPointers[39];
		typedef void (Component::*ClassPtr)(bool arg0);
		auto origPtr = *reinterpret_cast<ClassPtr*>(&voidPtr);
		return (*this.*origPtr)(arg0);
	}
	virtual void OnReady(bool arg0) {
		void* voidPtr = g_methodPointers[40];
		typedef void (Component::*ClassPtr)(bool arg0);
		auto origPtr = *reinterpret_cast<ClassPtr*>(&voidPtr);
		return (*this.*origPtr)(arg0);
	}
	void SetActive(bool arg0) {
		void* voidPtr = g_methodPointers[41];
		typedef void (Component::*ClassPtr)(bool arg0);
		auto origPtr = *reinterpret_cast<ClassPtr*>(&voidPtr);
		return (*this.*origPtr)(arg0);
	}
	void SetEnabled(bool arg0) {
		void* voidPtr = g_methodPointers[42];
		typedef void (Component::*ClassPtr)(bool arg0);
		auto origPtr = *reinterpret_cast<ClassPtr*>(&voidPtr);
		return (*this.*origPtr)(arg0);
	}
	bool IsActive() {
		void* voidPtr = g_methodPointers[43];
		typedef bool (Component::*ClassPtr)();
		auto origPtr = *reinterpret_cast<ClassPtr*>(&voidPtr);
		return (*this.*origPtr)();
	}
	bool IsSelected() {
		void* voidPtr = g_methodPointers[44];
		typedef bool (Component::*ClassPtr)();
		auto origPtr = *reinterpret_cast<ClassPtr*>(&voidPtr);
		return (*this.*origPtr)();
	}
	bool IsReady() {
		void* voidPtr = g_methodPointers[45];
		typedef bool (Component::*ClassPtr)();
		auto origPtr = *reinterpret_cast<ClassPtr*>(&voidPtr);
		return (*this.*origPtr)();
	}
protected:
	virtual void OnDestroyComponent() {
		void* voidPtr = g_methodPointers[46];
		typedef void (Component::*ClassPtr)();
		auto origPtr = *reinterpret_cast<ClassPtr*>(&voidPtr);
		return (*this.*origPtr)();
	}
	virtual void OnDestroyGameObject() {
		void* voidPtr = g_methodPointers[47];
		typedef void (Component::*ClassPtr)();
		auto origPtr = *reinterpret_cast<ClassPtr*>(&voidPtr);
		return (*this.*origPtr)();
	}
};

#endif