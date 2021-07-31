//
// Created by Monika on 26.07.2021.
//

#ifndef FBXLOADER_LOADER_H
#define FBXLOADER_LOADER_H

#include <FbxLoader/Fbx.h>
#include <mutex>
#include "Parser.h"

namespace FbxLoader {
    enum class State {
        Unknown, Definitions, Objects, NodeAttribute, Geometry, Vertices, PolygonVertexIndex
    };

    inline static State StateFromString(const std::string& str) {
        if (str == "Definitions")
            return State::Definitions;
        else if (str == "Objects")
            return State::Objects;
        else if (str == "NodeAttribute")
            return State::NodeAttribute;
        else if (str == "Geometry")
            return State::Geometry;
        else if (str == "Vertices")
            return State::Vertices;
        else if (str == "PolygonVertexIndex")
            return State::PolygonVertexIndex;
        else
            return State::Unknown;
    }

    class Loader {
    public:
        Loader(const Loader&) = delete;
        Loader() = delete;
        ~Loader() = delete;
    private:
        static bool OptimizeGeometry(Geometry* geometry);
        static std::vector<Vertex> GetVertices(Parser::Node* node, const std::vector<uint32_t>& indices);
        static Objects GetObjects(Parser::Node* node);
    public:
        static Fbx Load(
                const std::string& converter,
                const std::string& cache,
                const std::string& models,
                const std::string& path,
                bool optimizeGeometry);
    };
}

#endif //FBXLOADER_LOADER_H
