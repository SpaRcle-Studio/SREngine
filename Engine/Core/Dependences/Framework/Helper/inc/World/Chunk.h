//
// Created by Monika on 30.09.2021.
//

#ifndef GAMEENGINE_CHUNK_H
#define GAMEENGINE_CHUNK_H

#include <EntityComponentSystem/GameObject.h>
#include <Math/Vector2.h>
#include <Types/SafePointer.h>
#include <World/Observer.h>

namespace Framework::Helper {
    class GameObject;

    namespace World {
        class Scene;
        class Region;
        class Chunk;
        class Observer;

        #define SRChunkAllocArgs Framework::Helper::World::Observer* observer, Framework::Helper::World::Region* region, const Framework::Helper::Math::IVector3& position, const Framework::Helper::Math::IVector2& size
        #define SRChunkAllocVArgs observer, region, position, size

        class Chunk {
        protected:
            Chunk(SRChunkAllocArgs);

        public:
            virtual ~Chunk();

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
            [[nodiscard]] LoadState GetState() const { return m_loadState; }
            [[nodiscard]] bool IsAlive() const { return m_lifetime > 0; }
            [[nodiscard]] Math::IVector3 GetPosition() const { return m_position; }
            [[nodiscard]] Math::FVector3 GetWorldPosition(Math::Axis center = Math::AXIS_NONE) const;

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
}

#endif //GAMEENGINE_CHUNK_H
