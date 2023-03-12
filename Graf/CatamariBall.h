#pragma once
#include "SphereComponent.h"

class GameCatamari;

class CatamariBall : public SphereComponent
{
protected:
	GameCatamari* CGame;
	void UpdateSize(float absorbedSize);
public:
    float rotationSpeed;
    float moveSpeed;
    DirectX::SimpleMath::Quaternion savedRot;
    DirectX::SimpleMath::Vector3 velocity;
    DirectX::BoundingSphere collision;
    float Mass;
    CatamariBall(Game* game);
    ~CatamariBall() override;
    void Initialize() override;
    void Draw() override;
    void Update() override;
    void Reload() override;
    void DestroyResources() override;
    void SetPosition(DirectX::SimpleMath::Vector3 p) override;
};

