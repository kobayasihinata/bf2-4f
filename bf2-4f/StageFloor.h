#pragma once
#include "collider/BoxCollider.h"
class StageFloor :
    public BoxCollider
{
public:
    StageFloor();
    ~StageFloor();
    void Update();
    void Draw()const;
};

