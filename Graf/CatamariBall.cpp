#include "CatamariBall.h"
#include "Game.h"
#include "GameCatamari.h"

void CatamariBall::UpdateSize(float absorbedSize)
{
    float tmp = sqrtf(Mass * Mass + absorbedSize * absorbedSize);
    collision.Radius = tmp;
    SetPosition(Vector3(GetPosition().x, tmp, GetPosition().z));
    rotationSpeed = 0.1f / (tmp * tmp);
    if (rotationSpeed < 0.01f)
        rotationSpeed = 0.01f;
    moveSpeed = 8.0f * sqrtf(tmp);
    Mass = tmp;
}

CatamariBall::CatamariBall(Game* game) : SphereComponent(game, 1.0f, 32, 32, L"Textures/ac.dds"), 
                                         rotationSpeed(0.15f), 
                                         moveSpeed(10.0f), 
                                         velocity(Vector3::Zero), 
                                         collision(GetPosition(), 1.0f), 
                                         Mass(1.0f)
{
    CGame = dynamic_cast<GameCatamari*>(game);
}

CatamariBall::~CatamariBall()
{
}

void CatamariBall::Initialize()
{
    SphereComponent::Initialize();
}

void CatamariBall::Draw()
{
    SphereComponent::Draw();
}

void CatamariBall::Update()
{
    collision.Center = GetPosition();

    //for (auto furn : kGame->furniture)
    //{
    //    if (collision.Intersects(furn->collision) && !furn->isPickedUp && gameSize > furn->gameSize)
    //    {
    //        furn->isPickedUp = true;
    //        furn->kb = this;
    //        furn->initRelPos = furn->GetPosition() - GetPosition();
    //        rotation.Inverse(furn->invKbRot);
    //        UpdateSize(furn->gameSize);
    //    }
    //}

    //savedRot.RotateTowards(Quaternion::Identity, rotationDrag * game->DeltaTime);
    //rotation *= savedRot;
    //velocity *= 1.0f - moveDrag * game->DeltaTime;

    //outline->SetRotation(rotation);

    //outline->Update();
    //SphereComponent::Update();

    //position += velocity * game->DeltaTime;
    //outline->SetPosition(position);
}

void CatamariBall::Reload()
{
    SphereComponent::Reload();
}

void CatamariBall::DestroyResources()
{
    SphereComponent::DestroyResources();
}

void CatamariBall::SetPosition(DirectX::SimpleMath::Vector3 p)
{
    SphereComponent::SetPosition(p);
}
