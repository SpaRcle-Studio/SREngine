//
// Created by Evo Script code generator on Mon Jul 19 20:12:25 2021 | Author - Monika
//

#ifndef EVOSCRIPTLIB_RESOURCEMANAGER_H
#define EVOSCRIPTLIB_RESOURCEMANAGER_H

#include "Standard/Addresses.h"
#include "string"

class IResource {
protected:
	bool m_autoRemove;
	volatile bool m_isDestroy;
	volatile unsigned long m_countUses;
	const char* m_resource_name;
	std::string m_resource_id;
private:
	virtual void Free() {
		void* voidPtr = g_methodPointers[60];
		typedef void (IResource::*ClassPtr)();
		auto origPtr = *reinterpret_cast<ClassPtr*>(&voidPtr);
		return (*this.*origPtr)();
	}
public:
	bool IsEnabledAutoRemove() {
		void* voidPtr = g_methodPointers[61];
		typedef bool (IResource::*ClassPtr)();
		auto origPtr = *reinterpret_cast<ClassPtr*>(&voidPtr);
		return (*this.*origPtr)();
	}
	virtual bool Destroy() {
		void* voidPtr = g_methodPointers[62];
		typedef bool (IResource::*ClassPtr)();
		auto origPtr = *reinterpret_cast<ClassPtr*>(&voidPtr);
		return (*this.*origPtr)();
	}
	bool IsDestroy() {
		void* voidPtr = g_methodPointers[63];
		typedef bool (IResource::*ClassPtr)();
		auto origPtr = *reinterpret_cast<ClassPtr*>(&voidPtr);
		return (*this.*origPtr)();
	}
	void AddUsePoint() {
		void* voidPtr = g_methodPointers[64];
		typedef void (IResource::*ClassPtr)();
		auto origPtr = *reinterpret_cast<ClassPtr*>(&voidPtr);
		return (*this.*origPtr)();
	}
	void RemoveUsePoint() {
		void* voidPtr = g_methodPointers[65];
		typedef void (IResource::*ClassPtr)();
		auto origPtr = *reinterpret_cast<ClassPtr*>(&voidPtr);
		return (*this.*origPtr)();
	}
	unsigned int GetCountUses() {
		void* voidPtr = g_methodPointers[66];
		typedef unsigned int (IResource::*ClassPtr)();
		auto origPtr = *reinterpret_cast<ClassPtr*>(&voidPtr);
		return (*this.*origPtr)();
	}
	const char* GetResourceName() {
		void* voidPtr = g_methodPointers[67];
		typedef const char* (IResource::*ClassPtr)();
		auto origPtr = *reinterpret_cast<ClassPtr*>(&voidPtr);
		return (*this.*origPtr)();
	}
	std::string GetResourceID() {
		void* voidPtr = g_methodPointers[68];
		typedef std::string (IResource::*ClassPtr)();
		auto origPtr = *reinterpret_cast<ClassPtr*>(&voidPtr);
		return (*this.*origPtr)();
	}
};

#endif