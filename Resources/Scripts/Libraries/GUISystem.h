//
// Created by Evo Script code generator on Mon Jul 19 20:12:25 2021 | Author - Monika
//

#ifndef EVOSCRIPTLIB_GUISYSTEM_H
#define EVOSCRIPTLIB_GUISYSTEM_H

#include "Standard/Addresses.h"

class GUISystem {
public:
	static GUISystem* Get() {
		void* voidPtr = g_methodPointers[111];
		typedef GUISystem* (*ClassPtr)();
		auto origPtr = *reinterpret_cast<ClassPtr*>(&voidPtr);
		return (*origPtr)();
	}
	void BeginDockSpace() {
		void* voidPtr = g_methodPointers[112];
		typedef void (GUISystem::*ClassPtr)();
		auto origPtr = *reinterpret_cast<ClassPtr*>(&voidPtr);
		return (*this.*origPtr)();
	}
	void EndDockSpace() {
		void* voidPtr = g_methodPointers[113];
		typedef void (GUISystem::*ClassPtr)();
		auto origPtr = *reinterpret_cast<ClassPtr*>(&voidPtr);
		return (*this.*origPtr)();
	}
	bool BeginWindow(const char* arg0) {
		void* voidPtr = g_methodPointers[114];
		typedef bool (GUISystem::*ClassPtr)(const char* arg0);
		auto origPtr = *reinterpret_cast<ClassPtr*>(&voidPtr);
		return (*this.*origPtr)(arg0);
	}
	void EndWindow() {
		void* voidPtr = g_methodPointers[115];
		typedef void (GUISystem::*ClassPtr)();
		auto origPtr = *reinterpret_cast<ClassPtr*>(&voidPtr);
		return (*this.*origPtr)();
	}
	bool BeginChildWindow(const char* arg0) {
		void* voidPtr = g_methodPointers[116];
		typedef bool (GUISystem::*ClassPtr)(const char* arg0);
		auto origPtr = *reinterpret_cast<ClassPtr*>(&voidPtr);
		return (*this.*origPtr)(arg0);
	}
	void EndChildWindow() {
		void* voidPtr = g_methodPointers[117];
		typedef void (GUISystem::*ClassPtr)();
		auto origPtr = *reinterpret_cast<ClassPtr*>(&voidPtr);
		return (*this.*origPtr)();
	}
};

#endif