#include "StageFloor.h"
#include"DxLib.h"

StageFloor::StageFloor(int x, int y, int height, int width,int shift)
{
	location.x = (float)x;
	location.y = (float)y + shift;
	area.height = (float)height;
	area.width = (float)width;
	this->shift = shift;

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

void StageFloor::DrawLandLeft()
{
	DrawGraphF(location.x, location.y - shift, landleft, TRUE);
	DrawBox(location.x, location.y, location.x + area.width, location.y + area.height, 0x00ff00, false);
}

void StageFloor::DrawLandLeft2()
{
	DrawGraphF(location.x, location.y - shift, landleft2, TRUE);
}

void StageFloor::DrawLandRight()
{
	DrawGraphF(location.x, location.y - shift, landright, TRUE);
	DrawBox(location.x, location.y, location.x + area.width, location.y + area.height, 0x00ff00, false);
}

void StageFloor::DrawLandRight2()
{
	DrawGraphF(location.x, location.y - shift, landright2, TRUE);
}

void StageFloor::DrawFooting1()
{
	DrawGraphF(location.x, location.y - shift, footing1, TRUE);
	DrawBox(location.x, location.y, location.x + area.width, location.y + area.height, 0x00ff00, false);
}

void StageFloor::DrawFooting2()
{
	DrawGraphF(location.x, location.y, footing2, TRUE);
	DrawBox(location.x, location.y, location.x + area.width, location.y + area.height, 0x00ff00, false);
}

void StageFloor::DrawFooting3()
{
	DrawGraphF(location.x, location.y, footing3, TRUE);
	DrawBox(location.x, location.y, location.x + area.width, location.y + area.height, 0x00ff00, false);
}

void StageFloor::DrawFooting5()
{
	DrawGraphF(location.x, location.y, footing5, TRUE);
	DrawBox(location.x, location.y, location.x + area.width, location.y + area.height, 0x00ff00, false);
}

void StageFloor::DrawFooting6()
{
	DrawGraphF(location.x, location.y, footing6, TRUE);
	DrawBox(location.x, location.y, location.x + area.width, location.y + area.height, 0x00ff00, false);
}