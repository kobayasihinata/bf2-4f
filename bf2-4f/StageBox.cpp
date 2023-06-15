#include "StageBox.h"
#include"DxLib.h"

StageBox::StageBox()
{
	location.x = 325;
	location.y = 300;
	area.height = 50;
	area.width = 200;
}

StageBox::~StageBox()
{

}

void StageBox::Update()
{
	

}

void StageBox::Draw()const
{
	BoxCollider::Draw();
}