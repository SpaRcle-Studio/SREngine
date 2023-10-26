//
// Created by innerviewer on 10/26/2023.
//

#include <Utils/Common/Vertices.h>
#include <Utils/Debug.h>

#include <Hull/Coordinate.h>
#include <QuickHull/FastQuickHull.h>

namespace SR_UTILS_NS {
    std::vector<Vertex> ComputeConvexHull(const std::vector<Vertex>& vertices) {
        std::vector<hull::Coordinate> coordinates;
        coordinates.reserve(vertices.size());

        for (auto&& vertex : vertices) {
            coordinates.emplace_back(hull::Coordinate{vertex.position.x, vertex.position.y, vertex.position.z});
        }

        auto&& hullCoordinates = qh::convex_hull(coordinates);

        std::vector<Vertex> hullVertices;
        hullVertices.reserve(hullCoordinates.size() * 3);

        for (uint16_t i = 0; i <= hullCoordinates.size(); ++i) {
            auto&& face = hullCoordinates[i];

            hullVertices.emplace_back(vertices[face[0]]);
            hullVertices.emplace_back(vertices[face[1]]);
            hullVertices.emplace_back(vertices[face[2]]);
        }

        return hullVertices;
    }
}
