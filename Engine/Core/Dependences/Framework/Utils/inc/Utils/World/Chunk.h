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
    protected:
        Chunk(SRChunkAllocArgs);

    public:
        ~Chunk() override = default;

        enum class LoadState {
            Loaded, Unload, Preload
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
        SR_NODISCARD Math::IVector3 GetPosition() const { return m_position; }
        SR_NODISCARD Math::FVector3 GetWorldPosition(Math::Axis center = Math::AXIS_NONE) const;

        SR_NODISCARD SR_HTYPES_NS::Marshal Save() const;

    public:
        virtual void OnEnter();
        virtual void OnExit();
        virtual void Reload();
        virtual void Update(float_t dt);
        virtual bool Access(float_t dt);
        virtual bool Belongs(const Math::FVector3& point);
        virtual bool Unload();
        virtual bool Load(SR_HTYPES_NS::Marshal&& marshal);

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

    };
}

#endif //GAMEENGINE_CHUNK_H
