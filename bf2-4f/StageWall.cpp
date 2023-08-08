#include "StageWall.h"
#include"DxLib.h"

StageWall::StageWall(int x, int y, int height, int width, int shift)
{
	location.x = (float)x;
	location.y = (float)y + shift;
	area.height = (float)height;
	area.width = (float)width;
	this->shift = shift;
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

void StageWall::DrawFooting4()
{
	DrawGraphF(location.x, location.y - shift, footing4, TRUE);
}

void StageWall::DrawFooting7()
{
	DrawGraphF(location.x, location.y - shift, footing7, TRUE);
}

void StageWall::DrawFooting8()
{
	DrawGraphF(location.x, location.y - shift, footing8, TRUE);
}