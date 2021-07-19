//
// Created by Evo Script code generator on Mon Jul 19 20:12:25 2021 | Author - Monika
//

#ifndef EVOSCRIPTLIB_TEXTURE_H
#define EVOSCRIPTLIB_TEXTURE_H

#include "ResourceManager.h"
#include "Standard/Addresses.h"
#include "mutex"
#include "stdint.h"
#include "string"

enum class TextureCompression {
	None = 0, BC1 = 1, BC2 = 2, BC3 = 3, BC4 = 4, BC5 = 5, BC6 = 6, BC7 = 7, 
};

enum class TextureFormat {
	Unknown = 0, RGBA8_UNORM = 10000, RGBA16_UNORM = 10001, RGBA8_SRGB = 20000, 
};

enum class TextureType {
	Unknown = 0, Diffuse = 1, Normal = 2, Specular = 3, Roughness = 4, Glossiness = 5, 
};

enum class TextureFilter {
	Unknown = 0, NEAREST = 1, LINEAR = 2, 
};

class Texture : public IResource {
private:
	int32_t m_ID;
	uint32_t m_width;
	uint32_t m_height;
	TextureFormat m_format;
	TextureCompression m_compression;
	uint8_t m_mipLevels;
	bool m_alpha;
	uint8_t* m_data;
	volatile bool m_isCalculate;
	bool m_hasErrors;
	void* m_render;
	std::mutex m_mutex;
	TextureType m_type;
	TextureFilter m_filter;
private:
	bool Destroy() override {
		void* voidPtr = g_methodPointers[104];
		typedef bool (IResource::*ClassPtr)();
		auto origPtr = *reinterpret_cast<ClassPtr*>(&voidPtr);
		return (*this.*origPtr)();
	}
	void Free() override {
		void* voidPtr = g_methodPointers[105];
		typedef void (IResource::*ClassPtr)();
		auto origPtr = *reinterpret_cast<ClassPtr*>(&voidPtr);
		return (*this.*origPtr)();
	}
public:
	static Texture* Load(const std::string& arg0, TextureFormat arg1, bool arg2, TextureType arg3, TextureFilter arg4, TextureCompression arg5, uint8_t arg6) {
		void* voidPtr = g_methodPointers[106];
		typedef Texture* (*ClassPtr)(const std::string& arg0, TextureFormat arg1, bool arg2, TextureType arg3, TextureFilter arg4, TextureCompression arg5, uint8_t arg6);
		auto origPtr = *reinterpret_cast<ClassPtr*>(&voidPtr);
		return (*origPtr)(arg0, arg1, arg2, arg3, arg4, arg5, arg6);
	}
};

#endif