#pragma once
#include "collider/BoxCollider.h"
class StageBox :
    public BoxCollider
{
public:
    StageBox();
    ~StageBox();
    void Update();
    void Draw()const;
};

