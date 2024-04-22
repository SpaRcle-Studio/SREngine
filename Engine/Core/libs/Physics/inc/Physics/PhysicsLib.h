//
// Created by Monika on 28.07.2022.
//

#ifndef SR_ENGINE_PHYSICSLIB_H
#define SR_ENGINE_PHYSICSLIB_H

#include <Utils/Common/Measurement.h>
#include <Utils/Common/Singleton.h>
#include <Utils/Math/Vector3.h>

#include <Physics/Utils/Utils.h>

namespace SR_PTYPES_NS {
    class PhysicsMaterial;
}

namespace SR_PHYSICS_NS {
    class LibraryImpl;

    class PhysicsLibrary : public SR_UTILS_NS::Singleton<PhysicsLibrary> {
        SR_REGISTER_SINGLETON(PhysicsLibrary)
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

        SR_NODISCARD SR_PTYPES_NS::PhysicsMaterial* GetDefaultMaterial() const noexcept { return m_defaultMaterial; }

    protected:
        void InitSingleton() override;
        void OnSingletonDestroy() override;

    private:
        std::vector<LibraryImpl*> m_libraries;
        std::map<Space, LibraryType> m_activeLibs;
        std::set<LibraryType> m_supportedLibs;

        SR_PTYPES_NS::PhysicsMaterial* m_defaultMaterial = nullptr;
    };
}

#endif //SR_ENGINE_PHYSICSLIB_H
