#include "CameraController.h"
#include "Game.h"
#include "Camera.h"

using namespace DirectX;
using namespace SimpleMath;

CameraController::CameraController(Game* g, Camera* c, GameComponent* t) : game(g), camera(c), target(t),
rotation(Quaternion::Identity), radius(10.0f), sensitivityX(0.004f), sensitivityY(0.004f), isLMBActivated(true)
{
}

void CameraController::OnMouseMove(const InputDevice::MouseMoveEventArgs& args)
{
    if (game->InputDev->IsKeyDown(Keys::LeftButton) || !isLMBActivated) //LMB for move
    {
        Vector3 tmp = Vector3::Transform(Vector3::Right, rotation);
        if ((GetForward().y < 0 || game->InputDev->MouseOffset.y < 0) && (GetUp().y > 0.05f || game->InputDev->MouseOffset.y > 0))
            rotation *= Quaternion::CreateFromAxisAngle(tmp, sensitivityY * game->InputDev->MouseOffset.y);
        rotation *= Quaternion::CreateFromAxisAngle(Vector3::Up, -sensitivityX * game->InputDev->MouseOffset.x);
    }
    if ((radius > 5.0 || game->InputDev->MouseWheelDelta < 0) && (radius < 30.0 || game->InputDev->MouseWheelDelta > 0))
        radius -= 0.01f * game->InputDev->MouseWheelDelta;
}

void CameraController::Update()
{
    camera->LookAt(target->GetPosition() - GetForward() * radius, target->GetPosition(), Vector3::Transform(Vector3::Up, rotation));
}

Vector3 CameraController::GetForward() const
{
    return Vector3::Transform(Vector3::Forward, rotation);
}

Vector3 CameraController::GetUp() const
{
    return Vector3::Transform(Vector3::Up, rotation);
}