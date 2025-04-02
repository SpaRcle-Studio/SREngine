

# File PhysicsLib.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Physics**](dir_519f717f3cdf5b5486fbfb20b03d90e0.md) **>** [**inc**](dir_caed82ebc61f04cfe4cf46381d77d744.md) **>** [**Physics**](dir_0ab9965f62ec4b8feb4217f1d72c6eed.md) **>** [**PhysicsLib.h**](PhysicsLib_8h.md)

[Go to the documentation of this file](PhysicsLib_8h.md)


```C++
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
```


