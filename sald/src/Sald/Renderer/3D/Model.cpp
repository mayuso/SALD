#include "saldpch.h"
#include "Sald/Renderer/3D/Model.h"

#include "Sald/Core/Log.h"

Sald::Model::Model()
{
}

Sald::Model::~Model()
{
}

void Sald::Model::RenderModel()
{
    for (size_t i = 0; i < m_MeshList.size(); i++)
    {
        unsigned int materialIndex = m_MeshToTex[i];

        if (materialIndex < m_TextureList.size() && m_TextureList[materialIndex])
        {
            m_TextureList[materialIndex]->UseTexture();
        }
        m_MeshList[i]->RenderMesh();
    }
}

void Sald::Model::LoadModel(const std::string &fileName)
{
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(fileName, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenSmoothNormals | aiProcess_JoinIdenticalVertices);

    if (!scene)
    {
        SALD_CORE_ERROR("Model ({0}) failed to load: {1}", fileName.c_str(), importer.GetErrorString());
        return;
    }
    LoadNode(scene->mRootNode, scene);
    LoadMaterials(scene);
}

void Sald::Model::LoadNode(aiNode *node, const aiScene *scene)
{
    for (size_t i = 0; i < node->mNumMeshes; i++)
    {
        LoadMesh(scene->mMeshes[node->mMeshes[i]], scene);
    }

    for (size_t i = 0; i < node->mNumChildren; i++)
    {
        LoadNode(node->mChildren[i], scene);
    }
}
void Sald::Model::LoadMesh(aiMesh *mesh, const aiScene *scene)
{
    std::vector<GLfloat> vertices;
    std::vector<unsigned int> indices;

    for (size_t i = 0; i < mesh->mNumVertices; i++)
    {
        vertices.insert(vertices.end(), {mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z});
        if (mesh->mTextureCoords[0])
        {
            vertices.insert(vertices.end(), {mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y});
        }
        else
        {
            vertices.insert(vertices.end(), {0.0f, 0.0f});
        }
        vertices.insert(vertices.end(), {-mesh->mNormals[i].x, -mesh->mNormals[i].y, -mesh->mNormals[i].z});
    }
    for (size_t i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for (size_t j = 0; j < face.mNumIndices; j++)
        {
            indices.push_back(face.mIndices[j]);
        }
    }

    Mesh *newMesh = new Mesh();
    newMesh->CreateMesh(&vertices[0], &indices[0], vertices.size(), indices.size(), true);
    m_MeshList.push_back(newMesh);
    m_MeshToTex.push_back(mesh->mMaterialIndex);
}

void Sald::Model::LoadMaterials(const aiScene *scene)
{
    m_TextureList.resize(scene->mNumMaterials);

    for (size_t i = 0; i < scene->mNumMaterials; i++)
    {
        aiMaterial *material = scene->mMaterials[i];

        m_TextureList[i] = nullptr;

        if (material->GetTextureCount(aiTextureType_DIFFUSE))
        {
            aiString path;
            if (material->GetTexture(aiTextureType_DIFFUSE, 0, &path) == AI_SUCCESS)
            {
                int idx = std::string(path.data).rfind("\\");
                if (idx == -1)
                {
                    idx = std::string(path.data).rfind("/");
                }
                std::string fileName = std::string(path.data).substr(idx + 1);
                std::string texPath = std::string("Textures/") + fileName;

                m_TextureList[i] = new Texture(texPath.c_str());
                if (!m_TextureList[i]->LoadTexture())
                {
                    SALD_CORE_ERROR("Failed to load texture at: {0}", texPath.c_str());
                    delete m_TextureList[i];
                    m_TextureList[i] = nullptr;
                }
            }
        }
        if (!m_TextureList[i])
        {
            m_TextureList[i] = new Texture("Textures/plain.png");
            m_TextureList[i]->LoadTexture();
        }
    }
}

void Sald::Model::ClearModel()
{
    for (size_t i = 0; i < m_MeshList.size(); i++)
    {
        if (m_MeshList[i])
        {
            delete m_MeshList[i];
            m_MeshList[i] = nullptr;
        }
    }

    for (size_t i = 0; i < m_TextureList.size(); i++)
    {
        if (m_TextureList[i])
        {
            delete m_TextureList[i];
            m_TextureList[i] = nullptr;
        }
    }
}