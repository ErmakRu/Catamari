#include "QuadComponent.h"
#include "Game.h"

using namespace DirectX;

CD3D11_RASTERIZER_DESC QuadComponent::CreateRasterizerStateDesc()
{
	CD3D11_RASTERIZER_DESC rastDesc = TriangleComponent::CreateRasterizerStateDesc();
	rastDesc.CullMode = D3D11_CULL_NONE;
	return rastDesc;
}

void QuadComponent::ProcessNode(aiNode* node, const aiScene* scene)
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

void QuadComponent::ProcessMesh(aiMesh* mesh, const aiScene* scene)
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

QuadComponent::QuadComponent(Game* g, const wchar_t* diffuseTextureName) : TriangleComponent(g)
{
	textureFileName = diffuseTextureName;

	points.push_back({ Vector4(0.5f, 0.5f, 0.0f, 1.0f),	Vector4(64.0f, 64.0f, 0.0f, 0.0f) });
	points.push_back({ Vector4(-0.5f, -0.5f, 0.0f, 1.0f),Vector4(0.0f, 0.0f, 0.0f, 0.0f) });
	points.push_back({ Vector4(0.5f, -0.5f, 0.0f, 1.0f), Vector4(0.0f, 64.0f, 0.0f, 0.0f) });
	points.push_back({ Vector4(-0.5f, 0.5f, 0.0f, 1.0f), Vector4(64.0f, 0.0f, 0.0f, 0.0f) });

	indeces = { 0,1,2, 1,0,3 };
}
void QuadComponent::Initialize()
{
	Assimp::Importer importer;

	const aiScene* pScene = importer.ReadFile(fNameModel.c_str(), aiProcess_Triangulate | aiProcess_ConvertToLeftHanded);

	
	ProcessNode(pScene->mRootNode, pScene);

	TriangleComponent::Initialize();
}
//
//QuadComponent::~QuadComponent()
//{
//}
//
//void QuadComponent::DestroyResources()
//{
//	layout->Release();
//	pixelShader->Release();
//	pixelShaderByteCode->Release();
//	rastState->Release();
//	vertexShader->Release();
//	vertexShaderByteCode->Release();
//	vertexBuffer->Release();
//	indexBuffer->Release();
//}
//
//void QuadComponent::Draw()
//{
//	game->Context->RSSetState(rastState);
//
//	D3D11_VIEWPORT viewport = {};
//	viewport.Width = static_cast<float>(game->Display->ClientWidth);
//	viewport.Height = static_cast<float>(game->Display->ClientHeight);
//	viewport.TopLeftX = 0;
//	viewport.TopLeftY = 0;
//	viewport.MinDepth = 0;
//	viewport.MaxDepth = 1.0f;
//
//	game->Context->RSSetViewports(1, &viewport);
//
//	game->Context->IASetInputLayout(layout);
//	game->Context->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
//	game->Context->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);
//	game->Context->IASetVertexBuffers(0, 1, &vertexBuffer, strides, offsets);
//	game->Context->VSSetShader(vertexShader, nullptr, 0);
//	game->Context->VSSetConstantBuffers(0, 1, &constBuffer);
//	game->Context->PSSetShader(pixelShader, nullptr, 0);
//
//	game->Context->DrawIndexed(indeces.size(), 0, 0);
//}
//
//void QuadComponent::Initialize()
//{
//	ID3DBlob* errorVertexCode = nullptr;
//	auto res = D3DCompileFromFile(L"./Shaders/QuadShader.hlsl",
//		nullptr /*macros*/,
//		nullptr /*include*/,
//		"VSMain",
//		"vs_5_0",
//		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION,
//		0,
//		&vertexShaderByteCode,
//		&errorVertexCode);
//
//	if (FAILED(res)) {
//		// If the shader failed to compile it should have written something to the error message.
//		if (errorVertexCode) {
//			char* compileErrors = (char*)(errorVertexCode->GetBufferPointer());
//
//			std::cout << compileErrors << std::endl;
//		}
//		// If there was  nothing in the error message then it simply could not find the shader file itself.
//		else
//		{
//			MessageBox(game->Display->hWnd, L"QuadShader.hlsl", L"Missing Shader File", MB_OK);
//		}
//
//		return;
//	}
//
//	D3D_SHADER_MACRO Shader_Macros[] = { "TEST", "1", "TCOLOR", "float4(0.0f, 0.0f, 0.0f, 1.0f)", nullptr, nullptr };
//
//	ID3DBlob* errorPixelCode;
//	res = D3DCompileFromFile(L"./Shaders/QuadShader.hlsl",
//		Shader_Macros /*macros*/,
//		nullptr /*include*/,
//		"PSMain",
//		"ps_5_0",
//		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION,
//		0,
//		&pixelShaderByteCode,
//		&errorPixelCode);
//
//	game->Device->CreateVertexShader(
//		vertexShaderByteCode->GetBufferPointer(),
//		vertexShaderByteCode->GetBufferSize(),
//		nullptr, &vertexShader);
//
//	game->Device->CreatePixelShader(
//		pixelShaderByteCode->GetBufferPointer(),
//		pixelShaderByteCode->GetBufferSize(),
//		nullptr, &pixelShader);
//
//	D3D11_INPUT_ELEMENT_DESC inputElements[] = {
//		D3D11_INPUT_ELEMENT_DESC {
//			"POSITION",
//			0,
//			DXGI_FORMAT_R32G32B32A32_FLOAT,
//			0,
//			0,
//			D3D11_INPUT_PER_VERTEX_DATA,
//			0},
//		D3D11_INPUT_ELEMENT_DESC {
//			"COLOR",
//			0,
//			DXGI_FORMAT_R32G32B32A32_FLOAT,
//			0,
//			D3D11_APPEND_ALIGNED_ELEMENT,
//			D3D11_INPUT_PER_VERTEX_DATA,
//			0}
//	};
//
//	game->Device->CreateInputLayout(
//		inputElements,
//		2,
//		vertexShaderByteCode->GetBufferPointer(),
//		vertexShaderByteCode->GetBufferSize(),
//		&layout);
//
//	D3D11_BUFFER_DESC vertexBufDesc = {};
//	vertexBufDesc.Usage = D3D11_USAGE_DEFAULT;
//	vertexBufDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
//	vertexBufDesc.CPUAccessFlags = 0;
//	vertexBufDesc.MiscFlags = 0;
//	vertexBufDesc.StructureByteStride = 0;
//	vertexBufDesc.ByteWidth = sizeof(SimpleMath::Vector4) * points.size();
//
//	D3D11_SUBRESOURCE_DATA vertexData = {};
//	vertexData.pSysMem = points.data();
//	vertexData.SysMemPitch = 0;
//	vertexData.SysMemSlicePitch = 0;
//
//	game->Device->CreateBuffer(&vertexBufDesc, &vertexData, &vertexBuffer);
//
//
//	D3D11_BUFFER_DESC indexBufDesc = {};
//	indexBufDesc.Usage = D3D11_USAGE_DEFAULT;
//	indexBufDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
//	indexBufDesc.CPUAccessFlags = 0;
//	indexBufDesc.MiscFlags = 0;
//	indexBufDesc.StructureByteStride = 0;
//	indexBufDesc.ByteWidth = sizeof(int) * indeces.size();
//
//	D3D11_SUBRESOURCE_DATA indexData = {};
//	indexData.pSysMem = indeces.data();
//	indexData.SysMemPitch = 0;
//	indexData.SysMemSlicePitch = 0;
//
//	game->Device->CreateBuffer(&indexBufDesc, &indexData, &indexBuffer);
//
//	strides[0] = 32;
//	offsets[0] = 0;
//
//	D3D11_BUFFER_DESC constBufDesc = {};
//	constBufDesc.Usage = D3D11_USAGE_DEFAULT;
//	constBufDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
//	constBufDesc.CPUAccessFlags = 0;
//	constBufDesc.MiscFlags = 0;
//	constBufDesc.StructureByteStride = 0;
//	constBufDesc.ByteWidth = sizeof(SimpleMath::Vector4);
//
//	game->Device->CreateBuffer(&constBufDesc, nullptr, &constBuffer);
//
//	CD3D11_RASTERIZER_DESC rastDesc = {};
//	rastDesc.CullMode = D3D11_CULL_NONE;
//	rastDesc.FillMode = D3D11_FILL_SOLID;
//
//	res = game->Device->CreateRasterizerState(&rastDesc, &rastState);
//}
//
//void QuadComponent::Update()
//{
//	game->Context->UpdateSubresource(constBuffer, 0, 0, &offset, 0, 0);
//}
//
//void QuadComponent::Reload()
//{
//}
//
//void QuadComponent::SetPosition(float x, float y)
//{
//	offset.x = x;
//	offset.y = y;
//}
//
//void QuadComponent::SetPosition(DirectX::SimpleMath::Vector2 pos)
//{
//	offset.x = pos.x;
//	offset.y = pos.y;
//}
//
//void QuadComponent::SetY(float y)
//{
//	offset.y = y;
//}
//
//void QuadComponent::SetX(float x)
//{
//	offset.x = x;
//}
//
//float QuadComponent::GetX() const
//{
//	return offset.x;
//}
//
//float QuadComponent::GetY() const
//{
//	return offset.y;
//}
//
//DirectX::SimpleMath::Vector2 QuadComponent::GetPosition() const
//{
//	return DirectX::SimpleMath::Vector2(offset.x, offset.y); //add ballPos
//}
