#include "SphereComponent.h"
#include "Game.h"

using namespace DirectX;
using namespace SimpleMath;
constexpr int slicecount = 64;
constexpr int stackcount = 64;

SphereComponent::SphereComponent(Game* game, float radius, int sliceCount, int stackCount, const wchar_t* diffuseTextureName):TriangleComponent(game)
{
	textureFileName = diffuseTextureName;

	Point topPoint({ Vector4(0.0f, radius, 0.0f, 1.0f), Vector4(0.0f, 0.0f, 0.0f, 0.0f) });
	Point bottomPoint({ Vector4(0.0f, -radius, 0.0f, 1.0f), Vector4(0.0f, 1.0f, 0.0f, 0.0f) });

	
	points.push_back(topPoint);
	points.push_back(topPoint);

	const float phiStep = XM_PI / static_cast<float>(stackCount);
	const float thetaStep = XM_2PI / static_cast<float>(sliceCount);

	for (int i = 1; i <= stackCount - 1; ++i)
	{
		const float phi = static_cast<float>(i) * phiStep;

		for (int j = 0; j <= sliceCount; ++j)
		{
			const float theta = static_cast<float>(j) * thetaStep;
			Point p;
			p.Pos.x = radius * sinf(phi) * cosf(theta);
			p.Pos.y = radius * cosf(phi);
			p.Pos.z = radius * sinf(phi) * sinf(theta);
			p.Pos.w = 1.0f;
			p.TexturePos.x = theta / XM_2PI;
			p.TexturePos.y = phi / XM_PI;
			points.push_back(p);
		}
	}

	points.push_back(bottomPoint);

	for (int i = 1; i <= sliceCount; ++i)
	{
		
		indeces.push_back(0);
		indeces.push_back(i + 1);
		indeces.push_back(i);
	}

	int baseIndex = 1;
	const int ringVertexCount = sliceCount + 1;
	for (int i = 0; i < stackCount - 2; ++i)
	{
		for (int j = 0; j < sliceCount; ++j)
		{
			indeces.push_back(baseIndex + i * ringVertexCount + j);
			indeces.push_back(baseIndex + i * ringVertexCount + j + 1);
			indeces.push_back(baseIndex + (i + 1) * ringVertexCount + j);

			indeces.push_back(baseIndex + (i + 1) * ringVertexCount + j);
			indeces.push_back(baseIndex + i * ringVertexCount + j + 1);
			indeces.push_back(baseIndex + (i + 1) * ringVertexCount + j + 1);
		}
	}

	const int southPoleIndex = points.size() - 1;

	baseIndex = southPoleIndex - ringVertexCount;

	for (int i = 0; i < sliceCount; ++i)
	{
		indeces.push_back(southPoleIndex);
		indeces.push_back(baseIndex + i);
		indeces.push_back(baseIndex + i + 1);
	}
}

SphereComponent::~SphereComponent()
{
}

void SphereComponent::DestroyResources()
{
	layout->Release();
	pixelShader->Release();
	pixelShaderByteCode->Release();
	rastState->Release();
	vertexShader->Release();
	vertexShaderByteCode->Release();
	vertexBuffer->Release();
	indexBuffer->Release();
}

void SphereComponent::Draw()
{
	game->Context->RSSetState(rastState);

	D3D11_VIEWPORT viewport = {};
	viewport.Width = static_cast<float>(game->Display->ClientWidth);
	viewport.Height = static_cast<float>(game->Display->ClientHeight);
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.MinDepth = 0;
	viewport.MaxDepth = 1.0f;

	game->Context->RSSetViewports(1, &viewport);

	game->Context->IASetInputLayout(layout);
	game->Context->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	game->Context->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);
	game->Context->IASetVertexBuffers(0, 1, &vertexBuffer, strides, offsets);
	game->Context->VSSetShader(vertexShader, nullptr, 0);
	game->Context->VSSetConstantBuffers(0, 1, &constBuffer);
	game->Context->PSSetShader(pixelShader, nullptr, 0);

	game->Context->DrawIndexed(indeces.size(), 0, 0);
}

