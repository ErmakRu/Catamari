#include "MeshRenderComponent.h"

void MeshRenderComponent::ProcessNode(aiNode* node, const aiScene* scene)
{
    for (UINT i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        ProcessMesh(mesh, scene);
    }
    for (UINT i = 0; i < node->mNumChildren; i++)
    {
        ProcessNode(node->mChildren[i], scene);
    }
}

void MeshRenderComponent::ProcessMesh(aiMesh* mesh, const aiScene* scene)
{
    for (UINT i = 0; i < mesh->mNumVertices; i++)
    {
        Point point;

        point.Pos.x = mesh->mVertices[i].x;
        point.Pos.y = mesh->mVertices[i].y;
        point.Pos.z = mesh->mVertices[i].z;
        point.Pos.w = 1.0f;

        if (mesh->mTextureCoords[0])
        {
            point.TexturePos.x = mesh->mTextureCoords[0][i].x;
            point.TexturePos.y = mesh->mTextureCoords[0][i].y;
        }

        points.push_back(point);
    }

    for (UINT i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];

        for (UINT j = 0; j < face.mNumIndices; j++)
            indeces.push_back(face.mIndices[j]);
    }
}

MeshRenderComponent::MeshRenderComponent(Game* g, std::string fileNameModel, const wchar_t* fileNameTexture):
    TriangleComponent(g), fNameModel(fileNameModel), isPickedUp(false)
{
    textureFileName = fileNameTexture;
}

void MeshRenderComponent::Initialize()
{
    Assimp::Importer importer;

    const aiScene* pScene = importer.ReadFile(fNameModel.c_str(), aiProcess_Triangulate | aiProcess_ConvertToLeftHanded);

    ProcessNode(pScene->mRootNode, pScene);

    TriangleComponent::Initialize();
}

