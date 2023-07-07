#include "Dxlib.h"
#include "Pause.h"
#include"PadInput.h"

Pouse::Pouse()
{
	DrawMenu = false;
}

Pouse::~Pouse()
{

}

void Pouse::Update()
{
	//ポーズフラグ切り替え処理
	if (DrawMenu == true) {

	}
	
}

void Pouse::Draw()const
{
	if (DrawMenu == true) {
		DrawString(100, 100, "pouse now", 0xffffff);
	}
	
}
bool Pouse::PouseMenu() {
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_START)) {
		DrawMenu = !DrawMenu;
	}
	if (!DrawMenu) {
		Update();
	}
	return DrawMenu;
}

