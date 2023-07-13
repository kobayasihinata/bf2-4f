#include "Dxlib.h"
#include "Pause.h"
#include"PadInput.h"

Pause::Pause()
{
	DrawMenu = false;
}

Pause::~Pause()
{

}

void Pause::Update()
{
	//ポーズフラグ切り替え処理
	if (DrawMenu == true) {

	}
	
}

void Pause::Draw()const
{
	if (DrawMenu == true) {
		DrawString(100, 100, "pouse now", 0xffffff);
	}
	
}
bool Pause::PauseMenu() {
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_START)) {
		DrawMenu = !DrawMenu;
	}
	if (!DrawMenu) {
		Update();
	}
	return DrawMenu;
}

