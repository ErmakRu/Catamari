#pragma once
#include "TriangleComponent.h"

class Game;

class SphereComponent : public TriangleComponent
{
//protected:
//	ID3D11InputLayout* layout;
//	ID3D11PixelShader* pixelShader;
//	ID3DBlob* pixelShaderByteCode;
//	//std::vector <Point> points;
//	//std::vector<UINT> indeces;
//	ID3D11RasterizerState* rastState;
//	ID3D11VertexShader* vertexShader;
//	ID3DBlob* vertexShaderByteCode;
//	ID3D11Buffer* vertexBuffer;
//	ID3D11Buffer* indexBuffer;
//	ID3D11Buffer* constBuffer;
//	UINT strides[1];
//	UINT offsets[1];
public:
    explicit SphereComponent(Game* game, float radius, int sliceCount, int stackCount, const wchar_t* diffuseTextureName);
	void Initialize() override;
	//virtual ~SphereComponent();
	//void DestroyResources() override;
	//void Draw() override;
	//void Initialize() override;
	//void Update() override;
	//void Reload() override;
};

