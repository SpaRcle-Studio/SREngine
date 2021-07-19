//
// Created by Evo Script code generator on Mon Jul 19 20:12:25 2021 | Author - Monika
//

#ifndef EVOSCRIPTLIB_GAMEOBJECT_H
#define EVOSCRIPTLIB_GAMEOBJECT_H

#include "Component.h"
#include "Math/Vector3.h"
#include "Standard/Addresses.h"
#include "Transform.h"
#include "mutex"
#include "string"
#include "vector"

class Scene;

class GameObject {
private:
	bool m_isSelect;
	GameObject* m_parent;
	std::vector<GameObject*> m_children;
	uint32_t m_countChild;
	bool m_isDestroy;
	std::mutex m_mutex;
	Scene* m_scene;
	Transform* m_transform;
	std::vector<Component*> m_components;
	std::string m_name;
	std::string m_tag;
public:
	bool AddComponent(Component* arg0) {
		void* voidPtr = g_methodPointers[69];
		typedef bool (GameObject::*ClassPtr)(Component* arg0);
		auto origPtr = *reinterpret_cast<ClassPtr*>(&voidPtr);
		return (*this.*origPtr)(arg0);
	}
	Transform* GetTransform() {
		void* voidPtr = g_methodPointers[70];
		typedef Transform* (GameObject::*ClassPtr)();
		auto origPtr = *reinterpret_cast<ClassPtr*>(&voidPtr);
		return (*this.*origPtr)();
	}
	Component* GetComponent(const std::string& arg0) {
		void* voidPtr = g_methodPointers[71];
		typedef Component* (GameObject::*ClassPtr)(const std::string& arg0);
		auto origPtr = *reinterpret_cast<ClassPtr*>(&voidPtr);
		return (*this.*origPtr)(arg0);
	}
};

#endif