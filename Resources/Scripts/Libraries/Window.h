//
// Created by Evo Script code generator on Sun Jul 18 20:07:39 2021 | Author - Monika
//

#ifndef EVOSCRIPTLIB_WINDOW_H
#define EVOSCRIPTLIB_WINDOW_H

#include "Math/Vector2.h"
#include "Standard/Addresses.h"
#include "mutex"
#include "stdint.h"
#include "thread"
#include "vector"

class Camera;
class Mesh;

class Window {
private:
	volatile bool m_isCreate;
	volatile bool m_isInit;
	volatile bool m_isRun;
	volatile bool m_isClose;
	volatile bool m_hasErrors;
	volatile bool m_isEnvInit;
	volatile bool m_isWindowClose;
	volatile bool m_isWindowFocus;
	volatile bool m_isNeedResize;
	volatile bool m_isNeedMove;
	std::thread m_thread;
	void* m_time;
	void* m_env;
	const char* m_win_name;
	const char* m_icoPath;
	uint8_t m_smoothSamples;
	void* m_render;
	std::mutex m_camerasMutex;
	std::vector<Camera*> m_newCameras;
	uint32_t m_countNewCameras;
	std::vector<Camera*> m_camerasToDestroy;
	uint32_t m_countCamerasToDestroy;
	std::vector<Camera*> m_cameras;
	uint32_t m_countCameras;
	bool m_GUIEnabled;
	void* m_aimedWindowTarget;
	Camera* m_aimedCameraTarget;
	Mesh* m_aimedMesh;
	bool m_requireGetAimed;
	void* m_canvas;
	bool m_vsync;
	bool m_fullScreen;
	bool m_resizable;
	Vector2 m_windowPos;
	Vector2 m_newWindowPos;
	Vector2 m_newWindowSize;
public:
	void AddCamera(Camera* arg0) {
		void* voidPtr = g_methodPointers[77];
		typedef void (Window::*ClassPtr)(Camera* arg0);
		auto origPtr = *reinterpret_cast<ClassPtr*>(&voidPtr);
		return (*this.*origPtr)(arg0);
	}
	void Resize(uint32_t arg0, uint32_t arg1) {
		void* voidPtr = g_methodPointers[78];
		typedef void (Window::*ClassPtr)(uint32_t arg0, uint32_t arg1);
		auto origPtr = *reinterpret_cast<ClassPtr*>(&voidPtr);
		return (*this.*origPtr)(arg0, arg1);
	}
	void CentralizeWindow() {
		void* voidPtr = g_methodPointers[79];
		typedef void (Window::*ClassPtr)();
		auto origPtr = *reinterpret_cast<ClassPtr*>(&voidPtr);
		return (*this.*origPtr)();
	}
	void SetGUIEnabled(bool arg0) {
		void* voidPtr = g_methodPointers[80];
		typedef void (Window::*ClassPtr)(bool arg0);
		auto origPtr = *reinterpret_cast<ClassPtr*>(&voidPtr);
		return (*this.*origPtr)(arg0);
	}
};

#endif