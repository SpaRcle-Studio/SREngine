//
// Created by Monika on 28.06.2025.
//


#include <Utils/Input/KeyCodes.h>
#include <Utils/Math/Vector2.h>
#include <Utils/Math/Noise.h>
#include <Utils/Math/VectorRanges.h>

#include <Graphics/Types/Geometry/ProceduralMesh.h>
#include <Graphics/Types/ComputeShader.h>
#include <Graphics/Render/RenderContext.h>

#include <Scripting/Cpp/CppBehaviour.h>

namespace SpaRcle::Scripts::Samples {
    namespace Detail {
        struct alignas(16) Vertex {
             alignas(16) SR_MATH_NS::FVector3 position;
             alignas(16) SR_MATH_NS::FVector3 normal;
             alignas(16) SR_MATH_NS::IVector2 id;
        };

        struct alignas(16) Triangle {
             alignas(16) Vertex vertexC;
             alignas(16) Vertex vertexB;
             alignas(16) Vertex vertexA;
        };
    }

    class MarchingCubes : public SpaRcle::Scripting::CppBehaviour {
        SR_CLASS()
    public:
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
            Finalize();

            m_computeShader = SR_GTYPES_NS::ComputeShader::Load(shaderPath);

            if (m_computeShader) {
                constexpr uint64_t dataSize = sizeof(uint32_t) + 12 + sizeof(Detail::Triangle) * 64;
                SSBO = m_computeShader->GetPipeline()->AllocateSSBO(dataSize, SR_GRAPH_NS::SSBOUsage::Read);
            }

            Generate();
        }

        void Generate() {
            if (!m_computeShader) {
                return;
            }

            uint32_t trianglesCount = 0;
            m_computeShader->GetPipeline()->UpdateSSBO(SSBO, &trianglesCount, sizeof(uint32_t));

            if (m_computeShader->BeginCompute()) {
                m_computeShader->GetShader()->BindSSBO("triangles", SSBO);
                m_computeShader->Dispatch(4, 1, 1);
                m_computeShader->EndCompute();
            }

            DebugReadSSBO();
        }

        void DebugReadSSBO() {
            if (SSBO == SR_ID_INVALID) {
                return;
            }

            void* pData = nullptr;
            if (!m_computeShader->GetPipeline()->MapSSBO(SSBO, &pData)) {
                return;
            }

            uint32_t trianglesCount = *reinterpret_cast<uint32_t*>(pData);
            Detail::Triangle* triangles = reinterpret_cast<Detail::Triangle*>(reinterpret_cast<uint8_t*>(pData) + sizeof(uint32_t) + 12);

            for (uint32_t i = 0; i < trianglesCount; ++i) {
                const Detail::Triangle& triangle = triangles[i];

                SR_DEBUG_LOG("Triangle: A({:.2f}, {:.2f}, {:.2f}), B({:.2f}, {:.2f}, {:.2f}), C({:.2f}, {:.2f}, {:.2f})",
                     triangle.vertexA.position.x, triangle.vertexA.position.y, triangle.vertexA.position.z,
                     triangle.vertexB.position.x, triangle.vertexB.position.y, triangle.vertexB.position.z,
                     triangle.vertexC.position.x, triangle.vertexC.position.y, triangle.vertexC.position.z);
            }

            m_computeShader->GetPipeline()->UnMapSSBO(SSBO);
        }

        void Update(float_t dt) override {
        }

        void Finalize() {
            if (SSBO != SR_ID_INVALID) {
                m_computeShader->GetPipeline()->FreeSSBO(&SSBO);
            }

            m_computeShader = nullptr;
        }

    private:
        SR_GTYPES_NS::ComputeShader::Ptr m_computeShader = nullptr;
        int32_t SSBO = SR_ID_INVALID;

        /// @property
        SR_UTILS_NS::Path shaderPath = "Samples/MarchingCubes/MarchingCubes.srsl";
        /// @property @onChanged(DebugReadSSBO)
        bool debugReadSSBO = false;

    };
}

#include <Codegen/MarchingCubes.generated.hpp>