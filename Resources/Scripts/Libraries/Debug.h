//
// Created by Evo Script code generator on Mon Jul 19 20:12:25 2021 | Author - Monika
//

#ifndef EVOSCRIPTLIB_DEBUG_H
#define EVOSCRIPTLIB_DEBUG_H

#include "Standard/Addresses.h"
#include "string"

class Debug {
public:
	static void Log(std::string arg0) {
		void* voidPtr = g_methodPointers[0];
		typedef void (*ClassPtr)(std::string arg0);
		auto origPtr = *reinterpret_cast<ClassPtr*>(&voidPtr);
		return (*origPtr)(arg0);
	}
	static void Warn(std::string arg0) {
		void* voidPtr = g_methodPointers[1];
		typedef void (*ClassPtr)(std::string arg0);
		auto origPtr = *reinterpret_cast<ClassPtr*>(&voidPtr);
		return (*origPtr)(arg0);
	}
	static void System(std::string arg0) {
		void* voidPtr = g_methodPointers[2];
		typedef void (*ClassPtr)(std::string arg0);
		auto origPtr = *reinterpret_cast<ClassPtr*>(&voidPtr);
		return (*origPtr)(arg0);
	}
	static void Shader(std::string arg0) {
		void* voidPtr = g_methodPointers[3];
		typedef void (*ClassPtr)(std::string arg0);
		auto origPtr = *reinterpret_cast<ClassPtr*>(&voidPtr);
		return (*origPtr)(arg0);
	}
	static void Error(std::string arg0) {
		void* voidPtr = g_methodPointers[4];
		typedef void (*ClassPtr)(std::string arg0);
		auto origPtr = *reinterpret_cast<ClassPtr*>(&voidPtr);
		return (*origPtr)(arg0);
	}
	static void Info(std::string arg0) {
		void* voidPtr = g_methodPointers[5];
		typedef void (*ClassPtr)(std::string arg0);
		auto origPtr = *reinterpret_cast<ClassPtr*>(&voidPtr);
		return (*origPtr)(arg0);
	}
	static void Script(std::string arg0) {
		void* voidPtr = g_methodPointers[6];
		typedef void (*ClassPtr)(std::string arg0);
		auto origPtr = *reinterpret_cast<ClassPtr*>(&voidPtr);
		return (*origPtr)(arg0);
	}
	static void ScriptError(std::string arg0) {
		void* voidPtr = g_methodPointers[7];
		typedef void (*ClassPtr)(std::string arg0);
		auto origPtr = *reinterpret_cast<ClassPtr*>(&voidPtr);
		return (*origPtr)(arg0);
	}
	static void ScriptLog(std::string arg0) {
		void* voidPtr = g_methodPointers[8];
		typedef void (*ClassPtr)(std::string arg0);
		auto origPtr = *reinterpret_cast<ClassPtr*>(&voidPtr);
		return (*origPtr)(arg0);
	}
};

#endif