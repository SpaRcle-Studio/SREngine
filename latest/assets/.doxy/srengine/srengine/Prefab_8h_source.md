

# File Prefab.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Utils**](dir_f3d6dc6978aa78088efd06c6b2710310.md) **>** [**inc**](dir_e0f1b8570fc577fb78354cd460e9e760.md) **>** [**Utils**](dir_06a42b3e946fb631201a76a22d1aab06.md) **>** [**ECS**](dir_d56b953042ff1935f3f30a5ce5fa4a33.md) **>** [**Prefab.h**](Prefab_8h.md)

[Go to the documentation of this file](Prefab_8h.md)


```C++
//
// Created by Monika on 26.11.2022.
//

#ifndef SR_ENGINE_PREFAB_H
#define SR_ENGINE_PREFAB_H

#include <Utils/Resources/IResource.h>
#include <Utils/Types/SharedPtr.h>

namespace SR_HTYPES_NS {
    class Marshal;
}

namespace SR_WORLD_NS {
    class Scene;
}

namespace SR_UTILS_NS {
    class SceneObject;

    class SR_DLL_EXPORT Prefab : public IResource {
    public:
        using SceneObjectPtr = SR_HTYPES_NS::SharedPtr<SceneObject>;
        using ScenePtr = SR_WORLD_NS::Scene*;

        static constexpr const char* EXTENSION = "prefab";

    private:
        Prefab();
        ~Prefab() override;

    public:
        static Prefab* Load(const SR_UTILS_NS::Path& rawPath);

        SR_NODISCARD bool LoadToSO(const SceneObjectPtr& pSO);
        SR_NODISCARD SceneObjectPtr Instance(const ScenePtr& scene) const;
        SR_NODISCARD const SceneObjectPtr& GetData() const noexcept { return m_data; }

    protected:
        bool Unload() override;
        bool Load() override;

    private:
        SceneObjectPtr m_data;
        SR_UTILS_NS::IDeserializer* m_pDeserializer = nullptr;

    };
}

#endif //SR_ENGINE_PREFAB_H
```


