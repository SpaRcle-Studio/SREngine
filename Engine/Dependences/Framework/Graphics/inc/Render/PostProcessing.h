//
// Created by Nikita on 19.11.2020.
//

#ifndef GAMEENGINE_POSTPROCESSING_H
#define GAMEENGINE_POSTPROCESSING_H

#include "Shader.h"
#include <Environment/Environment.h>
#include <Debug.h>

namespace Framework::Graphics {
    class Render;
    class Camera;

    /*
     How use? (OpenGL)

     void Draw() {
        ...clear buffers

        postProcessing->Begin();

        ...draw geometry

        postProcessing->End();

        ...swapBuffers
     */

    // TODO: add freeing video buffers!
    class PostProcessing {
    private:
        ~PostProcessing() = default;
    public:
        PostProcessing(const PostProcessing&) = delete;
        PostProcessing(Camera* camera, unsigned char countHDRBuffers);
    private:
        float			      m_gamma                 = 0.8f;
        float                 m_exposure              = 1.f;
        float                 m_saturation            = 1.f;
        glm::vec3		      m_color_correction      = { 1, 1, 1 };
        glm::vec3		      m_bloomColor            = { 1, 1, 1 };
        float                 m_bloomIntensity        = 1.f;
        volatile uint8_t      m_bloomAmount           = 6;
    private:
        bool                  m_debugDisplayBloomMask = false;

        volatile bool         m_bloom                 = true;
        bool                  m_bloomClear            = false;
    private:
        bool                  m_horizontal            = false;
        bool                  m_firstIteration        = false;

        uint32_t              m_VAO                   = 0;
        uint32_t              m_VBO                   = 0;

        uint32_t              m_skyboxRBO             = 0;
        uint32_t              m_skyboxFBO             = 0;
        uint32_t              m_skyboxColorBuffer     = 0;

        uint32_t              m_finalRBO              = 0;
        uint32_t              m_finalFBO              = 0;
        uint32_t              m_finalColorBuffer      = 0;

        uint32_t              m_RBODepth              = 0;
        uint32_t              m_HDRFrameBufferObject  = 0;
        std::vector<uint32_t> m_ColorBuffers          = { 0, 0, 0, 0 };
        uint8_t               m_countColorBuffers     = 4;
        /*
             1 - color
             2 - bloom
             3 - depth
             4 - stencil
         */

        std::vector<uint32_t> m_PingPongFrameBuffers  = { 0, 0 };
        std::vector<uint32_t> m_PingPongColorBuffers  = { 0, 0 };
    private:
        Environment*          m_env                   = nullptr;

        Shader*               m_postProcessingShader  = nullptr;
        Shader*               m_blurShader            = nullptr;

        Camera*               m_camera                = nullptr;
        Render*               m_render                = nullptr;
        bool                  m_isInit                = false;
    private:
        void BlurBloom();
    public:
        [[nodiscard]] SR_FORCE_INLINE glm::vec3 GetColorCorrection() const noexcept { return m_color_correction;    }
        [[nodiscard]] SR_FORCE_INLINE glm::vec3 GetBloomColor()      const noexcept { return m_bloomColor;          }

        [[nodiscard]] SR_FORCE_INLINE float GetGamma()               const noexcept { return m_gamma;               }
        [[nodiscard]] SR_FORCE_INLINE float GetExposure()            const noexcept { return m_exposure;            }
        [[nodiscard]] SR_FORCE_INLINE float GetSaturation()          const noexcept { return m_saturation;          }
        [[nodiscard]] SR_FORCE_INLINE unsigned char GetBloomAmount() const noexcept { return m_bloomAmount;         }
        [[nodiscard]] SR_FORCE_INLINE float GetBloomIntensity()      const noexcept { return m_bloomIntensity;      }
        [[nodiscard]] SR_FORCE_INLINE bool GetBloomEnabled()         const noexcept { return this->m_bloom;         }
    public:
        SR_FORCE_INLINE void SetColorCorrection(glm::vec3 value)     noexcept { m_color_correction     = value;     }
        SR_FORCE_INLINE void SetBloomColor(glm::vec3 value)          noexcept { m_bloomColor           = value;     }
        SR_FORCE_INLINE void SetGamma(float gamma)                   noexcept { m_gamma                = gamma;     }
        SR_FORCE_INLINE void SetSaturation(float gamma)              noexcept { m_saturation           = gamma;     }
        SR_FORCE_INLINE void SetExposure(float exposure)             noexcept { m_exposure             = exposure;  }
        SR_FORCE_INLINE void SetBloomAmount(unsigned int amount)     noexcept { this->m_bloomAmount    = amount;    }
        SR_FORCE_INLINE void SetBloomIntensity(float intensity)      noexcept { this->m_bloomIntensity = intensity; }

        SR_FORCE_INLINE void SetBloom(bool v)                        noexcept { this->m_bloom = v;                  }
        SR_FORCE_INLINE void SetDisplayBloomMask(bool value)         noexcept { m_debugDisplayBloomMask = value;    }
    public:
        /** \brief Init shader and set default values \warning Call only from window context \return bool */
        bool Init(Render* render);
        bool Destroy();

        SR_FORCE_INLINE bool Free() noexcept {
            Helper::Debug::Graph("PostProcessing::Free() : free post processing pointer...");
            delete this;
            return true;
        }

        bool ReCalcFrameBuffers(int w, int h);

        void BeginSkybox();
        void EndSkybox();

        bool Begin();
        bool End();

        [[nodiscard]] SR_FORCE_INLINE unsigned int GetFinally()       const noexcept { return this->m_finalColorBuffer;  }
        [[nodiscard]] SR_FORCE_INLINE unsigned int GetColoredImage()  const noexcept { return this->m_ColorBuffers[0];   }
        [[nodiscard]] SR_FORCE_INLINE unsigned int GetBloomMask()     const noexcept { return this->m_ColorBuffers[1];   }
        [[nodiscard]] SR_FORCE_INLINE unsigned int GetDepthBuffer()   const noexcept { return this->m_ColorBuffers[2];   }
        [[nodiscard]] SR_FORCE_INLINE unsigned int GetBlurBloomMask() const noexcept { return m_PingPongColorBuffers[0]; }
        [[nodiscard]] SR_FORCE_INLINE unsigned int GetSkyboxColor()   const noexcept { return m_skyboxColorBuffer;       }
        [[nodiscard]] SR_FORCE_INLINE unsigned int GetStencilBuffer() const noexcept { return m_ColorBuffers[3];         }

        [[nodiscard]] SR_FORCE_INLINE unsigned int GetHDR_FBO()       const noexcept { return m_HDRFrameBufferObject;    }

        [[nodiscard]] SR_FORCE_INLINE unsigned int GetCustomColorBuffer(unsigned char id) const noexcept {
            if (m_countColorBuffers <= id) {
                Helper::Debug::Error("PostProcessing::GetCustomColorBuffer(): index error!");
            }
            else
                return m_ColorBuffers[id];
        }
    };
}

#endif //GAMEENGINE_POSTPROCESSING_H
