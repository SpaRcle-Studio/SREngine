//
// Created by Evo Script code generator on Mon Jul 19 20:12:25 2021 | Author - Monika
//

#ifndef EVOSCRIPTLIB_MESH_H
#define EVOSCRIPTLIB_MESH_H

#include "Component.h"
#include "Material.h"
#include "Math/Vector3.h"
#include "ResourceManager.h"
#include "Standard/Addresses.h"
#include "Utils.h"
#include "mutex"

class Mesh;
class Render;

class Mesh : public IResource, public Component {
protected:
	bool m_inverse;
	void* m_env;
	int m_pipeline;
	std::mutex m_mutex;
	std::string m_geometry_name;
	void* m_shader;
	void* m_render;
	Material* m_material;
	volatile bool m_hasErrors;
	volatile bool m_isCalculated;
	int32_t m_descriptorSet;
	int32_t m_VAO;
	int32_t m_VBO;
	int32_t m_IBO;
	int32_t m_UBO;
	std::vector<uint32_t> m_indices;
	uint32_t m_countVertices;
	uint32_t m_countIndices;
	bool m_useIndices;
	Vector3 m_position;
	Vector3 m_rotation;
	Vector3 m_scale;
	_64byte m_modelMat;
public:
	static std::vector<Mesh*> Load(const std::string& arg0) {
		void* voidPtr = g_methodPointers[48];
		typedef std::vector<Mesh*> (*ClassPtr)(const std::string& arg0);
		auto origPtr = *reinterpret_cast<ClassPtr*>(&voidPtr);
		return (*origPtr)(arg0);
	}
	bool DrawOnInspector() override {
		void* voidPtr = g_methodPointers[49];
		typedef bool (Component::*ClassPtr)();
		auto origPtr = *reinterpret_cast<ClassPtr*>(&voidPtr);
		return (*this.*origPtr)();
	}
	void OnMove(Vector3 arg0) override {
		void* voidPtr = g_methodPointers[50];
		typedef void (Component::*ClassPtr)(Vector3 arg0);
		auto origPtr = *reinterpret_cast<ClassPtr*>(&voidPtr);
		return (*this.*origPtr)(arg0);
	}
	void OnRotate(Vector3 arg0) override {
		void* voidPtr = g_methodPointers[51];
		typedef void (Component::*ClassPtr)(Vector3 arg0);
		auto origPtr = *reinterpret_cast<ClassPtr*>(&voidPtr);
		return (*this.*origPtr)(arg0);
	}
	void OnScaled(Vector3 arg0) override {
		void* voidPtr = g_methodPointers[52];
		typedef void (Component::*ClassPtr)(Vector3 arg0);
		auto origPtr = *reinterpret_cast<ClassPtr*>(&voidPtr);
		return (*this.*origPtr)(arg0);
	}
	void OnSelected(bool arg0) override {
		void* voidPtr = g_methodPointers[53];
		typedef void (Component::*ClassPtr)(bool arg0);
		auto origPtr = *reinterpret_cast<ClassPtr*>(&voidPtr);
		return (*this.*origPtr)(arg0);
	}
	bool Destroy() override {
		void* voidPtr = g_methodPointers[54];
		typedef bool (IResource::*ClassPtr)();
		auto origPtr = *reinterpret_cast<ClassPtr*>(&voidPtr);
		return (*this.*origPtr)();
	}
	void OnDestroyGameObject() override {
		void* voidPtr = g_methodPointers[55];
		typedef void (Component::*ClassPtr)();
		auto origPtr = *reinterpret_cast<ClassPtr*>(&voidPtr);
		return (*this.*origPtr)();
	}
	void OnReady(bool arg0) override {
		void* voidPtr = g_methodPointers[56];
		typedef void (Component::*ClassPtr)(bool arg0);
		auto origPtr = *reinterpret_cast<ClassPtr*>(&voidPtr);
		return (*this.*origPtr)(arg0);
	}
	void WaitCalculate() {
		void* voidPtr = g_methodPointers[57];
		typedef void (IResource::*ClassPtr)();
		auto origPtr = *reinterpret_cast<ClassPtr*>(&voidPtr);
		return (*this.*origPtr)();
	}
	Material* GetMaterial() {
		void* voidPtr = g_methodPointers[58];
		typedef Material* (IResource::*ClassPtr)();
		auto origPtr = *reinterpret_cast<ClassPtr*>(&voidPtr);
		return (*this.*origPtr)();
	}
	void OnDestroyComponent() override {
		void* voidPtr = g_methodPointers[59];
		typedef void (Component::*ClassPtr)();
		auto origPtr = *reinterpret_cast<ClassPtr*>(&voidPtr);
		return (*this.*origPtr)();
	}
};

#endif