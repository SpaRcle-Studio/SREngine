//
// Created by Monika on 09.08.2022.
//

#ifndef SRENGINE_ALLOCATOR_H
#define SRENGINE_ALLOCATOR_H

#include <MemoryAllocator.h>

void* operator new(size_t sz) {
    return ESMemoryAlloc(sz);
}

void operator delete(void* ptr) {
    ESMemoryFree(ptr);
}

void* operator new[](size_t sz) {
    return ESMemoryAlloc(sz);
}

void operator delete[](void* ptr) {
    ESMemoryFree(ptr);
}

#endif //SRENGINE_ALLOCATOR_H
