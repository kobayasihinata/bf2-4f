#include "StageBox.h"
#include"DxLib.h"

StageFloor::StageFloor()
{
	location.x = 325;
	location.y = 300;
	area.height = 50;
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