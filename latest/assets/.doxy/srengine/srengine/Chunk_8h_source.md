

# File Chunk.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Utils**](dir_f3d6dc6978aa78088efd06c6b2710310.md) **>** [**inc**](dir_e0f1b8570fc577fb78354cd460e9e760.md) **>** [**Utils**](dir_06a42b3e946fb631201a76a22d1aab06.md) **>** [**World**](dir_646ea3957657c91e40c16f5ff19dad51.md) **>** [**Chunk.h**](Chunk_8h.md)

[Go to the documentation of this file](Chunk_8h.md)


```C++
//
// Created by Monika on 30.09.2021.
//

#ifndef SR_ENGINE_CHUNK_H
#define SR_ENGINE_CHUNK_H

#include <Utils/Math/Vector2.h>
#include <Utils/Types/SharedPtr.h>
#include <Utils/Types/SharedPtr.h>
#include <Utils/Types/DataStorage.h>
#include <Utils/Types/Marshal.h>
#include <Utils/World/Observer.h>

namespace SR_UTILS_NS {
    class GameObject;
}

namespace SR_WORLD_NS {
    class Scene;
    class Region;
    class Chunk;
    class Observer;

    #define SRChunkAllocArgs SR_WORLD_NS::Observer* observer, SR_WORLD_NS::Region* region, const SR_MATH_NS::IVector3& position, const SR_MATH_NS::IVector2& size
    #define SRChunkAllocVArgs observer, region, position, size

    class SR_COMMON_DLL_API Chunk : public NonCopyable {
        using ScenePtr = SR_HTYPES_NS::SharedPtr<Scene>;
    protected:
        Chunk(SRChunkAllocArgs);

    public:
        ~Chunk() override;

        enum class LoadState {
            PreLoaded, Loaded, Unload, Preload
        };

    public:
        typedef std::function<Chunk*(SRChunkAllocArgs)> Allocator;

    public:
        static void SetAllocator(const Allocator& allocator);
        static Chunk* Allocate(SRChunkAllocArgs);
        static bool Belongs(const Math::IVector3& position, const Math::IVector2& size, const Math::FVector3& point);

    public:
        SR_NODISCARD LoadState GetState() const { return m_loadState; }
        SR_NODISCARD bool IsAlive() const { return m_lifetime > 0; }
        SR_NODISCARD bool IsPreLoaded() const { return m_loadState == LoadState::PreLoaded; }
        SR_NODISCARD SR_MATH_NS::IVector3 GetPosition() const { return m_position; }
        SR_NODISCARD SR_MATH_NS::FVector3 GetWorldPosition(SR_MATH_NS::Axis center = SR_MATH_NS::Axis::None) const;
        SR_NODISCARD ScenePtr GetScene() const;

        SR_NODISCARD SR_HTYPES_NS::Marshal::Ptr Save(SR_HTYPES_NS::DataStorage* pContext) const;

    public:
        virtual void OnEnter();
        virtual void OnExit();
        virtual void Reload();
        virtual void Update(float_t dt);
        virtual bool Access(float_t dt);
        virtual bool Belongs(const Math::FVector3& point);
        virtual bool Unload();
        virtual bool PreLoad(SR_HTYPES_NS::Marshal* pMarshal);
        virtual bool Load();

        virtual bool ApplyOffset();

    private:
        static Allocator g_allocator;

    protected:
        LoadState m_loadState;

        Observer* m_observer;
        Region* m_region;

        float_t m_lifetime;

        SR_MATH_NS::IVector2 m_size;
        SR_MATH_NS::IVector3 m_regionPosition;
        SR_MATH_NS::IVector3 m_position;

        std::list<SR_HTYPES_NS::SharedPtr<GameObject>> m_preloaded;

    };
}

#endif //SR_ENGINE_CHUNK_H
```


