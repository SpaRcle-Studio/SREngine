//
// Created by Evo Script code generator on Mon Jul 19 20:12:25 2021 | Author - Monika
//

#ifndef EVOSCRIPTLIB_SCENE_H
#define EVOSCRIPTLIB_SCENE_H

#include "GameObject.h"
#include "Standard/Addresses.h"
#include "map"
#include "mutex"
#include "set"
#include "stdint.h"
#include "string"
#include "vector"

class Scene {
private:
	bool m_hierarchyIsChanged;
	bool m_isDestroy;
	std::mutex m_mutex;
	std::string m_name;
	std::set<GameObject*> m_gameObjects;
	uint32_t m_countUses;
	std::vector<GameObject*> m_selectedGameObjects;
	std::mutex m_selectedMutex;
	uint32_t m_countSelected;
	std::vector<GameObject*> m_rootObjects;
	bool m_rootObjectsEmpty;
public:
	bool Destroy() {
		void* voidPtr = g_methodPointers[18];
		typedef bool (Scene::*ClassPtr)();
		auto origPtr = *reinterpret_cast<ClassPtr*>(&voidPtr);
		return (*this.*origPtr)();
	}
	bool Free() {
		void* voidPtr = g_methodPointers[19];
		typedef bool (Scene::*ClassPtr)();
		auto origPtr = *reinterpret_cast<ClassPtr*>(&voidPtr);
		return (*this.*origPtr)();
	}
	std::string GetName() {
		void* voidPtr = g_methodPointers[20];
		typedef std::string (Scene::*ClassPtr)();
		auto origPtr = *reinterpret_cast<ClassPtr*>(&voidPtr);
		return (*this.*origPtr)();
	}
	std::vector<GameObject*> GetGameObjects() {
		void* voidPtr = g_methodPointers[21];
		typedef std::vector<GameObject*> (Scene::*ClassPtr)();
		auto origPtr = *reinterpret_cast<ClassPtr*>(&voidPtr);
		return (*this.*origPtr)();
	}
	std::vector<GameObject*>& GetRootGameObjects() {
		void* voidPtr = g_methodPointers[22];
		typedef std::vector<GameObject*>& (Scene::*ClassPtr)();
		auto origPtr = *reinterpret_cast<ClassPtr*>(&voidPtr);
		return (*this.*origPtr)();
	}
	void AddUsePoint() {
		void* voidPtr = g_methodPointers[23];
		typedef void (Scene::*ClassPtr)();
		auto origPtr = *reinterpret_cast<ClassPtr*>(&voidPtr);
		return (*this.*origPtr)();
	}
	bool RemoveUsePoint() {
		void* voidPtr = g_methodPointers[24];
		typedef bool (Scene::*ClassPtr)();
		auto origPtr = *reinterpret_cast<ClassPtr*>(&voidPtr);
		return (*this.*origPtr)();
	}
	std::vector<GameObject*> GetSelected() {
		void* voidPtr = g_methodPointers[25];
		typedef std::vector<GameObject*> (Scene::*ClassPtr)();
		auto origPtr = *reinterpret_cast<ClassPtr*>(&voidPtr);
		return (*this.*origPtr)();
	}
	void UnselectAll() {
		void* voidPtr = g_methodPointers[26];
		typedef void (Scene::*ClassPtr)();
		auto origPtr = *reinterpret_cast<ClassPtr*>(&voidPtr);
		return (*this.*origPtr)();
	}
	bool RemoveSelected(GameObject* arg0) {
		void* voidPtr = g_methodPointers[27];
		typedef bool (Scene::*ClassPtr)(GameObject* arg0);
		auto origPtr = *reinterpret_cast<ClassPtr*>(&voidPtr);
		return (*this.*origPtr)(arg0);
	}
	void AddSelected(GameObject* arg0) {
		void* voidPtr = g_methodPointers[28];
		typedef void (Scene::*ClassPtr)(GameObject* arg0);
		auto origPtr = *reinterpret_cast<ClassPtr*>(&voidPtr);
		return (*this.*origPtr)(arg0);
	}
	GameObject* Instance(const std::string& arg0) {
		void* voidPtr = g_methodPointers[29];
		typedef GameObject* (Scene::*ClassPtr)(const std::string& arg0);
		auto origPtr = *reinterpret_cast<ClassPtr*>(&voidPtr);
		return (*this.*origPtr)(arg0);
	}
	GameObject* FindByComponent(const std::string& arg0) {
		void* voidPtr = g_methodPointers[30];
		typedef GameObject* (Scene::*ClassPtr)(const std::string& arg0);
		auto origPtr = *reinterpret_cast<ClassPtr*>(&voidPtr);
		return (*this.*origPtr)(arg0);
	}
	static Scene* New(const std::string& arg0) {
		void* voidPtr = g_methodPointers[31];
		typedef Scene* (*ClassPtr)(const std::string& arg0);
		auto origPtr = *reinterpret_cast<ClassPtr*>(&voidPtr);
		return (*origPtr)(arg0);
	}
};

#endif