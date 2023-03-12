#pragma once

#include <string>
#include "TriangleComponent.h"
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <assimp/Importer.hpp>

class CatamariBall;

class MeshRenderComponent : public TriangleComponent
{
protected:
    const std::string fNameModel;
    void ProcessNode(aiNode* node, const aiScene* scene);
    void ProcessMesh(aiMesh* mesh, const aiScene* scene);
public:
    bool isPickedUp;
    CatamariBall* Cb;
    MeshRenderComponent(Game* g, std::string fileNameModel, const wchar_t* fileNameTexture);
    void Initialize() override;
};

