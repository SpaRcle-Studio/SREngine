//
// Created by Monika on 26.07.2021.
//

#include <FbxLoader/Loader.h>
#include <FbxLoader/Utils.h>
#include <FbxLoader/Parser.h>
#include <FbxLoader/MD5Hash.h>
#include <unordered_set>

FbxLoader::Fbx FbxLoader::Loader::Load(
    const std::string& converter,
    const std::string& cache,
    const std::string& models,
    const std::string& path,
    bool optimizeGeometry
) {
    if (!Debug::IsInit())
        return {};

    const std::string name      = Tools::BackReadTo(path, '/');
    const std::string dir       = Tools::ReadToLast(path, '/', 1);
    const std::string ascii     = Tools::FixPath(cache + "/fbx_ascii/" + dir);
    const std::string model     = models + "/" + path;
    const std::string hashPath  = ascii + name + ".hash";
    const std::string cacheFile = ascii + name + ".cache";

    const std::string hash = Tools::GetHash(model);

    if (Tools::FileExists(hashPath) && Tools::LoadHash(hashPath) == hash) {
        Fbx fbx;
        fbx.LoadFrom(cacheFile);
        return fbx;
    }
    else {
        Tools::CreatePath(ascii);
        system((converter + " -c " + model + " -o " + ascii + name + " -ascii").c_str());
        Tools::SaveHash(hashPath, hash);
    }

    if (auto text = Tools::ReadAllText(ascii + name); text.empty()) {
        FBX_ERROR("FbxLoader::Load() : failed to read file! \n\tPath: " + ascii + name);
        return {};
    }
    else if (auto nodes = Parser::Parse(text); nodes) {
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

        if (!fbx.objects.geometries.empty()) {
            const auto source = fbx.objects.geometries; /// copy
            fbx.objects.geometries.clear();
            for (const auto& src : source)
                for (const auto& geometry : SplitByMaterials(src))
                    fbx.objects.geometries.emplace_back(geometry);
        }

        delete nodes;

        fbx.SaveTo(cacheFile);

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

                    geometry.materials = GetMaterials(object);
                }
                else {
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

std::vector<FbxLoader::Material> FbxLoader::Loader::GetMaterials(FbxLoader::Parser::Node *object) {
    std::vector<Material> materials;

    auto materials_node = [object]() -> Parser::Node* {
        if (auto v = object->Find("LayerElementMaterial"); v) return v->Find("Materials")->Get2SubNode(); return nullptr;
    }();

    if (!materials_node)
        return {};

    std::istringstream ss(materials_node->value);
    std::string value;
    Material material;

    uint32_t last = 0;
    uint32_t counter = 0;
    while (getline(ss, value, ',')) {
        auto id = static_cast<uint32_t>(std::stoi(value));

        if (id != last) {
            last = id;
            material.second = counter - 1;

            materials.emplace_back(material);

            material.first = counter;
        }

        ++counter;
    }

    material.second = counter - 1;
    materials.emplace_back(material);

    return materials;
}

std::vector<FbxLoader::Geometry> FbxLoader::Loader::SplitByMaterials(const Geometry& geometry) {
    if (geometry.materials.size() <= 1)
        return { geometry };

    std::vector<Geometry> geometries;

    uint32_t materialIndex= 0;
    for (const auto& material : geometry.materials) {
        Geometry newGeometry;

        newGeometry.materials = { material };
        newGeometry.name = geometry.name + " (" + std::to_string(materialIndex++) + ")";
        newGeometry.type = geometry.type;
        newGeometry.id   = geometry.id;

        std::vector<Vertex> vertices;
        std::unordered_map<Vertex, uint32_t> unique;
        uint32_t index = 0;

        for (auto vertexIndex : std::vector<uint32_t>(
                geometry.indices.begin() + material.first * 3,
                geometry.indices.begin() + material.second * 3))
        {
            auto&& vertex = geometry.vertices[vertexIndex];

            if (unique.count(vertex) == 0) {
                unique[vertex] = static_cast<uint32_t>(vertices.size());
                vertices.push_back(vertex);
            }

            newGeometry.indices.push_back(unique[vertex]);
        }

        newGeometry.vertices = vertices;

        geometries.emplace_back(newGeometry);
    }

    return geometries;
}

