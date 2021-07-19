//
// Created by Evo Script code generator on Mon Jul 19 20:12:25 2021 | Author - Monika
//

#ifndef EVOSCRIPTLIB_ENGINE_H
#define EVOSCRIPTLIB_ENGINE_H

#include "Standard/Addresses.h"

class Scene;
class Render;
class Camera;
class Window;

typedef void Time;
typedef void PhysEngine;

class Engine {
private:
	volatile bool m_isCreate;
	volatile bool m_isInit;
	volatile bool m_isRun;
	volatile bool m_isClose;
	volatile bool m_exitEvent;
	void* m_compiler;
	Window* m_window;
	void* m_render;
	Scene* m_scene;
	void* m_time;
	void* m_physics;
public:
	static Engine* Get() {
		void* voidPtr = g_methodPointers[9];
		typedef Engine* (*ClassPtr)();
		auto origPtr = *reinterpret_cast<ClassPtr*>(&voidPtr);
		return (*origPtr)();
	}
private:
	bool RegisterLibraries() {
		void* voidPtr = g_methodPointers[10];
		typedef bool (Engine::*ClassPtr)();
		auto origPtr = *reinterpret_cast<ClassPtr*>(&voidPtr);
		return (*this.*origPtr)();
	}
public:
	static void Reload() {
		void* voidPtr = g_methodPointers[11];
		typedef void (*ClassPtr)();
		auto origPtr = *reinterpret_cast<ClassPtr*>(&voidPtr);
		return (*origPtr)();
	}
	Time* GetTime() {
		void* voidPtr = g_methodPointers[12];
		typedef Time* (Engine::*ClassPtr)();
		auto origPtr = *reinterpret_cast<ClassPtr*>(&voidPtr);
		return (*this.*origPtr)();
	}
	Window* GetWindow() {
		void* voidPtr = g_methodPointers[13];
		typedef Window* (Engine::*ClassPtr)();
		auto origPtr = *reinterpret_cast<ClassPtr*>(&voidPtr);
		return (*this.*origPtr)();
	}
	Render* GetRender() {
		void* voidPtr = g_methodPointers[14];
		typedef Render* (Engine::*ClassPtr)();
		auto origPtr = *reinterpret_cast<ClassPtr*>(&voidPtr);
		return (*this.*origPtr)();
	}
	Scene* GetScene() {
		void* voidPtr = g_methodPointers[15];
		typedef Scene* (Engine::*ClassPtr)();
		auto origPtr = *reinterpret_cast<ClassPtr*>(&voidPtr);
		return (*this.*origPtr)();
	}
	bool IsRun() {
		void* voidPtr = g_methodPointers[16];
		typedef bool (Engine::*ClassPtr)();
		auto origPtr = *reinterpret_cast<ClassPtr*>(&voidPtr);
		return (*this.*origPtr)();
	}
	bool SetScene(Scene* arg0) {
		void* voidPtr = g_methodPointers[17];
		typedef bool (Engine::*ClassPtr)(Scene* arg0);
		auto origPtr = *reinterpret_cast<ClassPtr*>(&voidPtr);
		return (*this.*origPtr)(arg0);
	}
};

#endif