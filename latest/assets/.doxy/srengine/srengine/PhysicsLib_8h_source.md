

# File PhysicsLib.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Physics**](dir_b6093f632646a02ac714961018ea77eb.md) **>** [**inc**](dir_c3db09d6a2a4255c529e8dd3a426d758.md) **>** [**Physics**](dir_d2d325d8d5dbff54ef03880cbcd3bb2d.md) **>** [**PhysicsLib.h**](PhysicsLib_8h.md)

[Go to the documentation of this file](PhysicsLib_8h.md)


```C++
//
// Created by Monika on 28.07.2022.
//

#ifndef SR_ENGINE_PHYSICSLIB_H
#define SR_ENGINE_PHYSICSLIB_H

#include <Physics/macros.h>

#include <Utils/Common/Measurement.h>
#include <Utils/Common/Singleton.h>
#include <Utils/Math/Vector3.h>
#include <Utils/Types/SharedPtr.h>

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

        SR_NODISCARD SR_HTYPES_NS::SharedPtr<SR_PTYPES_NS::PhysicsMaterial> GetDefaultMaterial() const noexcept { return m_defaultMaterial; }

    protected:
        void InitSingleton() override;
        void OnSingletonDestroy() override;

    private:
        std::vector<LibraryImpl*> m_libraries;
        std::map<Space, LibraryType> m_activeLibs;
        std::set<LibraryType> m_supportedLibs;

        SR_HTYPES_NS::SharedPtr<SR_PTYPES_NS::PhysicsMaterial> m_defaultMaterial = nullptr;
    };
}

#endif //SR_ENGINE_PHYSICSLIB_H
```


