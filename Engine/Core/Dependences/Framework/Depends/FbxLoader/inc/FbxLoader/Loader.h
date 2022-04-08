//
// Created by Monika on 26.07.2021.
//

#ifndef FBXLOADER_LOADER_H
#define FBXLOADER_LOADER_H

#include <FbxLoader/Parser.h>
#include <FbxLoader/Fbx.h>
#include <FbxLoader/Optimization.h>
#include <mutex>

namespace FbxLoader {
    enum class State {
        Unknown, Definitions, Objects, NodeAttribute, Geometry, Vertices, PolygonVertexIndex
    };

    typedef std::vector<Vertex> VertexGroup;
    typedef std::vector<VertexGroup> VertexGroups;

    class Loader {
    public:
        Loader(const Loader&) = delete;
        Loader() = delete;
        ~Loader() = delete;

    public:
        static RawFbx Load(
                const std::string& converter,
                const std::string& cache,
                const std::string& models,
                const std::string& path,
                bool optimizeGeometry);

    private:
        static RawFbx LoadFbx(const std::string& ascii, const std::string& cache, bool needOptimize);
        static RawFbx LoadObj(const std::string& path, const std::string& cache, bool needOptimize);

        static bool OptimizeGeometry(RawGeometry* geometry);

        static std::vector<RawGeometry> SplitByMaterials(RawGeometry&& geometries);

        static RawGeometry ParseGeometry(Parser::Node* node);
        static RawModel ParseModel(Parser::Node* node);
        static NodeAttribute ParseNodeAttribute(Parser::Node* node);

        static std::vector<Vertex> GetVertices(Parser::Node* node, const std::vector<uint32_t>& indices);
        static Objects GetObjects(Parser::Node* node);
        static std::vector<MaterialRange> GetMaterialRanges(Parser::Node* node);

    };
}

#endif //FBXLOADER_LOADER_H
