//
// Created by Monika on 30.09.2021.
//

#ifndef GAMEENGINE_REGION_H
#define GAMEENGINE_REGION_H

#include <Math/Vector3.h>
#include <unordered_map>
#include <functional>
#include <World/Observer.h>
#include <Xml.h>

namespace Framework::Helper {
    class GameObject;

    namespace World {
        class Chunk;
        class Scene;
        class Region;
        class Observer;

        typedef std::unordered_map<Math::IVector3, Chunk*> Chunks;
        typedef std::unordered_map<Math::IVector3, MarshalEncodeNode> CachedChunks;

        #define SRRegionAllocArgs Framework::Helper::World::Observer* observer, uint32_t width, const Framework::Helper::Math::IVector2& chunkSize, const Framework::Helper::Math::IVector3& position
        #define SRRegionAllocVArgs observer, width, chunkSize, position

        class Region {
        protected:
            explicit Region(SRRegionAllocArgs)
                : m_observer(observer)
                , m_width(width)
                , m_chunkSize(chunkSize)
                , m_position(position)
                , m_containsObserver(false)
            { }

        public:
            virtual ~Region();

        public:
            virtual void Update(float_t dt);
            virtual bool Load();
            virtual bool Unload();
            virtual void OnEnter();
            virtual void OnExit();
            virtual void Reload();

            virtual void ApplyOffset();

        public:
            Chunk* GetChunk(const Math::IVector3& position);
            Chunk* GetChunk(const Math::FVector3& position);

            SR_NODISCARD Chunk* At(const Math::IVector3& position) const;
            SR_NODISCARD Chunk* Find(const Math::IVector3& position) const;
            SR_NODISCARD uint32_t GetWidth() const { return m_width; }
            SR_NODISCARD bool IsAlive() const { return !m_loadedChunks.empty(); }
            SR_NODISCARD Math::IVector3 GetPosition() const { return m_position; }
            SR_NODISCARD Math::IVector3 GetWorldPosition() const;
            SR_NODISCARD bool ContainsObserver() const { return m_containsObserver; }

            SR_NODISCARD MarshalEncodeNode Save() const;

        public:
            typedef std::function<Region*(SRRegionAllocArgs)> Allocator;

            static void SetAllocator(const Allocator& allocator);
            static Region* Allocate(SRRegionAllocArgs);

        private:
            static Allocator g_allocator;

        protected:
            Observer* m_observer;
            Chunks m_loadedChunks;
            CachedChunks m_cached;
            uint32_t m_width;
            Math::IVector2 m_chunkSize;
            Math::IVector3 m_position;
            std::atomic<bool> m_containsObserver;

        };
    }
}

#endif //GAMEENGINE_REGION_H
