#include "Dxlib.h"
#include "PadInput.h"
#include "Pause.h"

Pause::Pause()
{

}

Pause::~Pause()
{

}

AbstractScene* Pause::Update()
{

	return this;
}

void Pause::Draw()const
{
	DrawString(0, 0, "É|Å[ÉYíÜ", 0xff0000);
}