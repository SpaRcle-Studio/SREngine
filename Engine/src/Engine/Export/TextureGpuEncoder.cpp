//
// Created by OpenAI Codex on 22.11.2026.
//

#include <Engine/Export/TextureGpuEncoder.h>

#include <Utils/Profile/TracyContext.h>

#ifdef SR_TEXTURE_OPENCL
    #define CL_TARGET_OPENCL_VERSION 120
    #include <CL/cl.h>
    #include <TextureComputeSources.h>
#endif

namespace SR_CORE_NS {
    struct TextureGpuEncoder::State {
        SR_UTILS_NS::String identity = "cpu";
        bool reportedBackend = false;
    #ifdef SR_TEXTURE_OPENCL
        static constexpr uint32_t TileBlocks = 128;
        static constexpr uint32_t TilePixels = TileBlocks * 4;
        struct SourceInfo {
            uint32_t width;
            uint32_t height;
            uint32_t columns;
            uint32_t rows;
            float_t quality;
        };
        static_assert(sizeof(SourceInfo) == 20);
        struct Tile {
            SR_UTILS_NS::Vector<uint8_t> pixels;
            SR_UTILS_NS::Vector<uint8_t> encoded;
            SourceInfo info{};
            uint32_t startX = 0;
            uint32_t startY = 0;
            cl_event ready = nullptr;
            cl_event kernel = nullptr;
        } tiles[2];
        cl_device_id device = nullptr;
        cl_context context = nullptr;
        cl_command_queue queue = nullptr;
        cl_mem input = nullptr;
        cl_mem output = nullptr;
        cl_mem info = nullptr;
        cl_mem options = nullptr;
        struct Codec {
            cl_program program = nullptr;
            cl_kernel encoder = nullptr;
            cl_kernel initialize = nullptr;
            bool attempted = false;
        } codecs[8];
        bool attempted = false;

        bool Initialize() {
            if (attempted) {
                return context && queue && input && output && info && options;
            }
            attempted = true;
            cl_uint count = 0;
            if (clGetPlatformIDs(0, nullptr, &count) != CL_SUCCESS || count == 0) {
                SR_INFO("TextureGpuEncoder::State::Initialize() : OpenCL platforms unavailable; using CPU");
                return false;
            }
            SR_UTILS_NS::Vector<cl_platform_id> platforms(count);
            if (clGetPlatformIDs(count, platforms.data(), nullptr) != CL_SUCCESS) {
                return false;
            }
            for (const auto platform : platforms) {
                if (clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, 1, &device, nullptr) == CL_SUCCESS) {
                    break;
                }
                device = nullptr;
            }
            if (!device) {
                SR_INFO("TextureGpuEncoder::State::Initialize() : OpenCL GPU unavailable; using CPU");
                return false;
            }
            cl_int error = CL_SUCCESS;
            context = clCreateContext(nullptr, 1, &device, nullptr, nullptr, &error);
            if (error != CL_SUCCESS || !context) {
                return false;
            }
            queue = clCreateCommandQueue(context, device, CL_QUEUE_PROFILING_ENABLE, &error);
            if (error != CL_SUCCESS || !queue) {
                return false;
            }
            input = clCreateBuffer(context, CL_MEM_READ_ONLY, TilePixels * TilePixels * 4, nullptr, &error);
            if (error != CL_SUCCESS) {
                return false;
            }
            output = clCreateBuffer(context, CL_MEM_WRITE_ONLY, TilePixels * TilePixels, nullptr, &error);
            if (error != CL_SUCCESS) {
                return false;
            }
            info = clCreateBuffer(context, CL_MEM_READ_ONLY, 20, nullptr, &error);
            if (error != CL_SUCCESS) {
                return false;
            }
            options = clCreateBuffer(context, CL_MEM_READ_WRITE, 1024, nullptr, &error);
            if (error != CL_SUCCESS) {
                return false;
            }
            char name[256]{};
            char driver[256]{};
            clGetDeviceInfo(device, CL_DEVICE_NAME, sizeof(name) - 1, name, nullptr);
            clGetDeviceInfo(device, CL_DRIVER_VERSION, sizeof(driver) - 1, driver, nullptr);
            identity = "opencl:{}:{}"_format(name, driver);
            SR_INFO("TextureGpuEncoder::State::Initialize() : {}", identity);
            return true;
        }

