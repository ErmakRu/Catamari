#include "ObjEat.h"

ObjEat::ObjEat(Game* g, std::string fileNameModel, const wchar_t* fileNameTexture, float Mass, DirectX::SimpleMath::Vector3 collOffset) :
    MeshRenderComponent(g, fileNameModel, fileNameTexture), collision(GetPosition() + collOffset, Mass), originCollisionOffset(collOffset), MassObj(Mass)
{
}

void ObjEat::Update()
{ 
    if(Parent)
    {
        SetMatrix(RelativeTransform*Parent->Tranform);
    }
    MeshRenderComponent::Update();
}
