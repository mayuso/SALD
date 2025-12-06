#pragma once
#include "Sald/Core/Core.h"

#include "Sald/Renderer/3D/Mesh.h"
#include "Sald/Renderer/Texture.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace Sald
{
    class Model
    {
    public:
        SALD_API Model();
        SALD_API ~Model();
        SALD_API void Load(const std::string &fileName);
        SALD_API void Render();
        SALD_API void Clear();

    private:
        void LoadNode(aiNode *node, const aiScene *scene);
        void LoadMesh(aiMesh *mesh, const aiScene *scene);
        void LoadMaterials(const aiScene *scene);

        std::vector<Mesh *> m_MeshList;
        std::vector<Texture *> m_TextureList;
        std::vector<unsigned int> m_MeshToTex;
    };

}