//
// Created by Monika on 26.02.2023.
//

#include <Libraries/Utils/Allocator.h>
#include <Libraries/Types/Behaviour.h>
#include <Libraries/Math/Quaternion.h>

#include <Libraries/Debug.h>
#include <Libraries/Input.h>
#include <Libraries/Casts.h>
#include <Libraries/Observer.h>
#include <Libraries/Scene.h>
#include <Libraries/Mesh.h>

#define SR_ABS_CHUNK_POSITION_AXIS(regionAxis, ChunkAxis, regionSize) ((regionAxis > 0 ? regionAxis - 1 : regionAxis) * regionSize) + (ChunkAxis > 0 ? (ChunkAxis - 1) : (ChunkAxis + regionSize))

#define SR_ABS_CHUNK_POSITION(region, chunk, regionSize) IVector3 { \
        SR_ABS_CHUNK_POSITION_AXIS(region.x, chunk.x, regionSize),  \
        SR_ABS_CHUNK_POSITION_AXIS(region.y, chunk.y, regionSize),  \
        SR_ABS_CHUNK_POSITION_AXIS(region.z, chunk.z, regionSize) } \

class WorldGenerator : public Behaviour {
public:
    bool UpdateObserverPosition() {
        bool changed = false;

        if (auto&& region = m_observer->GetRegion(); region != m_region) {
            changed = true;
            m_region = region;
        }
        
        if (auto&& chunk = m_observer->GetChunk(); chunk != m_chunk) {
            changed = true;
            m_chunk = chunk;
        }

        if (auto&& scope = m_observer->GetScope(); scope != m_scope) {
            changed = true;
            m_scope = scope;
        }

        m_regionWidth = m_observer->GetRegionSize();

        return changed;
    }

    void CreateSpiral()
    {
        int x = 0;
    	int z = 0;

        int scope = std::max(1, m_scope - 3);
        int size = scope * 2 + 1;

        int boundary = size - 1;
        int sizeLeft = boundary;
        int flag = 1;

        char move = 'r';

        m_spiral.clear();

        for (int i = 1; i < size * size + 1; ++i)
        {
            if (m_logic->ScopeCheckFunction(x - scope, 0, z - scope)) {
                m_spiral.emplace(m_spiral.begin(), IVector3(x - scope, 0, z - scope));
            }

            switch (move) {
	            case 'r': x += 1; break;
	            case 'l': x -= 1; break;
	            case 'u': z -= 1; break;
	            case 'd': z += 1; break;
            }

            if (i == boundary)
            {
                boundary += sizeLeft;

                if (flag != 2) {
                    flag = 2;
                }
                else {
                    flag = 1;
                    sizeLeft -= 1;
                }

                switch (move) {
					case 'r': move = 'd'; break;
					case 'd': move = 'l'; break;
					case 'l': move = 'u'; break;
					case 'u': move = 'r'; break;
                }
            }
        }
    }

    void Awake() override {
        m_logic = DynamicCastSceneLogicToSceneCubeChunkLogic(scene->GetLogicBase());
        m_observer = m_logic->GetObserver();
        UpdateObserverPosition();
        ResetObserver();
    }

    void LoadCurrentChunk() {
        auto&& [region, chunk] = m_observer->MathNeighbour(m_currentSearch);

        if (!m_logic->IsChunkLoaded(region, chunk)) {
            return;
        } 
         
        auto&& position = m_logic->GetWorldPosition(region, chunk);
        auto&& absChunk = SR_ABS_CHUNK_POSITION(region, chunk, m_regionWidth);

        std::string name = "Chunk(" + std::to_string(absChunk.x) + ", " + std::to_string(absChunk.y) + ", " + std::to_string(absChunk.z) + ")";

        if (auto&& chunkPtr = scene->Find(name); !chunkPtr) {
            chunkPtr = scene->InstanceFromFile("Samples/ProceduralWorld/Chunk.prefab");
            chunkPtr->SetName(name);
            chunkPtr->GetTransform()->SetTranslation(position);

            /*chunkPtr = scene->Instance(name);


            if (!chunkPtr->GetComponent("Mesh3D")) {
                auto pCube = Mesh::Load("Engine/Models/cube.obj", MeshType::Static)[0];
                chunkPtr->AddComponent(DynamicCastMeshToComponent(pCube));
            }*/
        }
    }

    void SwitchToNextChunk() {
        if (m_spiralIndex >= m_spiral.size()) {
            m_spiralIndex = 0;
            m_allLoaded = true;
            return;
        }

        m_currentSearch = m_spiral[m_spiralIndex];
        ++m_spiralIndex;
    }

    void ResetObserver() {
        m_allLoaded = false;
        m_dt = 0.f;
        m_spiralIndex = 0;
        m_currentSearch = IVector3(-m_scope, -m_scope, -m_scope);
    }

    void Update(float_t dt) override {
        if (!m_observer || !m_observer->HasTarget()) {
            return;
        }

        if (UpdateObserverPosition()) {
            ResetObserver();
            CreateSpiral();
        }

        m_dt += dt;
        if (m_allLoaded || m_dt < 1.f) {
            return;
        }

        LoadCurrentChunk();
        SwitchToNextChunk();

        m_dt = 0.f;
    }

private:
    std::vector<IVector3> m_spiral;
    int m_spiralIndex = 0;

    Observer* m_observer = nullptr;
    SceneCubeChunkLogic* m_logic = nullptr;

    bool m_allLoaded = false;

    float_t m_dt = 0.f;

    IVector3 m_currentSearch;

    IVector3 m_region;
    IVector3 m_chunk;

    int32_t m_scope = 0;
    int32_t m_regionWidth = 0;

};

REGISTER_BEHAVIOUR(WorldGenerator)
