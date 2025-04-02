

# File Region.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Utils**](dir_f3d6dc6978aa78088efd06c6b2710310.md) **>** [**inc**](dir_e0f1b8570fc577fb78354cd460e9e760.md) **>** [**Utils**](dir_06a42b3e946fb631201a76a22d1aab06.md) **>** [**World**](dir_646ea3957657c91e40c16f5ff19dad51.md) **>** [**Region.h**](Region_8h.md)

[Go to the documentation of this file](Region_8h.md)


```C++
//
// Created by Monika on 30.09.2021.
//

#ifndef SR_ENGINE_REGION_H
#define SR_ENGINE_REGION_H

#include <Utils/Math/Vector3.h>
#include <Utils/World/Observer.h>
#include <Utils/Resources/Xml.h>

#define SRRegionAllocArgs SR_WORLD_NS::Observer* observer, uint32_t width, const SR_MATH_NS::IVector2& chunkSize, const SR_MATH_NS::IVector3& position
#define SRRegionAllocVArgs observer, width, chunkSize, position

namespace SR_UTILS_NS {
    class GameObject;
}

namespace SR_WORLD_NS {
    class Chunk;
    class Scene;
    class Region;
    class Observer;

    typedef std::unordered_map<Math::IVector3, Chunk*> Chunks;
    typedef std::unordered_map<Math::IVector3, SR_HTYPES_NS::Marshal::Ptr> CachedChunks;

    class SR_DLL_EXPORT Region : public NonCopyable {
        using ScenePtr = SR_HTYPES_NS::SharedPtr<Scene>;
    protected:
        explicit Region(SRRegionAllocArgs)
            : m_observer(observer)
            , m_width(width)
            , m_chunkSize(chunkSize)
            , m_position(position)
            , m_containsObserver(false)
        {
            //m_cached.resize(width * width * width);
            //m_loadedChunks.resize(width * width * width);
        }

    public:
        ~Region() override;

    public:
        virtual void Update(float_t dt);
        virtual bool Load();
        virtual bool PostLoad();
        virtual bool Unload(bool force = false);
        virtual void OnEnter();
        virtual void OnExit();
        virtual void Reload();

        virtual void ApplyOffset();

    public:
        Chunk* GetChunk(const Math::IVector3& position);
        Chunk* GetChunk(const Math::FVector3& position);

        SR_NODISCARD const Chunks& GetChunks() const noexcept { return m_loadedChunks; }
        SR_NODISCARD Chunk* At(const Math::IVector3& position) const;
        SR_NODISCARD Chunk* Find(const Math::IVector3& position) const;
        SR_NODISCARD uint32_t GetWidth() const { return m_width; }
        SR_NODISCARD bool IsAlive() const { return !m_loadedChunks.empty(); }
        SR_NODISCARD Math::IVector3 GetPosition() const { return m_position; }
        SR_NODISCARD Math::IVector3 GetWorldPosition() const;
        SR_NODISCARD bool ContainsObserver() const { return m_containsObserver; }
        SR_NODISCARD bool IsChunkLoaded(const SR_MATH_NS::IVector3& chunk) const;
        SR_NODISCARD ScenePtr GetScene() const;

        SR_NODISCARD SR_HTYPES_NS::Marshal::Ptr Save(SR_HTYPES_NS::DataStorage* pContext) const;

    public:
        typedef std::function<Region*(SRRegionAllocArgs)> Allocator;

        static void SetAllocator(const Allocator& allocator);
        static Region* Allocate(SRRegionAllocArgs);

    private:
        static Allocator g_allocator;
        static const uint16_t VERSION;

    protected:
        Observer* m_observer = nullptr;

        Chunks m_loadedChunks;
        CachedChunks m_cached;
        uint32_t m_width;
        Math::IVector2 m_chunkSize;
        Math::IVector3 m_position;
        std::atomic<bool> m_containsObserver;

    };
}

#endif //SR_ENGINE_REGION_H
```


