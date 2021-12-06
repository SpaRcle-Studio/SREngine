//
// Created by Monika on 26.07.2021.
//

#include <FbxLoader/Loader.h>
#include <FbxLoader/Utils.h>
#include <FbxLoader/Parser.h>

FbxLoader::Fbx FbxLoader::Loader::Load(
    const std::string& converter,
    const std::string& cache,
    const std::string& models,
    const std::string& path,
    bool optimizeGeometry
) {
    if (!Debug::IsInit())
        return {};

    std::string name  = Tools::BackReadTo(path, 'c');
    std::string dir   = Tools::ReadToLast(path, '/', 1);
    std::string ascii = Tools::FixPath(cache + "fbx_ascii/" + dir);
    Tools::CreatePath(ascii);

    system((converter + " -c " + models + path + " -o " + ascii + name + " -ascii").c_str());

    if (auto text = Tools::ReadAllText(ascii + name); text.empty()) {
        FBX_ERROR("FbxLoader::Load() : failed to read file!");
        return {};
    } else if (auto nodes = Parser::Parse(text); nodes) {
        Fbx fbx = {};

        if (fbx.objects = GetObjects(nodes); !fbx.objects.Ready()) {
            delete nodes;
            FBX_ERROR("FbxLoader::Load() : failed to get objects!");
            return {};
        }

        if (optimizeGeometry)
            for (auto& geometry : fbx.objects.geometries)
                if (!OptimizeGeometry(&geometry))
                    FBX_ERROR("FbxLoader::Load() : failed to optimize \"" + geometry.name + "\" geometry!");

        delete nodes;

        return fbx;
    } else {
        FBX_ERROR("FbxLoader::Load() : failed to parse file!");
        return {};
    }
}

FbxLoader::Objects FbxLoader::Loader::GetObjects(FbxLoader::Parser::Node *node) {
    auto node_objects = node->Find("Objects");
    if (!node_objects)
        return {};

    Objects objects = {};

    for (auto object : node_objects->nodes) {
        switch (StateFromString(object->value)) {
            case State::Geometry: {
                auto info = Tools::Split(object->subData, ',');
                if (info.size() != 3) {
                    FBX_ERROR("FbxLoader::GetObjects() : failed to get geometry info!");
                    return {};
                }

                Geometry geometry = { };
                geometry.id = std::stoll(info[0]);
                geometry.name = Tools::GetBetween(info[1], '\"');
                geometry.type = Tools::GetBetween(info[2], '\"');

                if (auto indices = object->Find("PolygonVertexIndex"); indices) {
                    geometry.indices = FixIndices(Tools::SplitAndCastToInt32(indices->Get2SubNode()->value, ','));
                    if (geometry.indices.empty()) {
                        FBX_ERROR("FbxLoader::GetObjects() : failed parse indices!");
                        return {};
                    }
                    if (geometry.vertices = GetVertices(object, geometry.indices); geometry.vertices.empty()) {
                        FBX_ERROR("FbxLoader::GetObjects() : failed parse vertices!");
                        return {};
                    }
                } else {
                    FBX_ERROR("FbxLoader::GetObjects() : failed to get indices!");
                    return {};
                }

                objects.geometries.emplace_back(geometry);
                break;
            }
            default:
                break;
        }
    }

    return objects;
}

std::vector<FbxLoader::Vertex> FbxLoader::Loader::GetVertices(FbxLoader::Parser::Node *object, const std::vector<uint32_t> &indices) {
    auto vertices_node = object->Find("Vertices")->Get2SubNode();

    auto normals_node = [object]() -> Parser::Node* {
        if (auto v = object->Find("LayerElementNormal"); v) return v->Find("Normals")->Get2SubNode(); return nullptr;
    }();

    auto binormals_node = [object]() -> Parser::Node* {
        if (auto v = object->Find("LayerElementBinormal"); v) return v->Find("Binormals")->Get2SubNode(); return nullptr;
    }();

    auto tangents_node = [object]() -> Parser::Node* {
        if (auto v = object->Find("LayerElementTangent"); v) return v->Find("Tangents")->Get2SubNode(); return nullptr;
    }();

    auto uvs_node = [object]() -> Parser::Node* {
        if (auto v = object->Find("LayerElementUV"); v) return v->Find("UV")->Get2SubNode(); return nullptr;
    }();

    auto uvIndices_node = [object]() -> Parser::Node* {
        if (auto layerUV = object->Find("LayerElementUV"); layerUV)
            if (auto uvIndex = layerUV->Find("UVIndex"); uvIndex)
                return uvIndex->Get2SubNode();
        return nullptr;
    }();

    return MakeVertices(
            indices,
            vertices_node  ? Tools::SplitAndCastToFloat(vertices_node->value, ',')   : std::vector<float_t>(),
            normals_node   ? Tools::SplitAndCastToFloat(normals_node->value, ',')    : std::vector<float_t>(),
            binormals_node ? Tools::SplitAndCastToFloat(binormals_node->value, ',')  : std::vector<float_t>(),
            tangents_node  ? Tools::SplitAndCastToFloat(tangents_node->value, ',')   : std::vector<float_t>(),
            uvs_node       ? Tools::SplitAndCastToFloat(uvs_node->value, ',')        : std::vector<float_t>(),
            uvIndices_node ? Tools::SplitAndCastToUInt32(uvIndices_node->value, ',') : std::vector<uint32_t>()
    );
}

bool FbxLoader::Loader::OptimizeGeometry(FbxLoader::Geometry *geometry) {
    if (!geometry)
        return false;

    std::vector<uint32_t> indices  = {};
    std::vector<Vertex>   vertices = {};

    std::unordered_map<Vertex, uint32_t> uniqueVertices {};

    for (auto vertex : geometry->vertices) {
        if (uniqueVertices.count(vertex) == 0) {
            uniqueVertices[vertex] = static_cast<uint32_t>(vertices.size());
            vertices.push_back(vertex);
        }

        indices.push_back(uniqueVertices[vertex]);
    }

    geometry->vertices = vertices;
    geometry->indices  = indices;

    return true;
}