        Codec* GetCodec(uint32_t index) {
            if (!Initialize() || index == 0 || index > 7 || index == 6) {
                return nullptr;
            }
            auto&& codec = codecs[index];
            if (codec.attempted) {
                return codec.encoder && codec.initialize ? &codec : nullptr;
            }
            codec.attempted = true;
            SR_UTILS_NS::Vector<const char*> sources;
            TextureComputeSources::Get(index, sources);
            if (sources.empty()) {
                return nullptr;
            }
            cl_int error = CL_SUCCESS;
            codec.program = clCreateProgramWithSource(context, static_cast<cl_uint>(sources.size()), sources.data(), nullptr, &error);
            if (!codec.program || error != CL_SUCCESS) {
                return nullptr;
            }
            // common_def.h selects OpenCL from __OPENCL_VERSION__; _WIN32 prevents
            // the vendor header from subsequently switching back to its CPU branch.
            const auto compilationStarted = std::chrono::steady_clock::now();
            error = clBuildProgram(codec.program, 1, &device, "-cl-std=CL1.2 -D_WIN32=1", nullptr, nullptr);
            if (error != CL_SUCCESS) {
                char log[4096]{};
                clGetProgramBuildInfo(codec.program, device, CL_PROGRAM_BUILD_LOG, sizeof(log) - 1, log, nullptr);
                SR_WARN("TextureGpuEncoder::State::GetCodec() : OpenCL codec {} failed; using CPU. {}", index, log);
                return nullptr;
            }
            const auto compilationMilliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - compilationStarted).count();
            SR_INFO("TextureGpuEncoder::State::GetCodec() : compiled OpenCL codec {} in {} ms", index, compilationMilliseconds);
            codec.encoder = clCreateKernel(codec.program, "CMP_GPUEncoder", &error);
            if (!codec.encoder || error != CL_SUCCESS) {
                return nullptr;
            }
            codec.initialize = clCreateKernel(codec.program, "SRInitialize", &error);
            if (!codec.initialize || error != CL_SUCCESS) {
                clReleaseKernel(codec.encoder);
                codec.encoder = nullptr;
                return nullptr;
            }
            return &codec;
        }

        ~State() {
            if (queue) {
                clFinish(queue);
            }
            for (auto&& codec : codecs) {
                if (codec.encoder) {
                    clReleaseKernel(codec.encoder);
                }
                if (codec.initialize) {
                    clReleaseKernel(codec.initialize);
                }
                if (codec.program) {
                    clReleaseProgram(codec.program);
                }
            }
            for (const auto memory : { input, output, info, options }) {
                if (memory) {
                    clReleaseMemObject(memory);
                }
            }
            if (queue) {
                clReleaseCommandQueue(queue);
            }
            if (context) {
                clReleaseContext(context);
            }
        }
    #endif
    };

    TextureGpuEncoder::TextureGpuEncoder()
        : m_pState(new State())
    { }

    TextureGpuEncoder::~TextureGpuEncoder() {
        delete m_pState;
    }

    SR_UTILS_NS::String TextureGpuEncoder::GetIdentity() const {
    #ifdef SR_TEXTURE_OPENCL
        m_pState->Initialize();
    #else
        if (!m_pState->reportedBackend) {
            SR_INFO("TextureGpuEncoder::GetIdentity() : OpenCL backend disabled at build time; using CPU");
            m_pState->reportedBackend = true;
        }
    #endif
        return m_pState->identity;
    }

    bool TextureGpuEncoder::Encode(uint32_t width, uint32_t height, const SR_UTILS_NS::Vector<float_t>& rgba,
        SR_GRAPH_NS::TextureCompression compression, float_t quality, float_t cutoff, SR_UTILS_NS::Vector<uint8_t>& output,
        const SR_HTYPES_NS::Function<bool()>& cancelled, const SR_HTYPES_NS::Function<void(float_t)>& progress) {
        SR_TRACY_ZONE;
    #ifndef SR_TEXTURE_OPENCL
        return false;
    #else
        const uint32_t index = static_cast<uint32_t>(compression);
        auto&& pCodec = m_pState->GetCodec(index);
        if (!pCodec || width == 0 || height == 0 || rgba.size() != uint64_t(width) * height * 4) {
            return false;
        }
        auto&& state = *m_pState;
        const uint32_t columns = (width + 3) / 4;
        const uint32_t rows = (height + 3) / 4;
        const uint32_t blockBytes = compression == SR_GRAPH_NS::TextureCompression::BC1 || compression == SR_GRAPH_NS::TextureCompression::BC4 ? 8 : 16;
        output.resize(uint64_t(columns) * rows * blockBytes);
        cl_int error = clSetKernelArg(pCodec->initialize, 0, sizeof(state.options), &state.options);
        error |= clSetKernelArg(pCodec->initialize, 1, sizeof(quality), &quality);
        const uint32_t threshold = static_cast<uint32_t>(std::clamp(cutoff, 0.f, 1.f) * 255.f + 0.5f);
        error |= clSetKernelArg(pCodec->initialize, 2, sizeof(threshold), &threshold);
        const size_t one = 1;
        error |= clEnqueueNDRangeKernel(state.queue, pCodec->initialize, 1, nullptr, &one, nullptr, 0, nullptr, nullptr);
        cl_mem arguments[] { state.input, state.output, state.info, state.options };
        for (uint32_t argument = 0; argument < 4; ++argument) {
            error |= clSetKernelArg(pCodec->encoder, argument, sizeof(cl_mem), &arguments[argument]);
        }
        if (error != CL_SUCCESS) {
            return false;
        }
        const auto encodingStarted = std::chrono::steady_clock::now();
        uint64_t completedBlocks = 0;
        cl_ulong kernelNanoseconds = 0;
        uint32_t nextTile = 0;
        auto cleanup = [&]() {
            clFinish(state.queue);
            for (auto&& tile : state.tiles) {
                if (tile.ready) {
                    clReleaseEvent(tile.ready);
                    tile.ready = nullptr;
                }
                if (tile.kernel) {
                    clReleaseEvent(tile.kernel);
                    tile.kernel = nullptr;
                }
            }
        };
        auto complete = [&](State::Tile& tile) {
            if (!tile.ready) {
                return true;
            }
            if (clWaitForEvents(1, &tile.ready) != CL_SUCCESS) {
                return false;
            }
            cl_ulong started = 0;
            cl_ulong finished = 0;
            if (clGetEventProfilingInfo(tile.kernel, CL_PROFILING_COMMAND_START, sizeof(started), &started, nullptr) == CL_SUCCESS
                && clGetEventProfilingInfo(tile.kernel, CL_PROFILING_COMMAND_END, sizeof(finished), &finished, nullptr) == CL_SUCCESS) {
                kernelNanoseconds += finished - started;
            }
            clReleaseEvent(tile.ready);
            tile.ready = nullptr;
            clReleaseEvent(tile.kernel);
            tile.kernel = nullptr;
            for (uint32_t row = 0; row < tile.info.rows; ++row) {
                memcpy(output.data() + (uint64_t(tile.startY + row) * columns + tile.startX) * blockBytes,
                    tile.encoded.data() + uint64_t(row) * tile.info.columns * blockBytes, tile.info.columns * blockBytes);
            }
            completedBlocks += uint64_t(tile.info.columns) * tile.info.rows;
            if (progress) {
                progress(static_cast<float_t>(completedBlocks) / static_cast<float_t>(uint64_t(columns) * rows));
            }
            return true;
        };
        for (uint32_t startY = 0; startY < rows; startY += State::TileBlocks) {
            for (uint32_t startX = 0; startX < columns; startX += State::TileBlocks) {
                if (cancelled && cancelled()) {
                    cleanup();
                    return false;
                }
                auto&& tile = state.tiles[nextTile];
                if (!complete(tile)) {
                    cleanup();
                    SR_WARN("TextureGpuEncoder::Encode() : OpenCL completion failed; retrying on CPU");
                    return false;
                }
                auto&& pixels = tile.pixels;
                auto&& encoded = tile.encoded;
                pixels.resize(State::TilePixels * State::TilePixels * 4);
                encoded.resize(State::TilePixels * State::TilePixels);
                const uint32_t tileColumns = std::min(State::TileBlocks, columns - startX);
                const uint32_t tileRows = std::min(State::TileBlocks, rows - startY);
                const uint32_t tileWidth = tileColumns * 4;
                const uint32_t tileHeight = tileRows * 4;
                for (uint32_t y = 0; y < tileHeight; ++y) {
                    for (uint32_t x = 0; x < tileWidth; ++x) {
                        const uint64_t source = (uint64_t(std::min(startY * 4 + y, height - 1)) * width + std::min(startX * 4 + x, width - 1)) * 4;
                        const uint64_t destination = (uint64_t(y) * tileWidth + x) * 4;
                        for (uint32_t channel = 0; channel < 4; ++channel) {
                            pixels[destination + channel] = static_cast<uint8_t>(std::clamp(rgba[source + channel], 0.f, 1.f) * 255.f + 0.5f);
                        }
                    }
                }
                tile.info = { tileWidth, tileHeight, tileColumns, tileRows, quality };
                tile.startX = startX;
                tile.startY = startY;
                // Device buffers are reused in queue order; host buffers stay alive until
                // their read event completes, allowing CPU preparation of the next tile.
                error = clEnqueueWriteBuffer(state.queue, state.input, CL_FALSE, 0, tileWidth * tileHeight * 4, pixels.data(), 0, nullptr, nullptr);
                error |= clEnqueueWriteBuffer(state.queue, state.info, CL_FALSE, 0, sizeof(tile.info), &tile.info, 0, nullptr, nullptr);
                const size_t work[] { tileColumns, tileRows };
                error |= clEnqueueNDRangeKernel(state.queue, pCodec->encoder, 2, nullptr, work, nullptr, 0, nullptr, &tile.kernel);
                if (error != CL_SUCCESS) {
                    cleanup();
                    SR_WARN("TextureGpuEncoder::Encode() : OpenCL dispatch failed ({}); retrying on CPU", error);
                    return false;
                }
                error = clEnqueueReadBuffer(state.queue, state.output, CL_FALSE, 0, tileColumns * tileRows * blockBytes, encoded.data(), 0, nullptr, &tile.ready);
                if (error == CL_SUCCESS) {
                    error = clFlush(state.queue);
                }
                if (error != CL_SUCCESS) {
                    cleanup();
                    SR_WARN("TextureGpuEncoder::Encode() : OpenCL readback failed ({}); retrying on CPU", error);
                    return false;
                }
                nextTile = (nextTile + 1) % 2;
            }
        }
        for (uint32_t pending = 0; pending < 2; ++pending) {
            if ((cancelled && cancelled()) || !complete(state.tiles[(nextTile + pending) % 2])) {
                cleanup();
                return false;
            }
        }
        const auto encodingMilliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - encodingStarted).count();
        SR_INFO("TextureGpuEncoder::Encode() : {}x{}, BC{}, GPU kernels {} ms, encode wall {} ms, tile {}x{}, 2 host buffers",
            width, height, index, kernelNanoseconds / 1000000, encodingMilliseconds, State::TilePixels, State::TilePixels);
        return true;
    #endif
    }
}
