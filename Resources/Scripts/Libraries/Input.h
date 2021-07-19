//
// Created by Evo Script code generator on Mon Jul 19 20:12:25 2021 | Author - Monika
//

#ifndef EVOSCRIPTLIB_INPUT_H
#define EVOSCRIPTLIB_INPUT_H

#include "Math/Vector2.h"
#include "Standard/Addresses.h"

enum class KeyCode {
	MouseLeft = 1, MouseRight = 2, MouseMiddle = 4, BackSpace = 8, Tab = 9, Enter = 13, LShift = 16, Ctrl = 17, Alt = 18, Esc = 27, Space = 32, LeftArrow = 37, UpArrow = 38, RightArrow = 39, DownArrow = 40, Del = 46, A = 65, B = 66, C = 67, D = 68, E = 69, F = 70, G = 71, H = 72, I = 73, J = 74, K = 75, L = 76, M = 77, N = 78, O = 79, P = 80, Q = 81, S = 83, R = 82, T = 84, U = 85, V = 86, W = 87, X = 88, Y = 89, Z = 90, 
};

class Input {
public:
	static int GetMouseWheel() {
		void* voidPtr = g_methodPointers[98];
		typedef int (*ClassPtr)();
		auto origPtr = *reinterpret_cast<ClassPtr*>(&voidPtr);
		return (*origPtr)();
	}
	static Vector2 GetMouseDrag() {
		void* voidPtr = g_methodPointers[99];
		typedef Vector2 (*ClassPtr)();
		auto origPtr = *reinterpret_cast<ClassPtr*>(&voidPtr);
		return (*origPtr)();
	}
	static bool GetKey(KeyCode arg0) {
		void* voidPtr = g_methodPointers[100];
		typedef bool (*ClassPtr)(KeyCode arg0);
		auto origPtr = *reinterpret_cast<ClassPtr*>(&voidPtr);
		return (*origPtr)(arg0);
	}
	static bool GetKeyDown(KeyCode arg0) {
		void* voidPtr = g_methodPointers[101];
		typedef bool (*ClassPtr)(KeyCode arg0);
		auto origPtr = *reinterpret_cast<ClassPtr*>(&voidPtr);
		return (*origPtr)(arg0);
	}
	static bool GetKeyUp(KeyCode arg0) {
		void* voidPtr = g_methodPointers[102];
		typedef bool (*ClassPtr)(KeyCode arg0);
		auto origPtr = *reinterpret_cast<ClassPtr*>(&voidPtr);
		return (*origPtr)(arg0);
	}
};

#endif