#pragma once
#include "SimpleMath.h"

using namespace DirectX;
using namespace SimpleMath;

class Game;

class GameComponent
{
public:
	Game* game;
	GameComponent(Game* g);
	virtual ~GameComponent();
	virtual void DestroyResources() = 0;
	virtual void Draw() = 0;
	virtual void Initialize() = 0;
	virtual void Reload() = 0;
	virtual void Update() = 0;
	DirectX::SimpleMath::Matrix Tranform;
	virtual void SetPosition(DirectX::SimpleMath::Vector3 Pos);
	virtual DirectX::SimpleMath::Vector3 GetPosition();
	void SetMatrix(Matrix m);
	DirectX::SimpleMath::Matrix GetMatrix();
	GameComponent* Parent;
};
