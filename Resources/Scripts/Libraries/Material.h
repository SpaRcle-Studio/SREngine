//
// Created by Evo Script code generator on Sun Jul 18 20:07:39 2021 | Author - Monika
//

#ifndef EVOSCRIPTLIB_MATERIAL_H
#define EVOSCRIPTLIB_MATERIAL_H

#include "Standard/Addresses.h"
#include "Texture.h"
#include "Utils.h"

class Mesh;

class Material {
private:
	bool m_transparent;
	volatile bool m_bloom;
	_16byte m_color;
	Mesh* m_mesh;
	volatile bool m_texturesIsFree;
	Texture* m_diffuse;
	Texture* m_normal;
	Texture* m_specular;
	Texture* m_glossiness;
public:
	void SetDiffuse(Texture* arg0) {
		void* voidPtr = g_methodPointers[105];
		typedef void (Material::*ClassPtr)(Texture* arg0);
		auto origPtr = *reinterpret_cast<ClassPtr*>(&voidPtr);
		return (*this.*origPtr)(arg0);
	}
	void SetNormal(Texture* arg0) {
		void* voidPtr = g_methodPointers[106];
		typedef void (Material::*ClassPtr)(Texture* arg0);
		auto origPtr = *reinterpret_cast<ClassPtr*>(&voidPtr);
		return (*this.*origPtr)(arg0);
	}
	void SetSpecular(Texture* arg0) {
		void* voidPtr = g_methodPointers[107];
		typedef void (Material::*ClassPtr)(Texture* arg0);
		auto origPtr = *reinterpret_cast<ClassPtr*>(&voidPtr);
		return (*this.*origPtr)(arg0);
	}
	void SetGlossiness(Texture* arg0) {
		void* voidPtr = g_methodPointers[108];
		typedef void (Material::*ClassPtr)(Texture* arg0);
		auto origPtr = *reinterpret_cast<ClassPtr*>(&voidPtr);
		return (*this.*origPtr)(arg0);
	}
};

#endif