//
// Created by Monika on 30.09.2021.
//

#ifndef GAMEENGINE_CHUNK_H
#define GAMEENGINE_CHUNK_H

#include <Utils/Math/Vector2.h>
#include <Utils/Types/SafePointer.h>
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

    class SR_DLL_EXPORT Chunk : public NonCopyable {
        using ScenePtr = SR_HTYPES_NS::SafePtr<Scene>;
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
        SR_NODISCARD SR_MATH_NS::FVector3 GetWorldPosition(SR_MATH_NS::Axis center = SR_MATH_NS::AXIS_NONE) const;
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

    //private:
    //    void SetDebugActive(BoolExt enabled);
    //    void SetDebugLoaded(BoolExt enabled);

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

        //uint64_t m_debugLoadedId = SR_ID_INVALID;
        //uint64_t m_debugActiveId = SR_ID_INVALID;

    };
}

#endif //GAMEENGINE_CHUNK_H
