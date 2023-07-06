#include "Dxlib.h"
#include "Pause.h"

Pouse::Pouse()
{
	DrawMenu = false;
}

Pouse::~Pouse()
{

}

AbstractScene* Pouse::Update()
{
	

	return this;
}

void Pouse::Draw()const
{
	if (DrawMenu == true) {
		DrawString(0, 0, "É|Å[ÉY", 0xff0000);
	}
}