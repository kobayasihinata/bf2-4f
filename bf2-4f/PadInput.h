#pragma once
#include"DxLib.h"

#define BUTTONS 16
#define MARGIN 32767*0.25

//スティック
struct Stick
{
	short ThumbX;	//横軸値
	short ThumbY;	//縦軸値
};

class PAD_INPUT
{
private:
	static char NowKey[BUTTONS]; //今回の入力キー
	static char OldKey[BUTTONS]; //前回の入力キー
	static XINPUT_STATE Input; //パッド
	static Stick Rstick; //右スティック
	static Stick Lstick; //左スティック
private:
	//コンストラクタ
	PAD_INPUT() = default;
public:
	//パッド情報の更新
	static void UpdateKey()
	{
		// 入力キー取得
		GetJoypadXInputState(DX_INPUT_KEY_PAD1, &Input);

		for (int i = 0; i < BUTTONS; i++)
		{
			OldKey[i] = NowKey[i];
			NowKey[i] = Input.Buttons[i];
		}

		//右スティック
		Rstick.ThumbX = Input.ThumbRX;
		Rstick.ThumbY = Input.ThumbRY;

		//左スティック
		Lstick.ThumbX = Input.ThumbLX;
		Lstick.ThumbY = Input.ThumbLY;
	}

	//ボタンを押された瞬間
	static bool OnButton(int button)
	{
		bool ret = (NowKey[button] == 1 && OldKey[button] == 0);
		return ret;
	}

	//ボタンを押してる間
	static bool OnPressed(int button)
	{
		bool ret = (NowKey[button] == 1);
		return ret;
	}

	//ボタンを離した瞬間
	static bool OnRelease(int button)
	{
		bool ret = (NowKey[button] == 1 && OldKey[button] == 0);
		return ret;
	}

	//右スティックの取得
	static Stick GetRStick()
	{
		return Rstick;
	}

	//左スティックの取得
	static Stick GetLStick()
	{
		return Lstick;
	}
};

