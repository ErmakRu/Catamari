#include "GameComponent.h"
#include "Game.h"

using namespace DirectX;
using namespace SimpleMath;

GameComponent::GameComponent(Game* g) : game(g), Tranform(Matrix::Identity)
{
}

GameComponent::~GameComponent()
{
}

void GameComponent::SetPosition(DirectX::SimpleMath::Vector3 Pos)
{
	Tranform *= Matrix::CreateTranslation(-GetPosition())*Matrix::CreateTranslation(Pos);
}

DirectX::SimpleMath::Vector3 GameComponent::GetPosition()
{
	return Tranform.Translation();
}

void GameComponent::SetMatrix(Matrix m)
{
	Tranform = m;
}

DirectX::SimpleMath::Matrix GameComponent::GetMatrix()
{
	return Tranform;
}
