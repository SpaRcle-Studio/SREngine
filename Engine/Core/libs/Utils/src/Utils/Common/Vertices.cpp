//
// Created by innerviewer on 10/26/2023.
//

#include <Utils/Common/Vertices.h>
#include <Utils/Debug.h>

#include <Hull/Coordinate.h>
#include <QuickHull/FastQuickHull.h>

#include <quickhull/quickhull.hpp>

#include <Utils/Types/RawMesh.h>

namespace SR_UTILS_NS {
/*    SR_HTYPES_NS::ConvexRawMesh ComputeConvexHull(const std::vector<Vertex>& rawVertices) {
        std::vector<hull::Coordinate> coordinates;
        coordinates.reserve(rawVertices.size());

        for (auto&& vertex : rawVertices) {
            coordinates.emplace_back(hull::Coordinate{vertex.position.x, vertex.position.y, vertex.position.z});
        }

        qh::ConvexHullContext context;
        context.max_iterations = 2000;
        auto&& hullIndices = qh::convex_hull(coordinates, context);

        std::vector<SR_MATH_NS::FVector3> convexMeshVertices;
        for (auto&& vertex : rawVertices) {
            convexMeshVertices.emplace_back(vertex.position.x, vertex.position.y, vertex.position.z);
        }

        for (auto&& convexMeshVertex : convexMeshVertices) {
            convexMeshVertex *= 10.0f;
        }

        std::vector<uint32_t> convexMeshIndices;
        for (auto&& index : hullIndices) {
            convexMeshIndices.emplace_back(index[0]);
            convexMeshIndices.emplace_back(index[1]);
            convexMeshIndices.emplace_back(index[2]);
        }

        SR_HTYPES_NS::ConvexRawMesh convexRawMesh;
        convexRawMesh.vertices = std::move(convexMeshVertices);
        convexRawMesh.indices = std::move(convexMeshIndices);

        return convexRawMesh;
    }*/

    SR_HTYPES_NS::ConvexRawMesh ComputeConvexHull(const std::vector<Vertex>& rawVertices) {
        quickhull::QuickHull<float> quickHull;
        std::vector<quickhull::Vector3<float>> pointCloud;
        pointCloud.reserve(rawVertices.size());

        for (auto&& vertex : rawVertices) {
            pointCloud.emplace_back(vertex.position.x, vertex.position.y, vertex.position.z);
        }

        auto&& hull = quickHull.getConvexHull(pointCloud, false, false);
        auto&& indexBuffer = hull.getIndexBuffer();
        auto&& vertexBuffer = hull.getVertexBuffer();

        std::vector<SR_MATH_NS::FVector3> convexMeshVertices;
        for (auto&& vertex : vertexBuffer) {
            convexMeshVertices.emplace_back(vertex.x, vertex.y, vertex.z);
        }

        for (auto&& convexMeshVertex : convexMeshVertices) {
            convexMeshVertex *= 10.0f;
        }

        std::vector<uint32_t> convexMeshIndices;
        for (auto&& index : indexBuffer) {
            convexMeshIndices.emplace_back(index);
        }

        SR_HTYPES_NS::ConvexRawMesh convexRawMesh;
        convexRawMesh.vertices = std::move(convexMeshVertices);
        convexRawMesh.indices = std::move(convexMeshIndices);

        return convexRawMesh;
    }
}
