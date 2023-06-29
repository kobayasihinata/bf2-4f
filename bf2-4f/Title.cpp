#include "Dxlib.h"
#include "Title.h"

Title::Title()
{

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
	DrawString(430, 330, "ƒ^ƒCƒgƒ‹", 0xff0000);
}