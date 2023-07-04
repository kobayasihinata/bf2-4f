#include "StageFloor.h"
#include"DxLib.h"

StageFloor::StageFloor()
{
	location.x = 225;
	location.y = 200;
	area.height = 20;
	area.width = 200;
}

StageFloor::~StageFloor()
{

}

void StageFloor::Update()
{
	

}

void StageFloor::Draw()const
{
	BoxCollider::Draw();
}