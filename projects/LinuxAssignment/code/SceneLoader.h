#pragma once

#include "core/app.h"

#include <fstream>
#include <iostream>
#include "tiny_gltf.h"

#define TINYGLTF_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define TINYGLTF_NOEXCEPTION
#define JSON_NOEXCEPTION

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

using namespace std;

class SceneLoader
{
public:

    SceneLoader() {};
    ~SceneLoader() {};

    bool LoadModel(tinygltf::Model &model, const char *fileName)
    {
        tinygltf::TinyGLTF loader;
        string err, warn;
        return loader.LoadASCIIFromFile(&model, &err, &warn, fileName);
    }

    map<int, unsigned int> BindMesh(map<int, unsigned int> vbos, tinygltf::Model &model, tinygltf::Mesh &mesh) 
    {
        for (size_t i = 0; i < model.bufferViews.size(); ++i) 
        {
            const tinygltf::BufferView &bufferView = model.bufferViews[i];

            if (bufferView.target == 0) 
            {
                cout << "WARN: bufferView.target is zero" << endl;
                continue;
            }
        
            const tinygltf::Buffer &buffer = model.buffers[bufferView.buffer];
            cout << "bufferview.target " << bufferView.target << endl;
        
            unsigned int vbo;
            glGenBuffers(1, &vbo);
            vbos[i] = vbo;
            glBindBuffer(bufferView.target, vbo);
        
            cout << "buffer.data.size = " << buffer.data.size() << ", bufferview.byteOffset = " << bufferView.byteOffset << endl;
        
            glBufferData(bufferView.target, bufferView.byteLength, &buffer.data.at(0) + bufferView.byteOffset, GL_STATIC_DRAW);
        }
        
        for (size_t i = 0; i < mesh.primitives.size(); ++i) 
        {
            tinygltf::Primitive primitive = mesh.primitives[i];
            tinygltf::Accessor indexAccessor = model.accessors[primitive.indices];
        
            for (auto &attrib : primitive.attributes) 
            {
                tinygltf::Accessor accessor = model.accessors[attrib.second];
                int byteStride = accessor.ByteStride(model.bufferViews[accessor.bufferView]);
                glBindBuffer(GL_ARRAY_BUFFER, vbos[accessor.bufferView]);

                int size = 1;
                if (accessor.type != TINYGLTF_TYPE_SCALAR) 
                {
                    size = accessor.type;
                }

                int vaa = -1;
                if (attrib.first.compare("POSITION")   == 0) vaa = 0;
                if (attrib.first.compare("NORMAL")     == 0) vaa = 1;
                if (attrib.first.compare("TEXCOORD_0") == 0) vaa = 2;

                if (vaa > -1) 
                {
                    glEnableVertexAttribArray(vaa);
                    glVertexAttribPointer(vaa, size, accessor.componentType, accessor.normalized ? GL_TRUE : GL_FALSE, byteStride, BUFFER_OFFSET(accessor.byteOffset));
                }
                else
                    cout << "vaa missing: " << attrib.first << endl;
            }
        
            if (model.textures.size() > 0) 
            {
                tinygltf::Texture &tex = model.textures[0];

                if (tex.source == -1)
                {
                    return vbos;
                }
        
                unsigned int texid;
                glGenTextures(1, &texid);

                tinygltf::Image &image = model.images[tex.source];

                glBindTexture(GL_TEXTURE_2D, texid);
                glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
                glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

                GLenum format = GL_RGBA;

                if (image.component == 1) 
                {
                    format = GL_RED;
                } 
                else if (image.component == 2) 
                {
                    format = GL_RG;
                } 
                else if (image.component == 3) 
                {
                    format = GL_RGB;
                }

                GLenum type = GL_UNSIGNED_BYTE;
                if (image.bits == 8) 
                {
                    // ok
                } 
                else if (image.bits == 16) 
                {
                    type = GL_UNSIGNED_SHORT;
                } 

                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.width, image.height, 0, format, type, &image.image.at(0));
            }
        }
        
        return vbos;
    }


    // bind models
    void BindModelNodes(map<int, unsigned int> vbos, tinygltf::Model &model, tinygltf::Node &node) 
    {
        if ((node.mesh >= 0) && (node.mesh < model.meshes.size())) 
        {
            BindMesh(vbos, model, model.meshes[node.mesh]);
        }

        for (size_t i = 0; i < node.children.size(); i++) 
        {
          assert((node.children[i] >= 0) && (node.children[i] < model.nodes.size()));
          BindModelNodes(vbos, model, model.nodes[node.children[i]]);
        }
    }

    unsigned int BindModel(tinygltf::Model &model) 
    {
        map<int, unsigned int> vbos;
        unsigned int vao;
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        const tinygltf::Scene &scene = model.scenes[model.defaultScene];
        for (size_t i = 0; i < scene.nodes.size(); ++i) {
          assert((scene.nodes[i] >= 0) && (scene.nodes[i] < model.nodes.size()));
          BindModelNodes(vbos, model, model.nodes[scene.nodes[i]]);
        }

        glBindVertexArray(0);

        // cleanup vbos
        for (size_t i = 0; i < vbos.size(); ++i) 
        {
            glDeleteBuffers(1, &vbos[i]);
        }

        return vao;
    }

    void DrawMesh(tinygltf::Model &model, tinygltf::Mesh &mesh)
    {
        for (size_t i = 0; i < mesh.primitives.size(); ++i)
        {
            tinygltf::Primitive primitive = mesh.primitives[i];
            tinygltf::Accessor accessor = model.accessors[primitive.indices];

            glDrawElements(primitive.mode, accessor.count, accessor.componentType, BUFFER_OFFSET(accessor.byteOffset));
        }
    }

    void DrawModelNodes(tinygltf::Model &model, tinygltf::Node &node)
    {
        if (node.mesh >= 0 && node.mesh < model.meshes.size())
        {
            DrawMesh(model, model.meshes[node.mesh]);
        }

        for (size_t i = 0; i < node.children.size(); ++i)
        {
            DrawModelNodes(model, model.nodes[node.children[i]]);
        }
    }

    void DrawModel(unsigned int vao, tinygltf::Model &model)
    {
        glBindVertexArray(vao);

        const tinygltf::Scene &scene = model.scenes[model.defaultScene];
        for (size_t i = 0; i < scene.nodes.size(); ++i)
        {
            DrawModelNodes(model, model.nodes[scene.nodes[i]]);
        }
        
        glBindVertexArray(0);
    }

};