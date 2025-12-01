//
// Created by Monika on 28.06.2025.
//

#include <MarchingCubes/DensityGenerator.h>

#include <Scripting/Cpp/CppBehaviour.h>

#include <Utils/Common/StringAtomLiterals.h>
#include <Utils/FileSystem/PathDataAccessor.h>

namespace SpaRcle::Scripts::Samples {
    class MarchingCubes : public SpaRcle::Scripting::CppBehaviour {
        SR_CLASS()
    public:
	    struct alignas(16) Vertex {
			alignas(16) SR_MATH_NS::FVector3 position;
			alignas(16) SR_MATH_NS::FVector3 normal;
			alignas(16) SR_MATH_NS::FVector2 uv;
		};

        ~MarchingCubes() override {
            Finalize();
        }

        SR_NODISCARD bool ExecuteInEditMode() const override {
            return true; // Allow execution in edit mode for testing purposes
        }

        void OnDisable() override {
            Finalize();
        }

        void OnEnable() override {
            isDirty = true;
        }

        void GenerateDensity() {
            SR_TRACY_ZONE;

            const uint32_t countPexAxis = densityCountAxis;
            const auto densitiesCount = static_cast<uint64_t>(countPexAxis * countPexAxis * countPexAxis);
            pDensitySSBO = SR_GRAPH_NS::SSBOInstance::Create<float_t>(densitiesCount, SR_GRAPH_NS::SSBOUsage::CPUToGPU, "densities");
            pDensitySSBO->Memset(0);

            if (shape != MarchingCubesShape::Shader) {
                DensityFieldSettings settings;
                settings.noiseScale = noiseScale;
                settings.seed = seed;
                settings.isoLevel = isoLevel;
                settings.geometrySize = geometrySize;
                settings.densityCountAxis = countPexAxis;
                settings.shape = shape;

                std::vector<float_t> densities;
                GenerateDensityField(settings, densities);
                pDensitySSBO->UpdateSSBO(densities.data());
                return;
            }

            if (pDensityComputeShader->BeginCompute()) {
                pDensitySSBO->Bind();
                pDensityComputeShader->GetShader()->SetConstInt("densityCountAxis"_atom, static_cast<int>(countPexAxis));
                pDensityComputeShader->GetShader()->SetConstInt("seed"_atom, static_cast<int>(seed));
                pDensityComputeShader->GetShader()->SetConstFloat("isoLevel"_atom, isoLevel);
                pDensityComputeShader->GetShader()->SetConstFloat("noiseScale"_atom, noiseScale);
                pDensityComputeShader->GetShader()->SetConstIVec3("chunkCoord"_atom, chunkCoord);
                pDensityComputeShader->Dispatch(densityComputeGroups, densityComputeGroups, densityComputeGroups);
                pDensityComputeShader->EndCompute();
            }
        }

        void ReInit() {
            SR_TRACY_ZONE;

            if (!isDirty) {
                return;
            }

            isDirty = false;

            Finalize();

            pMarchingComputeShader = SR_GTYPES_NS::ComputeShader::Load(marchingCubesShader);
            pDensityComputeShader = SR_GTYPES_NS::ComputeShader::Load(densityShader);

            if (!pMarchingComputeShader || !pDensityComputeShader) {
                SRHalt("Failed to load compute shaders for Marching Cubes!");
                return;
            }

            const int numVoxelsPerAxis = numPointsPerAxis - 1;
            const int numVoxels = numVoxelsPerAxis * numVoxelsPerAxis * numVoxelsPerAxis;
            const int maxTriangleCount = numVoxels * 5;
            const int maxVertexCount = maxTriangleCount * 3;

            pHashTableSSBO = SR_GRAPH_NS::SSBOInstance::Create<uint32_t>(vertexHashTableSize, SR_GRAPH_NS::SSBOUsage::CPUToGPU, "hashTable");
            pVerticesSSBO = SR_GRAPH_NS::SSBOInstance::Create<Vertex>(maxVertexCount, SR_GRAPH_NS::SSBOUsage::GPUToCPU, "vertices", SR_GRAPH_NS::SSBOFlags::StructuredCounter);
            pIndicesSSBO = SR_GRAPH_NS::SSBOInstance::Create<uint32_t>(maxVertexCount, SR_GRAPH_NS::SSBOUsage::GPUToCPU, "indices", SR_GRAPH_NS::SSBOFlags::Counter);

            GenerateDensity();
            Generate();
        }

        void Generate() {
            SR_TRACY_ZONE;

            if (!pMarchingComputeShader) {
                return;
            }

            int numVoxelsPerAxis = numPointsPerAxis - 1;
            if (numVoxelsPerAxis <= 0) {
                return;
            }

            pHashTableSSBO->Memset(-1);

            for (int stage = 0; stage <= 1; ++stage) {
                if (pMarchingComputeShader->BeginCompute()) {
                    pDensitySSBO->Bind();
                    pHashTableSSBO->Bind();
                    pVerticesSSBO->Bind();
                    pIndicesSSBO->Bind();
                    pMarchingComputeShader->GetShader()->SetConstInt("vertexHashTableSize"_atom, static_cast<int>(vertexHashTableSize));
                    pMarchingComputeShader->GetShader()->SetConstInt("densityCountAxis"_atom, static_cast<int>(densityCountAxis));
                    pMarchingComputeShader->GetShader()->SetConstFloat("isoLevel"_atom, isoLevel);
                    pMarchingComputeShader->GetShader()->SetConstInt(SR_GRAPH_NS::SHADER_COMPUTE_STAGE, stage);
                    pMarchingComputeShader->Dispatch(numVoxelsPerAxis, numVoxelsPerAxis, numVoxelsPerAxis);
                    pMarchingComputeShader->EndCompute();
                }
            }

            GenerateMesh();
        }

