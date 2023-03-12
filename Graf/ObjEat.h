#pragma once
#include "MeshRenderComponent.h"
class ObjEat: public MeshRenderComponent
{
public:
	ObjEat(Game* g, std::string fileNameModel, const wchar_t* fileNameTexture, float Mass, DirectX::SimpleMath::Vector3 collOffset);
	DirectX::BoundingSphere collision;
	DirectX::SimpleMath::Vector3 originCollisionOffset;
	DirectX::SimpleMath::Matrix RelativeTransform;
	float MassObj;
	void Update() override;
};

