#include "StageFloor.h"
#include"DxLib.h"

StageFloor::StageFloor(int x, int y, int height, int width,int margin)
{
	location.x = (float)x;
	location.y = (float)y + margin;
	area.height = (float)height;
	area.width = (float)width;
	this->margin = margin;

	landleft = LoadGraph("images/Stage/Stage_Land_Left01.png");
	landright = LoadGraph("images/Stage/Stage_Land_Right01.png");

	footing1 = LoadGraph("images/Stage/Stage_Footing01.png");
	footing2 = LoadGraph("images/Stage/Stage_Footing02.png");
	footing3 = LoadGraph("images/Stage/Stage_Footing03.png");
	footing4 = LoadGraph("images/Stage/Stage_Footing04.png");
	footing5 = LoadGraph("images/Stage/Stage_Footing05.png");
}

StageFloor::~StageFloor()
{
	DeleteGraph(landleft);
	DeleteGraph(landright);

	DeleteGraph(footing1);
	DeleteGraph(footing2);
	DeleteGraph(footing3);
	DeleteGraph(footing4);
	DeleteGraph(footing5);
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
	DrawGraphF(location.x, location.y - margin, landleft, TRUE);
}

void StageFloor::DrawLandRight()
{
	DrawGraphF(location.x, location.y - margin, landright, TRUE);
}

void StageFloor::DrawFooting1()
{
	DrawGraphF(location.x, location.y - margin, footing1, TRUE);
}

void StageFloor::DrawFooting2()
{
	DrawGraphF(location.x, location.y, footing2, TRUE);
}

void StageFloor::DrawFooting3()
{
	DrawGraphF(location.x, location.y, footing3, TRUE);
}

void StageFloor::DrawFooting4()
{
	DrawGraphF(location.x, location.y, footing4, TRUE);
}

void StageFloor::DrawFooting5()
{
	DrawGraphF(location.x, location.y, footing5, TRUE);
}