        void ReadIndices() {
            SR_TRACY_ZONE;

            if (void* pData = pIndicesSSBO->MapData()) {
                const uint32_t indicesCount = pIndicesSSBO->GetCounter();
                indices.resize(indicesCount);
                std::memcpy(indices.data(), pData, sizeof(uint32_t) * indicesCount);
                pIndicesSSBO->ResetCounter();
                pIndicesSSBO->FlushCounter();
                pIndicesSSBO->UnMap();
            }
        }

        void ReadVertices() {
            SR_TRACY_ZONE;

            if (auto&& pVertices = reinterpret_cast<Vertex*>(pVerticesSSBO->MapData())) {
                const uint32_t verticesCount = pVerticesSSBO->GetCounter();
                vertices.resize(verticesCount);

                auto&& range = std::views::iota(0, static_cast<int>(verticesCount));

                std::for_each(std::execution::par_unseq, range.begin(), range.end(), [&](int index) {
                    const Vertex& vertex = pVertices[index];
                    vertices[index] = SR_GRAPH_NS::Vertices::StaticMeshVertex{
                        .pos = vertex.position,
                        .uv = vertex.uv,
                        .norm = vertex.normal
                    };
                });

                pVerticesSSBO->ResetCounter();
                pVerticesSSBO->FlushCounter();
                pVerticesSSBO->UnMap();
            }
        }

        void GenerateMesh() {
            SR_TRACY_ZONE;

            if (isDirty) {
                return;
            }

            ReadIndices();
            ReadVertices();

            if (gameObject) {
                if (auto&& pProceduralMesh = gameObject->GetComponent<SR_GTYPES_NS::ProceduralMesh>()) {
                    pProceduralMesh->SwapIndices(indices);
                    pProceduralMesh->SwapIndexedVertices(vertices);
                }
            }
        }

        void Update(float_t dt) override {
            if (isDirty) {
                ReInit();
            }
            else if (generateEveryFrame) {
                Generate();
            }

            if (exportMesh) {
                if (auto&& pProceduralMesh = gameObject->GetComponent<SR_GTYPES_NS::ProceduralMesh>()) {
                    if (!pProceduralMesh->Export(SR_UTILS_NS::ResourceManager::Instance().GetCachePath().Concat("MarchingCubesMesh.obj"))) {
                        SR_ERROR("Failed to export Marching Cubes mesh!");
                    }
                }
                exportMesh = false; // Reset after export
            }
        }

        void Finalize() {
            SR_TRACY_ZONE;

            pVerticesSSBO = nullptr;
            pIndicesSSBO = nullptr;
            pHashTableSSBO = nullptr;
            pDensitySSBO = nullptr;
            pDensityComputeShader = nullptr;
            pMarchingComputeShader = nullptr;
        }

    private:
        SR_HTYPES_NS::FastMemoryArray<SR_GRAPH_NS::Vertices::StaticMeshVertex> vertices;
        SR_HTYPES_NS::FastMemoryArray<uint32_t> indices;

        bool isDirty = true;

        SR_GTYPES_NS::ComputeShader::Ptr pMarchingComputeShader = nullptr;
        SR_GTYPES_NS::ComputeShader::Ptr pDensityComputeShader = nullptr;

        SR_GRAPH_NS::SSBOInstance::Ptr pDensitySSBO = nullptr;
        SR_GRAPH_NS::SSBOInstance::Ptr pHashTableSSBO = nullptr;
        SR_GRAPH_NS::SSBOInstance::Ptr pVerticesSSBO = nullptr;
        SR_GRAPH_NS::SSBOInstance::Ptr pIndicesSSBO = nullptr;

        /// @property @onChanged(OnEnable)
        uint32_t numPointsPerAxis = 10;

        /// @property @onChanged(OnEnable)
        uint32_t vertexHashTableSize = 65536;

        /// @property @onChanged(OnEnable)
        uint32_t densityCountAxis = 64;

        /// @property @onChanged(OnEnable)
        uint32_t densityComputeGroups = 8;

        /// @property @onChanged(OnEnable)
        float_t noiseScale = 10.0f;
        /// @property @onChanged(OnEnable)
        int64_t seed = 1;
        /// @property @onChanged(OnEnable)
        float_t geometrySize = 1.f;
        /// @property @onChanged(OnEnable)
        float_t isoLevel = 0.2f;
        /// @property
        bool generateEveryFrame = false;
        /// @property
        bool exportMesh = false;

        /// @property @onChanged(OnEnable)
        SR_MATH_NS::IVector3 chunkCoord;

        /// @property @onChanged(OnEnable)
        MarchingCubesShape shape = MarchingCubesShape::Sphere;

        /// @property
        SR_UTILS_NS::Path marchingCubesShader = "Samples/MarchingCubes/MarchingCubes.srsl";
        /// @property
        SR_UTILS_NS::Path densityShader = "Samples/MarchingCubes/Density.srsl";

    };
}

#include <Codegen/MarchingCubes.generated.hpp>