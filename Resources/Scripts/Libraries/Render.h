//
// Created by Evo Script code generator on Sun Jul 18 20:07:39 2021 | Author - Monika
//

#ifndef EVOSCRIPTLIB_RENDER_H
#define EVOSCRIPTLIB_RENDER_H

#include "Skybox.h"
#include "Standard/Addresses.h"
#include "Texture.h"
#include "Utils.h"
#include "map"
#include "mutex"
#include "stdint.h"
#include "vector"

class Window;
class Camera;
class Mesh;

class MeshCluster {
private:
	std::map<uint32_t, std::vector<Mesh*>> MeshGroups;
	std::map<uint32_t, uint32_t> MeshGroupCounters;
	uint32_t m_total;
};

class Render {
private:
	volatile bool m_isCreate;
	volatile bool m_isInit;
	volatile bool m_isRun;
	volatile bool m_isClose;
	void* m_env;
	Window* m_window;
	Camera* m_currentCamera;
	std::mutex m_mutex;
	std::vector<Mesh*> m_newMeshes;
	std::vector<Mesh*> m_removeMeshes;
	std::vector<void*> m_textureToFree;
	std::vector<Skybox*> m_skyboxesToFreeVidMem;
	MeshCluster m_geometry;
	MeshCluster m_transparentGeometry;
	Skybox* m_newSkybox;
	Skybox* m_skybox;
	void* m_geometryShader;
	void* m_transparentShader;
	void* m_flatGeometryShader;
	void* m_skyboxShader;
	void* m_grid;
	void* m_colorBuffer;
	bool m_gridEnabled;
	bool m_skyboxEnabled;
	bool m_wireFrame;
	int32_t m_pipeLine;
public:
	virtual void UpdateUBOs() {
		void* voidPtr = g_methodPointers[81];
		typedef void (Render::*ClassPtr)();
		auto origPtr = *reinterpret_cast<ClassPtr*>(&voidPtr);
		return (*this.*origPtr)();
	}
	virtual bool DrawGeometry() {
		void* voidPtr = g_methodPointers[82];
		typedef bool (Render::*ClassPtr)();
		auto origPtr = *reinterpret_cast<ClassPtr*>(&voidPtr);
		return (*this.*origPtr)();
	}
	virtual bool DrawSkybox() {
		void* voidPtr = g_methodPointers[83];
		typedef bool (Render::*ClassPtr)();
		auto origPtr = *reinterpret_cast<ClassPtr*>(&voidPtr);
		return (*this.*origPtr)();
	}
	virtual void DrawGrid() {
		void* voidPtr = g_methodPointers[84];
		typedef void (Render::*ClassPtr)();
		auto origPtr = *reinterpret_cast<ClassPtr*>(&voidPtr);
		return (*this.*origPtr)();
	}
	virtual void DrawSingleColors() {
		void* voidPtr = g_methodPointers[85];
		typedef void (Render::*ClassPtr)();
		auto origPtr = *reinterpret_cast<ClassPtr*>(&voidPtr);
		return (*this.*origPtr)();
	}
	virtual bool DrawTransparentGeometry() {
		void* voidPtr = g_methodPointers[86];
		typedef bool (Render::*ClassPtr)();
		auto origPtr = *reinterpret_cast<ClassPtr*>(&voidPtr);
		return (*this.*origPtr)();
	}
	virtual bool DrawSettingsPanel() {
		void* voidPtr = g_methodPointers[87];
		typedef bool (Render::*ClassPtr)();
		auto origPtr = *reinterpret_cast<ClassPtr*>(&voidPtr);
		return (*this.*origPtr)();
	}
	void SetSkybox(Skybox* arg0) {
		void* voidPtr = g_methodPointers[88];
		typedef void (Render::*ClassPtr)(Skybox* arg0);
		auto origPtr = *reinterpret_cast<ClassPtr*>(&voidPtr);
		return (*this.*origPtr)(arg0);
	}
	void RegisterMesh(Mesh* arg0) {
		void* voidPtr = g_methodPointers[89];
		typedef void (Render::*ClassPtr)(Mesh* arg0);
		auto origPtr = *reinterpret_cast<ClassPtr*>(&voidPtr);
		return (*this.*origPtr)(arg0);
	}
	void RegisterTexture(Texture* arg0) {
		void* voidPtr = g_methodPointers[90];
		typedef void (Render::*ClassPtr)(Texture* arg0);
		auto origPtr = *reinterpret_cast<ClassPtr*>(&voidPtr);
		return (*this.*origPtr)(arg0);
	}
};

#endif