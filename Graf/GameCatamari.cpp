#include "GameCatamari.h"

#include "ObjEat.h"
#include "QuadComponent.h"
#include "CatamariBall.h"

using namespace DirectX;
using namespace SimpleMath;

GameCatamari::GameCatamari(): Game(L"Katamari Game", 800, 800)
{
	srand(static_cast<unsigned>(time(nullptr)));
	ball = new CatamariBall(this);
	ball->SetPosition(Vector3(0.0f, 1.0f, 0.0f));
	Components.push_back(ball);

	QuadComponent* quad = new QuadComponent(this, L"Textures/Grisha.dds"); 
    quad->SetMatrix(quad->GetMatrix()*Matrix::CreateScale(Vector3::One*1000.0f)*Matrix::CreateRotationX(XM_PI/2));
    Components.push_back(quad);

    for (int i = 0; i < 10; ++i)
    {
        ObjEat* Barrel = new ObjEat(this, "Models/Barrel.obj", L"Textures/Grisha.dds", 1.5f, Vector3(0.0f, 0.8f, 0.0f));
        Barrel->SetPosition(Vector3(static_cast<float>(rand()) / RAND_MAX * 100.0f - 50.0f, 0.0f, static_cast<float>(rand()) / RAND_MAX * 100.0f - 50.0f));
        Barrel->collision.Radius = 0.8f;
        Components.push_back(Barrel);
        Objects.push_back(Barrel);
    }

   /* for (int i = 0; i < 10; ++i)
    {
        KatamariFurnitureComponent* strawberry = new KatamariFurnitureComponent(this, "Models/strawberry.obj", L"Textures/strawberry.dds", 0.4f, Vector3(0.0f, 0.5f, 0.0f));
        strawberry->SetScale(Vector3(0.1f, 0.1f, 0.1f));
        strawberry->SetPosition(Vector3(static_cast<float>(rand()) / RAND_MAX * 100.0f - 50.0f, 0.0f, static_cast<float>(rand()) / RAND_MAX * 100.0f - 50.0f));
        strawberry->collision.Radius = 0.1f;
        Components.push_back(strawberry);
        furniture.push_back(strawberry);
    }

    for (int i = 0; i < 10; ++i)
    {
        KatamariFurnitureComponent* duck = new KatamariFurnitureComponent(this, "Models/duck.obj", L"Textures/duck.dds", 1.2f, Vector3(0.0f, 1.0f, 0.0f));
        duck->SetScale(Vector3(0.02f, 0.02f, 0.02f));
        duck->SetPosition(Vector3(static_cast<float>(rand()) / RAND_MAX * 100.0f - 50.0f, 0.0f, static_cast<float>(rand()) / RAND_MAX * 100.0f - 50.0f));
        duck->collision.Radius = 0.2f;
        Components.push_back(duck);
        furniture.push_back(duck);
    }*/

    CameraController = new::CameraController(this, Camera, ball);
    InputDev->MouseMove.AddRaw(CameraController, &CameraController::OnMouseMove);
}

void GameCatamari::Update()
{
    CameraController->Update();
    Vector3 dir = Vector3::Zero;
    if (InputDev->IsKeyDown(Keys::W))
        dir += CameraController->GetForward();
    if (InputDev->IsKeyDown(Keys::S))
        dir -= CameraController->GetForward();
    if (InputDev->IsKeyDown(Keys::A))
        dir -= (CameraController->GetForward()).Cross(CameraController->GetUp());
    if (InputDev->IsKeyDown(Keys::D))
        dir += (CameraController->GetForward()).Cross(CameraController->GetUp());
    dir.y = 0;
    if (dir.Length() > 0.0f)
    {
        dir.Normalize();
        ball->SetPosition(ball->GetPosition() + dir * DeltaTime * ball->moveSpeed);
    }
    Game::Update();
}
