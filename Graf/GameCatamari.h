#pragma once
#include "Game.h"
#include "CameraController.h"

class ObjEat;
class CatamariBall;

class GameCatamari: public Game
{
protected:
    CatamariBall* ball;
    CameraController* CameraController{};
public:
    std::vector<ObjEat*> Objects{};
    GameCatamari();
    void Update() override;
};