void SphereComponent::Initialize()
{
	ID3DBlob* errorVertexCode = nullptr;
	auto res = D3DCompileFromFile(L"./Shaders/SphereShader.hlsl",
		nullptr /*macros*/,
		nullptr /*include*/,
		"VSMain",
		"vs_5_0",
		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION,
		0,
		&vertexShaderByteCode,
		&errorVertexCode);

	if (FAILED(res)) {
		// If the shader failed to compile it should have written something to the error message.
		if (errorVertexCode) {
			char* compileErrors = (char*)(errorVertexCode->GetBufferPointer());

			std::cout << compileErrors << std::endl;
		}
		// If there was  nothing in the error message then it simply could not find the shader file itself.
		else
		{
			MessageBox(game->Display->hWnd, L"SphereShader.hlsl", L"Missing Shader File", MB_OK);
		}

		return;
	}

	D3D_SHADER_MACRO Shader_Macros[] = { "TEST", "1", "TCOLOR", "float4(0.0f, 1.0f, 0.0f, 1.0f)", nullptr, nullptr };

	ID3DBlob* errorPixelCode;
	res = D3DCompileFromFile(L"./Shaders/SphereShader.hlsl",
		Shader_Macros /*macros*/,
		nullptr /*include*/,
		"PSMain",
		"ps_5_0",
		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION,
		0,
		&pixelShaderByteCode,
		&errorPixelCode);

	game->Device->CreateVertexShader(
		vertexShaderByteCode->GetBufferPointer(),
		vertexShaderByteCode->GetBufferSize(),
		nullptr, &vertexShader);

	game->Device->CreatePixelShader(
		pixelShaderByteCode->GetBufferPointer(),
		pixelShaderByteCode->GetBufferSize(),
		nullptr, &pixelShader);

	D3D11_INPUT_ELEMENT_DESC inputElements[] = {
		D3D11_INPUT_ELEMENT_DESC {
			"POSITION",
			0,
			DXGI_FORMAT_R32G32B32A32_FLOAT,
			0,
			0,
			D3D11_INPUT_PER_VERTEX_DATA,
			0},
		D3D11_INPUT_ELEMENT_DESC {
			"COLOR",
			0,
			DXGI_FORMAT_R32G32B32A32_FLOAT,
			0,
			D3D11_APPEND_ALIGNED_ELEMENT,
			D3D11_INPUT_PER_VERTEX_DATA,
			0}
	};

	game->Device->CreateInputLayout(
		inputElements,
		2,
		vertexShaderByteCode->GetBufferPointer(),
		vertexShaderByteCode->GetBufferSize(),
		&layout);

	D3D11_BUFFER_DESC vertexBufDesc = {};
	vertexBufDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufDesc.CPUAccessFlags = 0;
	vertexBufDesc.MiscFlags = 0;
	vertexBufDesc.StructureByteStride = 0;
	vertexBufDesc.ByteWidth = sizeof(Point) * points.size();

	D3D11_SUBRESOURCE_DATA vertexData = {};
	vertexData.pSysMem = points.data();
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	game->Device->CreateBuffer(&vertexBufDesc, &vertexData, &vertexBuffer);


	D3D11_BUFFER_DESC indexBufDesc = {};
	indexBufDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufDesc.CPUAccessFlags = 0;
	indexBufDesc.MiscFlags = 0;
	indexBufDesc.StructureByteStride = 0;
	indexBufDesc.ByteWidth = sizeof(int) * indeces.size();

	D3D11_SUBRESOURCE_DATA indexData = {};
	indexData.pSysMem = indeces.data();
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	game->Device->CreateBuffer(&indexBufDesc, &indexData, &indexBuffer);

	strides[0] = 32;
	offsets[0] = 0;

	D3D11_BUFFER_DESC constBufDesc = {};
	constBufDesc.Usage = D3D11_USAGE_DEFAULT;
	constBufDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	constBufDesc.CPUAccessFlags = 0;
	constBufDesc.MiscFlags = 0;
	constBufDesc.StructureByteStride = 0;
	constBufDesc.ByteWidth = sizeof(Matrix);

	game->Device->CreateBuffer(&constBufDesc, nullptr, &constBuffer);

	CD3D11_RASTERIZER_DESC rastDesc = {};
	rastDesc.CullMode = D3D11_CULL_BACK;
	rastDesc.FrontCounterClockwise = false;
	rastDesc.FillMode = D3D11_FILL_SOLID;
	res = game->Device->CreateRasterizerState(&rastDesc, &rastState);
}

void SphereComponent::Update()
{
}

void SphereComponent::Reload()
{
}