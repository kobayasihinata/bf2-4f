#include "Stage.h"
#include <math.h>

#include "DxLib.h"

Stage::Stage()
{
	landleft = LoadGraph("images/Stage/Stage_Land_Left01.png");
	landright = LoadGraph("images/Stage/Stage_Land_Right01.png");
	sea = LoadGraph("images/Stage/Stage_Sea01.png");
	footing1 = LoadGraph("images/Stage/Stage_Footing01.png");
	footing2 = LoadGraph("images/Stage/Stage_Footing02.png");
	footing3 = LoadGraph("images/Stage/Stage_Footing03.png");
	footing4 = LoadGraph("images/Stage/Stage_Footing04.png");
	footing5 = LoadGraph("images/Stage/Stage_Footing05.png");
}

Stage::~Stage()
{
	DeleteGraph(stagefloor);
	DeleteGraph(landleft);
	DeleteGraph(landright);
	DeleteGraph(sea);
	DeleteGraph(footing1);
	DeleteGraph(footing2);
	DeleteGraph(footing3);
	DeleteGraph(footing4);
	DeleteGraph(footing5);
}

AbstractScene* Stage::Update()
{
	return this;
}

void Stage::Draw() const
{
	DrawGraph(0,416,landleft, TRUE);
	DrawGraph(479,416,landright, TRUE);
	DrawGraph(159,444,sea, TRUE);
	DrawGraph(180,260,footing1, TRUE);
}