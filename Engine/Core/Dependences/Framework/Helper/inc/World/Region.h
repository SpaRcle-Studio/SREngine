//
// Created by Monika on 30.09.2021.
//

#ifndef GAMEENGINE_REGION_H
#define GAMEENGINE_REGION_H

#include <Math/Vector3.h>
#include <unordered_map>
#include <functional>
#include <World/Observer.h>

namespace Framework::Helper {
    class GameObject;

    namespace World {
        class Chunk;
        class Scene;
        class Region;

        typedef std::unordered_map<Math::IVector3, Chunk*> Chunks;

        #define SRRegionAllocArgs uint32_t width, const Framework::Helper::Math::IVector2& chunkSize, const Framework::Helper::Math::IVector2& position
        #define SRRegionAllocVArgs width, chunkSize, position

        class Region {
        protected:
            explicit Region(SRRegionAllocArgs)
                : m_width(width)
                , m_chunkSize(chunkSize)
                , m_position(position)
            { }

        public:
            virtual ~Region();

        public:
            typedef std::function<Region*(SRRegionAllocArgs)> Allocator;

        public:
            [[nodiscard]] Math::IVector2 GetPosition() const { return m_position; }
            [[nodiscard]] Math::IVector2 GetWorldPosition() const;

        public:
            virtual void Update(float_t dt);
            virtual bool Unload();
            virtual void OnEnter();
            virtual void OnExit();

            virtual void SetOffset(const World::Offset& offset);
            virtual void ApplyOffset();

        public:
            Chunk* GetChunk(const Math::IVector3& position);
            [[nodiscard]] Chunk* At(const Math::IVector3& position) const;
            [[nodiscard]] Chunk* Find(const Math::IVector3& position) const;
            [[nodiscard]] uint32_t GetWidth() const { return m_width; }

        public:
            static void SetAllocator(const Allocator& allocator);
            static Region* Allocate(SRRegionAllocArgs);

        private:
            static Allocator g_allocator;

        protected:
            Chunks m_loadedChunks;
            uint32_t m_width;
            Math::IVector2 m_chunkSize;
            Math::IVector2 m_position;
            World::Offset m_offset;
        };
    }
}

#endif //GAMEENGINE_REGION_H
