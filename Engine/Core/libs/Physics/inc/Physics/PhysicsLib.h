//
// Created by Monika on 28.07.2022.
//

#ifndef SRENGINE_PHYSICSLIB_H
#define SRENGINE_PHYSICSLIB_H

#include <Utils/Common/Enumerations.h>
#include <Utils/Common/Singleton.h>
#include <Utils/Math/Vector3.h>

#include <Physics/Utils/Utils.h>

namespace SR_PHYSICS_NS {
    class LibraryImpl;

    class PhysicsLibrary : public SR_UTILS_NS::Singleton<PhysicsLibrary> {
        friend class SR_UTILS_NS::Singleton<PhysicsLibrary>;
        using Super = SR_UTILS_NS::Singleton<PhysicsLibrary>;
    public:
        PhysicsLibrary();
        ~PhysicsLibrary() override;

    public:
        SR_NODISCARD LibraryImpl* GetLibrary(LibraryType type);
        SR_NODISCARD LibraryImpl* GetActiveLibrary();

    private:
        std::vector<LibraryImpl*> m_libraries;

    };
}

#endif //SRENGINE_PHYSICSLIB_H
