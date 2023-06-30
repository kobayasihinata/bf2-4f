#include "StageWall.h"
#include"DxLib.h"

StageWall::StageWall()
{
	location.x = 525;
	location.y = 150;
	area.height = 200;
	area.width = 20;
}

StageWall::~StageWall()
{

}

void StageWall::Update()
{

}

void StageWall::Draw()const
{
	BoxCollider::Draw();
}