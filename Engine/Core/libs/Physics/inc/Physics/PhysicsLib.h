//
// Created by Monika on 28.07.2022.
//

#ifndef SRENGINE_PHYSICSLIB_H
#define SRENGINE_PHYSICSLIB_H

#include <Utils/Common/Measurement.h>
#include <Utils/Common/Singleton.h>
#include <Utils/Math/Vector3.h>

#include <Physics/Utils/Utils.h>

namespace SR_PHYSICS_NS {
    class LibraryImpl;

    class PhysicsLibrary : public SR_UTILS_NS::Singleton<PhysicsLibrary> {
        friend class SR_UTILS_NS::Singleton<PhysicsLibrary>;
        using Super = SR_UTILS_NS::Singleton<PhysicsLibrary>;
        using Space = SR_UTILS_NS::Measurement;
        using LibraryTypes = std::vector<LibraryType>;
    public:
        PhysicsLibrary();
        ~PhysicsLibrary() override;

    public:
        SR_NODISCARD LibraryImpl* GetLibrary(LibraryType type);
        SR_NODISCARD LibraryImpl* GetActiveLibrary(Space space);
        SR_NODISCARD LibraryTypes GetSupportedLibraries() const;

    protected:
        void InitSingleton() override;

    private:
        std::vector<LibraryImpl*> m_libraries;
        std::map<Space, LibraryType> m_activeLibs;
        std::set<LibraryType> m_supportedLibs;

    };
}

#endif //SRENGINE_PHYSICSLIB_H
