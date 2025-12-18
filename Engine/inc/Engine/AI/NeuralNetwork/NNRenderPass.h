//
// Created by Monika on 05.01.2025.
//

#ifndef SR_ENGINE_AI_NN_RENDER_PASS_H
#define SR_ENGINE_AI_NN_RENDER_PASS_H

#include <Engine/AI/NeuralNetwork/NNModel.h>

#include <Graphics/Pass/BasePass.h>
#include <Graphics/Memory/SSBO.h>
#include <Graphics/Types/Shader.h>

namespace SpaRcle::AI {
    class NNRenderPass : public SR_GRAPH_NS::BasePass {
        SR_CLASS()
        using Super = SR_GRAPH_NS::BasePass;
    private:
        struct alignas(16) NeuronRenderData {
            alignas(16) SR_MATH_NS::FVector3 position;
            alignas(16) SR_MATH_NS::FColor color;
        };

        struct alignas(16) SynapseRenderData {
            alignas(16) SR_MATH_NS::FVector3 from;
            alignas(16) SR_MATH_NS::FVector3 to;
            alignas(16) SR_MATH_NS::FColor startColor;
            alignas(16) SR_MATH_NS::FColor endColor;
        };

        struct NNInstance {
            bool isDirty = true;
            int32_t neuronsDescriptorSet = SR_ID_INVALID;
            int32_t synapsesDescriptorSet = SR_ID_INVALID;
            SR_GRAPH_NS::SSBOInstance::Ptr pNeuronsSSBO;
            SR_GRAPH_NS::SSBOInstance::Ptr pSynapsesSSBO;
            SpaRcle::AI::NeuralNetwork::Ptr pNetwork;
        };

    public:
        void Register(SpaRcle::AI::NeuralNetwork::Ptr pNetwork);

        bool Prepare() override;
        bool Render() override;
        void Update() override;

        bool Init() override;
        void DeInit() override;

    private:
        void Draw(bool isNeurons);
        void UpdateInstanceData(NNInstance* pInstance);

    private:
        /// @property
        /// @customArgs(pick: enabled, filter name: Shader, relative: resources)
        /// @customArg(filter value: srsl)
        SR_UTILS_NS::Path m_neuronShaderPath;
        /// @property
        /// @customArgs(pick: enabled, filter name: Shader, relative: resources)
        /// @customArg(filter value: srsl)
        SR_UTILS_NS::Path m_synapseShaderPath;

        SR_GTYPES_NS::Shader::Ptr m_neuronShader;
        SR_GTYPES_NS::Shader::Ptr m_synapseShader;

        SR_HTYPES_NS::FastMemoryArray<NeuronRenderData> m_neuronRenderDataCache;
        SR_HTYPES_NS::FastMemoryArray<SynapseRenderData> m_synapseRenderDataCache;

        std::vector<NNInstance*> m_instances;

    };
}

#endif //SR_ENGINE_AI_NN_RENDER_PASS_H
