//
// Created by Monika on 08.11.2025.
//

#include <Engine/AI/NeuralNetwork/NNRenderPass.h>

#include <Graphics/Types/Camera.h>

#include <Utils/Math/Vector4.h>

#include <Codegen/NNRenderPass.generated.hpp>

namespace SpaRcle::AI {
    bool NNRenderPass::Init() {
        NeuralNetwork::Ptr pTestNetwork = NeuralNetwork::GenerateNetwork(100, 64, { 225, 144, 100 }, 10.0f);
        Register(pTestNetwork);

        m_neuronShader = SR_GTYPES_NS::Shader::Load(m_neuronShaderPath);
        if (m_neuronShader) {
            m_neuronShader->AddUsePoint();
        }
        else {
            SR_ERROR("NNRenderPass::Init() : failed to load neuron shader: ", m_neuronShaderPath);
        }

        m_synapseShader = SR_GTYPES_NS::Shader::Load(m_synapseShaderPath);
        if (m_synapseShader) {
            m_synapseShader->AddUsePoint();
        }
        else {
            SR_ERROR("NNRenderPass::Init() : failed to load synapse shader: {}", m_synapseShaderPath);
        }

        return Super::Init();
    }

    void NNRenderPass::DeInit() {
        for (auto&& pInstance : m_instances) {
            if (pInstance->neuronsDescriptorSet != SR_ID_INVALID) {
                SR_GRAPH_NS::DescriptorManager::Instance().FreeDescriptorSet(&pInstance->neuronsDescriptorSet);
                pInstance->neuronsDescriptorSet = SR_ID_INVALID;
            }
            if (pInstance->synapsesDescriptorSet != SR_ID_INVALID) {
                SR_GRAPH_NS::DescriptorManager::Instance().FreeDescriptorSet(&pInstance->synapsesDescriptorSet);
                pInstance->synapsesDescriptorSet = SR_ID_INVALID;
            }
            delete pInstance;
        }
        m_instances.clear();

        if (m_neuronShader) {
            m_neuronShader->RemoveUsePoint();
            m_neuronShader = nullptr;
        }

        if (m_synapseShader) {
            m_synapseShader->RemoveUsePoint();
            m_synapseShader = nullptr;
        }

        Super::DeInit();
    }

    void NNRenderPass::Prepare() {
        SR_TRACY_ZONE;

        for (auto pIt = m_instances.begin(); pIt != m_instances.end(); ) {
            auto&& pInstance = *pIt;

            if (!pInstance->pNetwork) {
                delete *pIt;
                pIt = m_instances.erase(pIt);
                GetPipeline()->SetDirty(true);
                continue;
            }

            if (pInstance->isDirty) {
                UpdateInstanceData(pInstance);
                pInstance->isDirty = false;
            }

            ++pIt;
        }

        Super::Prepare();
    }

    void NNRenderPass::Draw(bool isNeurons) {
        auto&& pShader = isNeurons ? m_neuronShader : m_synapseShader;

        if (pShader && pShader->Use() != SR_GRAPH_NS::ShaderBindResult::Failed) {
            for (auto&& pInstance: m_instances) {
                int32_t& descriptor = isNeurons ? pInstance->neuronsDescriptorSet : pInstance->synapsesDescriptorSet;
                (isNeurons ? pInstance->pNeuronsSSBO : pInstance->pSynapsesSSBO)->Bind();

                if (descriptor == SR_ID_INVALID) {
                    descriptor = SR_GRAPH_NS::DescriptorManager::Instance().AllocateDescriptorSet(SR_ID_INVALID);
                }

                if (descriptor != SR_ID_INVALID) {
                    SR_GRAPH_NS::DescriptorManager::Instance().Bind(descriptor);
                    pShader->AttachDescriptorSets();
                }

                GetPipeline()->SetDrawInstancesCount(isNeurons ? pInstance->pNetwork->GetNeuronsCount() : pInstance->pNetwork->GetSynapsesCount());
                GetPipeline()->Draw(isNeurons ? 1 : 2);
                GetPipeline()->ResetDrawInstancesCount();
            }
            pShader->UnUse();
        }
    }

    bool NNRenderPass::Render() {
        SR_TRACY_ZONE;
        Draw(true);
        Draw(false);
        return true;
    }

