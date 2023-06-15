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
	DrawString(0, 0, "ƒ^ƒCƒgƒ‹", 0xff0000);
	stagebox->Draw();
}