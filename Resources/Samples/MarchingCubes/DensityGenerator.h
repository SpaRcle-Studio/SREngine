//
// Created by Monika on 06.07.2025.
//

#include <Utils/Input/KeyCodes.h>
#include <Utils/Math/Vector2.h>
#include <Utils/Math/Noise.h>
#include <Utils/Math/VectorRanges.h>

#include <Graphics/Types/Geometry/ProceduralMesh.h>
#include <Graphics/Types/ComputeShader.h>
#include <Graphics/Render/RenderContext.h>
#include <Graphics/Memory/SSBO.h>

namespace SpaRcle::Scripts::Samples {
    SR_ENUM_NS_CLASS_T(MarchingCubesShape, uint32_t,
        Sphere,
        Cube,
        WavySphere,
        PerlinNoise,
        Shader
    );


    std::vector<float_t> GeneratePerlinDensityField(int densityCountAxis, float noiseScale, double seed) {
        SR_TRACY_ZONE;

        const int sizeX = densityCountAxis;
        const int sizeY = densityCountAxis;
        const int sizeZ = densityCountAxis;
        const float voxelSize = 1.0f; // шаг сетки в мире
        const float isoLevel = 0.0f;  // поверхность будет на расстоянии radius от центра

        std::vector<float_t> densities(sizeX * sizeY * sizeZ);

        for (int z = 0; z < sizeZ; ++z) {
            for (int y = 0; y < sizeY; ++y) {
                for (int x = 0; x < sizeX; ++x) {
                    int index = z * sizeY * sizeX + y * sizeX + x;

                    glm::vec3 worldPos = glm::vec3(x, y, z) * voxelSize;

                    const double dx = static_cast<double>(worldPos.x) / noiseScale + seed;
                    const double dy = static_cast<double>(worldPos.y) / noiseScale + seed;
                    const double dz = static_cast<double>(worldPos.z) / noiseScale + seed;

                    // Генерация случайной плотности с использованием шума Перлина
                    float noiseValue = SR_MATH_NS::SNoise(dx, dy, dz);
                    densities[index] = noiseValue - isoLevel; // смещение по isoLevel
                }
            }
        }

        return densities;
    }

    std::vector<float_t> GenerateCubeDensityField(int densityCountAxis, float geometrySize) {
        SR_TRACY_ZONE;

        const int sizeX = densityCountAxis;
        const int sizeY = densityCountAxis;
        const int sizeZ = densityCountAxis;
        const float voxelSize = 1.0f; // шаг сетки в мире
        const float isoLevel = 0.0f;  // поверхность будет на расстоянии radius от центра
        const float cubeSize = 32.0f * geometrySize;  // поверхность будет на расстоянии radius от центра

        std::vector<float_t> densities(sizeX * sizeY * sizeZ);

        // Центр куба
        glm::vec3 center = glm::vec3(sizeX, sizeY, sizeZ) * 0.5f * voxelSize;
        glm::vec3 halfExtents = glm::vec3(cubeSize * 0.5f);

        for (int z = 0; z < sizeZ; ++z) {
            for (int y = 0; y < sizeY; ++y) {
                for (int x = 0; x < sizeX; ++x) {
                    int index = z * sizeY * sizeX + y * sizeX + x;

                    glm::vec3 worldPos = glm::vec3(x, y, z) * voxelSize;
                    glm::vec3 d = glm::abs(worldPos - center) - halfExtents;

                    // SDF куба: max(max(d.x, d.y), d.z)
                    float outside = glm::max(glm::max(d.x, d.y), d.z);
                    float sdf = -outside; // < 0 — снаружи, > 0 — внутри

                    densities[index] = sdf;
                }
            }
        }

        return densities;
    }

