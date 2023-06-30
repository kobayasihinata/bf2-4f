#include "Stage.h"
#include <math.h>

#include "DxLib.h"

Stage::Stage()
{

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