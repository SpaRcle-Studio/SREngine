//
// Created by Nikita on 12.06.2021.
//

#ifndef GAMEENGINE_VULKANPOSTPROCESSING_H
#define GAMEENGINE_VULKANPOSTPROCESSING_H

#include <Render/PostProcessing.h>

namespace Framework::Graphics {
    class VulkanPostProcessing : public PostProcessing {
    private:
        ~VulkanPostProcessing() override = default;
    public:
        VulkanPostProcessing(Camera *camera) : PostProcessing(camera) {}
    public:
        bool BeginGeometry() override {
            if (m_frameBuffer >= 0) {
                m_env->BindFrameBuffer(m_frameBuffer);
                m_env->ClearBuffers();
                return true;
            } else {
                Helper::Debug::Error("VulkanPostProcessing::BeginGeometry() : frame buffer is not calculated!");
                return false;
            }
        }
        void EndGeometry() override {
            m_env->BindFrameBuffer(0);
        }

        void BeginSkybox() override {}
        void EndSkybox() override {}

        void Complete() override {
            m_postProcessingShader->Use();

            if (m_descriptorSet == -1) {
                m_descriptorSet = m_env->AllocDescriptorSet({DescriptorType::Uniform});

                if (m_ubo == -1)
                    m_ubo = m_env->AllocateUBO(sizeof(PostProcessingUBO));

                this->m_env->UpdateDescriptorSets(m_descriptorSet, {
                        { DescriptorType::Uniform, { 0, m_ubo } },
                });

                PostProcessingUBO ubo = { 1.f, 1.f }; m_env->UpdateUBO(m_ubo, &ubo, sizeof(PostProcessingUBO));

                m_env->BindDescriptorSet(m_descriptorSet);
                //this->m_env->SetDescriptorID(m_descriptorSet);
                /*
                 *  0 - post processing uniform
                 *  1 - geometry sampler
                 *  2 - skybox sampler
                 */
                this->m_env->BindTexture(1, 0);
            }

            m_env->BindDescriptorSet(m_descriptorSet);

            m_env->Draw(3);

            m_env->UnUseShader();
        }
    public:
        bool Free() override {
            Helper::Debug::Graph("VulkanPostProcessing::Free() : free post processing pointer...");
            delete this;
            return true;
        }

        bool Destroy() override {
            if (m_postProcessingShader) {
                m_postProcessingShader->Free();
                m_postProcessingShader = nullptr;
            }

            if (m_descriptorSet != -1) {
                m_env->FreeDescriptorSet(m_descriptorSet);
                m_descriptorSet = -1;
            }

            if (m_ubo != -1) {
                if (!m_env->FreeUBO(m_ubo))
                    Helper::Debug::Warn("VulkanPostProcessing::Destroy() : failed to free UBO!");
                m_ubo = -1;
            }

            return PostProcessing::Destroy();
        }
    };
}

#endif //GAMEENGINE_VULKANPOSTPROCESSING_H
