#include "Dxlib.h"
#include "Title.h"

Title::Title()
{
	stagebox = new StageBox();
}

Title::~Title()
{

}

AbstractScene* Title::Update()
{
	
	return this;
}

void Title::Draw()const
{
	DrawString(0, 0, "�^�C�g��", 0xff0000);
	stagebox->Draw();
}