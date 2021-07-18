#ifndef EVOSCRIPTLIB_ADDRESSES_H
#define EVOSCRIPTLIB_ADDRESSES_H

#define EXTERN extern "C" __declspec(dllexport)

void** g_methodPointers; 

EXTERN void Init(void** methodPointers) {
	g_methodPointers = methodPointers;
}

#endif
