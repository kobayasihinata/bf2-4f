#include "Stage.h"
#include <math.h>

#include "DxLib.h"

Stage::Stage()
{
	stageimage = LoadGraph("images/stages/stage1.png");
}

Stage::~Stage()
{
	DeleteGraph(stageimage);
}

AbstractScene* Stage::Update()
{
	return this;
}

void Stage::Draw() const
{
	DrawGraph(0,0,stageimage, TRUE);
}