//
// Created by Monika on 31.01.2022.
//

#include <FbxLoader/Fbx.h>
#include <FbxLoader/Utils.h>
#include <fstream>
#include <iostream>

void FbxLoader::NodeAttribute::Save(std::ofstream& file) const {
    Tools::SaveValue(file, id);
    Tools::SaveString(file, name);
    Tools::SaveString(file, type);
}

void FbxLoader::NodeAttribute::Load(std::ifstream &file) {
    id = Tools::LoadValue<int64_t>(file);
    name = Tools::LoadStr(file);
    type = Tools::LoadStr(file);
}

FbxLoader::NodeAttribute::NodeAttribute()
    : id(0)
{ }

FbxLoader::Geometry::Geometry()
    : id(0)
{ }

void FbxLoader::Geometry::Save(std::ofstream &file) const {
    Tools::SaveValue(file, id);
    Tools::SaveString(file, name);
    Tools::SaveString(file, type);
    Tools::SaveComplexVector(file, vertices);
    Tools::SaveVector(file, indices);
    Tools::SaveVectorOfPairs(file, materials);
}

void FbxLoader::Geometry::Load(std::ifstream &file) {
    id = Tools::LoadValue<int64_t>(file);
    name = Tools::LoadStr(file);
    type = Tools::LoadStr(file);
    vertices = Tools::LoadComplexVector<Vertex>(file);
    indices = Tools::LoadVector<uint32_t>(file);
    materials = Tools::LoadVectorOfPairs<uint32_t, uint32_t>(file);
}

bool FbxLoader::Geometry::Valid() const {
    return !indices.empty() && !vertices.empty();
}

void FbxLoader::Objects::Save(std::ofstream &file) const {
    Tools::SaveComplexVector(file, nodeAttributes);
    Tools::SaveComplexVector(file, geometries);
    Tools::SaveComplexVector(file, models);
}

void FbxLoader::Objects::Load(std::ifstream &file) {
    nodeAttributes = Tools::LoadComplexVector<NodeAttribute>(file);
    geometries = Tools::LoadComplexVector<Geometry>(file);
}

void FbxLoader::Objects::Clear() {
    geometries.clear();
    nodeAttributes.clear();
}

void FbxLoader::Definitions::Save(std::ofstream &file) const {
    Tools::SaveValue(file, version);
    Tools::SaveValue(file, count);
}

void FbxLoader::Definitions::Load(std::ifstream &file) {
    version = Tools::LoadValue<uint32_t>(file);
    count = Tools::LoadValue<uint32_t>(file);
}

void FbxLoader::Definitions::Clear() {
    count = 0;
    version = 0;
}

void FbxLoader::Fbx::Save(std::ofstream &file) const {
    definitions.Save(file);
    objects.Save(file);
}

void FbxLoader::Fbx::Load(std::ifstream &file) {
    definitions.Load(file);
    objects.Load(file);
}

void FbxLoader::Connections::Save(std::ofstream &file) const {

}

void FbxLoader::Connections::Load(std::ifstream &file) {

}

void FbxLoader::Connections::Clear() {
    geometryToModel.clear();
    materialToModel.clear();
    textureToMaterial.clear();
    videoToTexture.clear();
    nodeAttributeToModel.clear();
    modelToModel.clear();
}

void FbxLoader::Model::Save(std::ofstream &file) const {
    Tools::SaveValue(file, id);
    Tools::SaveString(file, name);
    Tools::SaveString(file, type);
    Tools::SaveValue(file, Translation);
    Tools::SaveValue(file, Rotation);
    Tools::SaveValue(file, Scale);
}

void FbxLoader::Model::Load(std::ifstream &file) {
    id = Tools::LoadValue<uint64_t>(file);
    name = Tools::LoadStr(file);
    type = Tools::LoadStr(file);
    Translation = Tools::LoadValue<vec3>(file);
    Rotation = Tools::LoadValue<vec3>(file);
    Scale = Tools::LoadValue<vec3>(file);
}

bool FbxLoader::Model::Valid() const {
    return id != 0;
}
