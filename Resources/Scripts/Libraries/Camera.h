//
// Created by Evo Script code generator on Sun Jul 18 20:07:39 2021 | Author - Monika
//

#ifndef EVOSCRIPTLIB_CAMERA_H
#define EVOSCRIPTLIB_CAMERA_H

#include "Component.h"
#include "Math/Vector2.h"
#include "Math/Vector3.h"
#include "Standard/Addresses.h"
#include "Utils.h"
#include "stdint.h"

class Camera : public Component {
private:
	volatile bool m_isCreate;
	volatile bool m_isCalculate;
	volatile bool m_isBuffCalculate;
	volatile bool m_needUpdate;
	volatile float m_yaw;
	volatile float m_pitch;
	volatile float m_roll;
	void* m_postProcessing;
	void* m_env;
	int m_pipeline;
	void* m_window;
	_64byte m_projection;
	_64byte m_viewTranslateMat;
	_64byte m_viewMat;
	Vector3 m_pos;
	_128byte m_ubo;
	bool m_isEnableDirectOut;
	bool m_allowUpdateProj;
	float m_far;
	float m_near;
	void* m_canvas;
	Vector2 m_cameraSize;
public:
	static Camera* Allocate(uint32_t arg0, uint32_t arg1) {
		void* voidPtr = g_methodPointers[70];
		typedef Camera* (*ClassPtr)(uint32_t arg0, uint32_t arg1);
		auto origPtr = *reinterpret_cast<ClassPtr*>(&voidPtr);
		return (*origPtr)(arg0, arg1);
	}
	void SetDirectOutput(bool arg0) {
		void* voidPtr = g_methodPointers[71];
		typedef void (Component::*ClassPtr)(bool arg0);
		auto origPtr = *reinterpret_cast<ClassPtr*>(&voidPtr);
		return (*this.*origPtr)(arg0);
	}
private:
	void OnDestroyGameObject() override {
		void* voidPtr = g_methodPointers[72];
		typedef void (Component::*ClassPtr)();
		auto origPtr = *reinterpret_cast<ClassPtr*>(&voidPtr);
		return (*this.*origPtr)();
	}
	void OnRotate(Vector3 arg0) override {
		void* voidPtr = g_methodPointers[73];
		typedef void (Component::*ClassPtr)(Vector3 arg0);
		auto origPtr = *reinterpret_cast<ClassPtr*>(&voidPtr);
		return (*this.*origPtr)(arg0);
	}
	void OnMove(Vector3 arg0) override {
		void* voidPtr = g_methodPointers[74];
		typedef void (Component::*ClassPtr)(Vector3 arg0);
		auto origPtr = *reinterpret_cast<ClassPtr*>(&voidPtr);
		return (*this.*origPtr)(arg0);
	}
	bool DrawOnInspector() override {
		void* voidPtr = g_methodPointers[75];
		typedef bool (Component::*ClassPtr)();
		auto origPtr = *reinterpret_cast<ClassPtr*>(&voidPtr);
		return (*this.*origPtr)();
	}
	void OnDestroyComponent() override {
		void* voidPtr = g_methodPointers[76];
		typedef void (Component::*ClassPtr)();
		auto origPtr = *reinterpret_cast<ClassPtr*>(&voidPtr);
		return (*this.*origPtr)();
	}
};

#endif