

# File Prefab.h

[**File List**](files.md) **>** [**ECS**](dir_df4674c010a45d2af7a2a452a0d36896.md) **>** [**Prefab.h**](Prefab_8h.md)

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

    class SR_COMMON_DLL_API Prefab : public IResource {
        SR_CLASS()
    public:
        using Ptr = SR_HTYPES_NS::SharedPtr<Prefab>;

    public:
        using SceneObjectPtr = SR_HTYPES_NS::SharedPtr<SceneObject>;
        using ScenePtr = SR_WORLD_NS::Scene*;

        static constexpr const char* EXTENSION = "prefab";

    public:
        Prefab();
        ~Prefab() override;

    public:
        static Prefab::Ptr Load(const SR_UTILS_NS::Path& rawPath);

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


