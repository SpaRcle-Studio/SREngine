//
// Created by Monika on 30.09.2021.
//

#ifndef GAMEENGINE_CHUNK_H
#define GAMEENGINE_CHUNK_H

#include <unordered_set>
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

        #define SRChunkAllocArgs Helper::World::Region* region, const Framework::Helper::Math::IVector3& position, const Framework::Helper::Math::IVector2& size
        #define SRChunkAllocVArgs region, position, size

        class Chunk {
        protected:
            Chunk(SRChunkAllocArgs);

        public:
            virtual ~Chunk();

        public:
            typedef std::function<Chunk*(SRChunkAllocArgs)> Allocator;

        public:
            static void SetAllocator(const Allocator& allocator);
            static Chunk* Allocate(SRChunkAllocArgs);
            static bool Belongs(const Math::IVector3& position, const Math::IVector2& size, const Math::FVector3& point);

        public:
            bool Clear();
            void Insert(const GameObject::Ptr& ptr);
            void Erase(const GameObject::Ptr& ptr);
            uint32_t GetContainerSize() const;

        public:
            virtual void OnEnter();
            virtual void OnExit();
            virtual void Update(float_t dt);
            virtual bool Access(const Math::FVector3& point);
            virtual bool Belongs(const Math::FVector3& point);
            virtual bool Unload();

            virtual bool ApplyOffset();
            virtual void SetOffset(const World::Offset& offset);

        private:
            static Allocator g_allocator;

        protected:
            Region* m_region;

            std::unordered_set<GameObject::Ptr> m_container;
            Types::SafePtr<World::Scene> m_scene;

            float_t m_lifetime;

            Math::IVector2 m_size;
            Math::IVector3 m_position;

            World::Offset m_offset;
            World::Offset m_delta;
        };
    }
}

#endif //GAMEENGINE_CHUNK_H
