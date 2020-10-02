#pragma once

#include "config.h"

#include <fstream>
#include <iostream>

#include "tiny_gltf.h"

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

using namespace std;

class SceneLoader
{
public:

    SceneLoader() {};
    ~SceneLoader() {};

    bool LoadModel(tinygltf::Model &model, const char *fileName);

    map<int, unsigned int> BindMesh(map<int, unsigned int> vbos, tinygltf::Model &model, tinygltf::Mesh &mesh);

    // bind models
    void BindModelNodes(map<int, unsigned int> vbos, tinygltf::Model &model, tinygltf::Node &node);

    unsigned int BindModel(tinygltf::Model &model);

    void DrawMesh(tinygltf::Model &model, tinygltf::Mesh &mesh);

    void DrawModelNodes(tinygltf::Model &model, tinygltf::Node &node);

    void DrawModel(unsigned int vao, tinygltf::Model &model);
};