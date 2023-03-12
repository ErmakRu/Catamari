#pragma once
//#include <d3d.h>
//#include <d3d11.h>
//#include <d3dcompiler.h>
//#include <directxmath.h>
#include "SimpleMath.h"
//#include <vector>
#include <string>
#include "TriangleComponent.h"
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <assimp/Importer.hpp>

class CatamariBall;

using namespace std;

class QuadComponent :
    public TriangleComponent
{
//protected:
//	ID3D11InputLayout* layout;
//	ID3D11PixelShader* pixelShader;
//	ID3DBlob* pixelShaderByteCode;
//	std::vector<DirectX::SimpleMath::Vector4> points;
//	std::vector<UINT> indeces;
//	//DirectX::SimpleMath::Vector4 points[24];
//	ID3D11RasterizerState* rastState;
//	ID3D11VertexShader* vertexShader;
//	ID3DBlob* vertexShaderByteCode;
//	ID3D11Buffer* vertexBuffer;
//	ID3D11Buffer* indexBuffer;
//	ID3D11Buffer* constBuffer;
//	UINT strides[1];
//	UINT offsets[1];
//	DirectX::SimpleMath::Vector4 offset;
//public:
//	QuadComponent(Game* g, const wchar_t* texture);
//	virtual ~QuadComponent();
//	void DestroyResources() override;
//	void Draw() override;
//	void Initialize() override;
//	void Update() override;
//	void Reload() override;
//	void SetPosition(float x, float y);
//	void SetPosition(DirectX::SimpleMath::Vector2 pos);
//	void SetY(float y);
//	void SetX(float x);
//	float GetX() const;
//	float GetY() const;
//	DirectX::SimpleMath::Vector2 GetPosition() const;
protected:
    const std::string fNameModel;
    CD3D11_RASTERIZER_DESC CreateRasterizerStateDesc() override;
    void ProcessNode(aiNode* node, const aiScene* scene);
    void ProcessMesh(aiMesh* mesh, const aiScene* scene);
public:
    CatamariBall* Cb;
    explicit QuadComponent(Game* g, const wchar_t* diffuseTextureName);
    void Initialize() override;

};

