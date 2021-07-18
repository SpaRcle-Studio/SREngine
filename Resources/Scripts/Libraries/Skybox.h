//
// Created by Evo Script code generator on Sun Jul 18 20:07:39 2021 | Author - Monika
//

#ifndef EVOSCRIPTLIB_SKYBOX_H
#define EVOSCRIPTLIB_SKYBOX_H

#include "Standard/Addresses.h"
#include "array"
#include "stdint.h"
#include "string"
#include "vector"

class Skybox {
private:
	void* m_env;
	void* m_render;
	void* m_shader;
	int32_t m_VAO;
	int32_t m_VBO;
	int32_t m_IBO;
	int32_t m_descriptorSet;
	int32_t m_cubeMap;
	uint32_t m_width;
	uint32_t m_height;
	std::array<uint8_t*, 6> m_data;
	bool m_isCalculated;
	bool m_hasErrors;
	volatile bool m_isVideoMemFree;
	std::string m_name;
public:
	static Skybox* Load(const std::string& arg0) {
		void* voidPtr = g_methodPointers[101];
		typedef Skybox* (*ClassPtr)(const std::string& arg0);
		auto origPtr = *reinterpret_cast<ClassPtr*>(&voidPtr);
		return (*origPtr)(arg0);
	}
};

#endif