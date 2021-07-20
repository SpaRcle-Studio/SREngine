//
// Created by Nikita on 19.11.2020.
//

#ifndef GAMEENGINE_POSTPROCESSING_H
#define GAMEENGINE_POSTPROCESSING_H

#include <Render/Shader.h>
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
    protected:
        virtual ~PostProcessing() = default;;
        PostProcessing(Camera* camera);
    public:
        PostProcessing(const PostProcessing&) = delete;
    protected:
        float			      m_gamma                 = 0.8f;
        float                 m_exposure              = 1.f;
        float                 m_saturation            = 1.f;
        glm::vec3		      m_color_correction      = { 1, 1, 1 };
        glm::vec3		      m_bloomColor            = { 1, 1, 1 };
        float                 m_bloomIntensity        = 1.f;
        volatile uint8_t      m_bloomAmount           = 6;
    protected:
        volatile bool         m_bloom                 = true;
        bool                  m_bloomClear            = false;
    protected:
        bool                  m_horizontal            = false;
        bool                  m_firstIteration        = false;

        int32_t               m_finalDepth            = -1;
        int32_t               m_finalFBO              = -1;
        int32_t               m_finalColorBuffer      = -1;

        /*
         *  0 - geometry color
         *  1 - bright color
         *  2 - depth color
         *  3 - stencil mask
         *  4 - skybox color
         */
        std::vector<int32_t>  m_colors                = { -1, -1, -1, -1, -1 };
        int32_t               m_depth                 = -1;
        int32_t               m_frameBuffer           = -1;

        std::vector<int32_t>  m_PingPongFrameBuffers  = { -1, -1 };
        std::vector<int32_t>  m_PingPongColorBuffers  = { -1, -1 };

        int32_t               m_descriptorSet         = -1;
        int32_t               m_ubo                   = -1;
    protected:
        Environment*          m_env                   = nullptr;

        Shader*               m_postProcessingShader  = nullptr;
        Shader*               m_blurShader            = nullptr;

        Camera*               m_camera                = nullptr;
        Render*               m_render                = nullptr;
        bool                  m_isInit                = false;
    public:
        static PostProcessing* Allocate(Camera* camera);
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
    public:
        /** \brief Init shader and set default values \warning Call only from window context \return bool */
        virtual bool Init(Render* render);

        virtual bool Destroy();

        virtual bool Free() = 0;
        virtual bool OnResize(uint32_t w, uint32_t h);

        virtual void BeginSkybox()   = 0;
        virtual void EndSkybox()     = 0;

        virtual bool BeginGeometry() = 0;
        virtual void EndGeometry()   = 0;

        virtual void Complete()      = 0;
    public:
        [[nodiscard]] SR_FORCE_INLINE uint32_t GetFinally()       const noexcept { return this->m_finalColorBuffer;  }
        [[nodiscard]] SR_FORCE_INLINE uint32_t GetColoredImage()  const noexcept { return this->m_colors[0];   }
        [[nodiscard]] SR_FORCE_INLINE uint32_t GetBloomMask()     const noexcept { return this->m_colors[1];   }
        [[nodiscard]] SR_FORCE_INLINE uint32_t GetDepthBuffer()   const noexcept { return this->m_colors[2];   }
        [[nodiscard]] SR_FORCE_INLINE uint32_t GetBlurBloomMask() const noexcept { return m_PingPongColorBuffers[0]; }
        [[nodiscard]] SR_FORCE_INLINE uint32_t GetSkyboxColor()   const noexcept { return m_colors[4];         }
        [[nodiscard]] SR_FORCE_INLINE uint32_t GetStencilBuffer() const noexcept { return m_colors[3];         }
        [[nodiscard]] SR_FORCE_INLINE uint32_t GetCustomColorBuffer(uint8_t id) const noexcept { return m_colors[id]; }
    };
}

#endif //GAMEENGINE_POSTPROCESSING_H