    void NNRenderPass::Update() {
        if (!GetCamera()) {
            return;
        }

        if (m_neuronShader && m_neuronShader->BeginSharedUBO()) {
            m_neuronShader->SetMat4(SR_GRAPH_NS::SHADER_VIEW_MATRIX, GetCamera()->GetViewTranslate());
            m_neuronShader->SetMat4(SR_GRAPH_NS::SHADER_PROJECTION_MATRIX, GetCamera()->GetProjection());
            m_neuronShader->EndSharedUBO();
        }

        if (m_synapseShader && m_synapseShader->BeginSharedUBO()) {
            m_synapseShader->SetMat4(SR_GRAPH_NS::SHADER_VIEW_MATRIX, GetCamera()->GetViewTranslate());
            m_synapseShader->SetMat4(SR_GRAPH_NS::SHADER_PROJECTION_MATRIX, GetCamera()->GetProjection());
            m_synapseShader->EndSharedUBO();
        }

        Super::Update();
    }

    void NNRenderPass::Register(SpaRcle::AI::NeuralNetwork::Ptr pNetwork) {
        auto&& pInstance = m_instances.emplace_back(new NNInstance());

        pInstance->pNeuronsSSBO = SR_GRAPH_NS::SSBOInstance::Create<NeuronRenderData>(pNetwork->GetNeuronsCount(), SR_GRAPH_NS::SSBOUsage::CPUToGPU, "neurons", SR_GRAPH_NS::SSBOFlags::StructuredCounter);
        pInstance->pSynapsesSSBO = SR_GRAPH_NS::SSBOInstance::Create<SynapseRenderData>(pNetwork->GetSynapsesCount(), SR_GRAPH_NS::SSBOUsage::CPUToGPU, "synapses", SR_GRAPH_NS::SSBOFlags::StructuredCounter);

        pInstance->pNetwork = std::move(pNetwork);

        GetPipeline()->SetDirty(true);
    }

    void NNRenderPass::UpdateInstanceData(NNInstance* pInstance) {
        const uint64_t neuronsCount = pInstance->pNetwork->GetNeuronsCount();
        m_neuronRenderDataCache.clear();
        m_neuronRenderDataCache.reserve(neuronsCount);

        const uint64_t synapsesCount = pInstance->pNetwork->GetSynapsesCount();
        m_synapseRenderDataCache.clear();
        m_synapseRenderDataCache.reserve(synapsesCount);

        if (neuronsCount > uint64_t(pInstance->pNeuronsSSBO->GetCapacity() / sizeof(NeuronRenderData))) {
            pInstance->pNeuronsSSBO->Resize(neuronsCount * sizeof(NeuronRenderData));
            GetPipeline()->SetDirty(true);
        }

        if (synapsesCount > uint64_t(pInstance->pSynapsesSSBO->GetCapacity() / sizeof(SynapseRenderData))) {
            pInstance->pSynapsesSSBO->Resize(synapsesCount * sizeof(SynapseRenderData));
            GetPipeline()->SetDirty(true);
        }

        pInstance->pNetwork->ForEachNeuron([&](auto id, Neuron& neuron) {
            NeuronRenderData renderData;
            renderData.position = neuron.position + SR_MATH_NS::FVector3(40.0f, 0.0f, 0.0f);
            renderData.color = SR_MATH_NS::FColor::RGBFromHash(std::hash<SR_MATH_NS::FVector3>()(renderData.position)) / 255.f;
            m_neuronRenderDataCache.emplace_back(renderData);

            for (auto& [toId, synapse] : neuron.outputSynapses) {
                const auto& toNeuron = pInstance->pNetwork->GetNeuron(toId);
                SynapseRenderData synapseData;
                synapseData.from = neuron.position + SR_MATH_NS::FVector3(40.0f, 0.0f, 0.0f);
                synapseData.to = toNeuron.position + SR_MATH_NS::FVector3(40.0f, 0.0f, 0.0f);
                synapseData.startColor = SR_MATH_NS::FColor::RGBFromHash(std::hash<SR_MATH_NS::FVector3>()(synapseData.to)) / 255.f;
                synapseData.endColor = SR_MATH_NS::FColor::RGBFromHash(std::hash<SR_MATH_NS::FVector3>()(synapseData.from)) / 255.f;
                m_synapseRenderDataCache.emplace_back(synapseData);
            }
        });

        if (auto&& pData = pInstance->pNeuronsSSBO->MapData()) {
            std::memcpy(pData, m_neuronRenderDataCache.data(), neuronsCount * sizeof(NeuronRenderData));
            pInstance->pNeuronsSSBO->ResetCounter(neuronsCount);
            pInstance->pNeuronsSSBO->Flush();
            pInstance->pNeuronsSSBO->UnMap();
        }

        if (auto&& pData = pInstance->pSynapsesSSBO->MapData()) {
            std::memcpy(pData, m_synapseRenderDataCache.data(), synapsesCount * sizeof(SynapseRenderData));
            pInstance->pSynapsesSSBO->ResetCounter(synapsesCount);
            pInstance->pSynapsesSSBO->Flush();
            pInstance->pSynapsesSSBO->UnMap();
        }
    }
}
