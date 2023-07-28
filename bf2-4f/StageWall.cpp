#include "StageWall.h"
#include"DxLib.h"

StageWall::StageWall(int x, int y, int height, int width, int shift)
{
	location.x = (float)x;
	location.y = (float)y + shift;
	area.height = (float)height;
	area.width = (float)width;
	this->shift = shift;

	footing4 = LoadGraph("images/Stage/Stage_Footing04.png");
	footing7 = LoadGraph("images/Stage/Stage_Footing07.png");
	footing8 = LoadGraph("images/Stage/Stage_Footing08.png");

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