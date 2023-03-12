#pragma once
#include "GameComponent.h"
#include <d3d.h>
#include <d3d11.h>
#include <d3dcompiler.h>
#include <directxmath.h>
#include "SimpleMath.h"
#include <vector>

struct Point
{
	DirectX::SimpleMath::Vector4 Pos;
	DirectX::SimpleMath::Vector4 TexturePos;
};
class TriangleComponent : public GameComponent
{
protected:
	ID3D11InputLayout* layout;
	ID3D11PixelShader* pixelShader;
	ID3DBlob* pixelShaderByteCode;
	ID3D11RasterizerState* rastState;
	ID3D11VertexShader* vertexShader;
	ID3DBlob* vertexShaderByteCode;
	ID3D11Buffer* vertexBuffer;
	ID3D11Buffer* indexBuffer;
	ID3D11Buffer* constBuffer;
	UINT strides[1];
	UINT offsets[1];
	std::vector <Point> points;
	std::vector<UINT> indeces;
	bool passThroughVS;
	bool colorModePS;
	D3D_PRIMITIVE_TOPOLOGY topologyType;
	virtual CD3D11_RASTERIZER_DESC CreateRasterizerStateDesc();
	const wchar_t* textureFileName;
	ID3D11SamplerState* samplerState;
public:
	TriangleComponent(Game* g);
	~TriangleComponent();
	void DestroyResources() override;
	void Draw() override;
	void Initialize() override;
	void Update() override;
	void Reload() override;
};