    std::vector<float_t> generateWavySphereDensities(int densityCountAxis, float geometrySize) {
        SR_TRACY_ZONE;
        const int GRID_SIZE = densityCountAxis; // Размер сетки
        std::vector<float_t> density(GRID_SIZE * GRID_SIZE * GRID_SIZE);

        for (int z = 0; z < GRID_SIZE; ++z) {
            for (int y = 0; y < GRID_SIZE; ++y) {
                for (int x = 0; x < GRID_SIZE; ++x) {
                    // Нормализуем координаты в [-1, 1]
                    float fx = (float)x / (GRID_SIZE - 1) * 2.f - 1.f;
                    float fy = (float)y / (GRID_SIZE - 1) * 2.f - 1.f;
                    float fz = (float)z / (GRID_SIZE - 1) * 2.f - 1.f;

                    // Расстояние до центра
                    float dist = std::sqrt(fx * fx + fy * fy + fz * fz);

                    // Базовая плотность — сфера радиуса 0.5
                    float base = 0.5f * geometrySize - dist;

                    // Волны в разных плоскостях
                    float waveXZ = 0.07f * std::sin(10.f * fx) * std::sin(10.f * fz);
                    float waveXY = 0.07f * std::cos(12.f * fx) * std::cos(12.f * fy);

                    // Итоговая плотность
                    float finalDensity = base + waveXZ + waveXY;

                    density[x + y * GRID_SIZE + z * GRID_SIZE * GRID_SIZE] = finalDensity;
                }
            }
        }

        return density;
    }

    std::vector<float_t> GenerateSphereDensityField(int densityCountAxis, float geometrySize) {
        SR_TRACY_ZONE;

        /// Параметры сетки
        const int sizeX = densityCountAxis;
        const int sizeY = densityCountAxis;
        const int sizeZ = densityCountAxis;
        const float voxelSize = 1.0f; // шаг сетки в мире
        const float isoLevel = 0.0f;  // поверхность будет на расстоянии radius от центра

        /// Центр и радиус сферы
        glm::vec3 center = glm::vec3(sizeX, sizeY, sizeZ) * 0.5f * voxelSize;
        float radius = 20.0f * geometrySize;

        std::vector<float_t> densities(sizeX * sizeY * sizeZ);

        for (int z = 0; z < sizeZ; ++z) {
            for (int y = 0; y < sizeY; ++y) {
                for (int x = 0; x < sizeX; ++x) {
                    int index = z * sizeY * sizeX + y * sizeX + x;

                    // Мировая позиция текущего вокселя
                    glm::vec3 worldPos = glm::vec3(x, y, z) * voxelSize;

                    // SDF сферы: (расстояние от центра - радиус)
                    float d = radius - glm::distance(worldPos, center);

                    densities[index] = d;
                }
            }
        }

        return densities;
    }

    struct DensityFieldSettings {
        /// Параметры сетки
        int densityCountAxis = 64;
        float geometrySize = 1.0f;
        float isoLevel = 0.0f;

        /// Параметры генерации
        MarchingCubesShape shape = MarchingCubesShape::Sphere;
        float noiseScale = 1.0f; // для PerlinNoise
        double seed = 0.0; // для PerlinNoise
    };

    bool GenerateDensityField(const DensityFieldSettings& settings, std::vector<float_t>& outDensities) {
        SR_TRACY_ZONE;

        switch (settings.shape) {
            case MarchingCubesShape::Sphere:
                outDensities = GenerateSphereDensityField(settings.densityCountAxis, settings.geometrySize);
                break;

            case MarchingCubesShape::Cube:
                outDensities = GenerateCubeDensityField(settings.densityCountAxis, settings.geometrySize);
                break;

            case MarchingCubesShape::WavySphere:
                outDensities = generateWavySphereDensities(settings.densityCountAxis, settings.geometrySize);
                break;

            case MarchingCubesShape::PerlinNoise:
                outDensities = GeneratePerlinDensityField(settings.densityCountAxis, settings.noiseScale, settings.seed);
                break;

            default:
                return false; // Неизвестная форма
        }

        // Здесь можно сохранить или использовать сгенерированные данные
        // Например, передать их в шейдер или сохранить в файл

        return true; // Успешно сгенерировано
    }
}