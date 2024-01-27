//
// Created by innerviewer on 3/4/2023.
//

#ifndef SR_ENGINE_PHYSICSMATERIALIMPL_H
#define SR_ENGINE_PHYSICSMATERIALIMPL_H

#include <Utils/Common/NonCopyable.h>

namespace SR_PHYSICS_NS {
    class LibraryImpl;
}

namespace SR_PTYPES_NS {
    class PhysicsMaterialImpl : public SR_UTILS_NS::NonCopyable {
        using Super = SR_UTILS_NS::NonCopyable;
        using LibraryPtr = SR_PHYSICS_NS::LibraryImpl*;
    protected:
        explicit PhysicsMaterialImpl(LibraryPtr pLibrary)
            : Super()
            , m_library(pLibrary)
        { }

    public:
        virtual bool Init() = 0;
        virtual void DeInit() = 0;

        template<typename T> SR_NODISCARD T* GetLibrary() const {
            if (auto&& pLibrary = dynamic_cast<T*>(m_library)) {
                return pLibrary;
            }

            SRHalt("Failed to cast library!");

            return nullptr;
        }

        SR_NODISCARD virtual void* GetHandle() = 0;

        virtual void SetMaterial(PhysicsMaterial* pMaterial) = 0;

    private:
        SR_PHYSICS_NS::LibraryImpl* m_library = nullptr;
    };
}

#endif //SR_ENGINE_PHYSICSMATERIALIMPL_H
