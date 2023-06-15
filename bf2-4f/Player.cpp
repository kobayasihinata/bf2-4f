#include "Dxlib.h"
#include "Player.h"
#include "PadInput.h"

#define FLOOR 400 //床（仮）

#define MAX_SPEED 1000 //最高速度
#define MAX_JUMP 10	   //最大上昇強度

Player::Player()
{
	player_state = IDOL;
	x = 0;
	y = 0;
	acs_left = 0;
	acs_right = 0;
	acs_up = 0;
	acs_down = 0;
	jump_combo = 0;
}

Player::~Player()
{

}

void Player::Update()
{
	//落下 もしくは上昇
	if (y < FLOOR)
	{
		player_state = FLY_RIGHT;

		//落下し続ける程下に加速
		if (acs_down < MAX_SPEED)
		{
			acs_down++;
		}

		//下降処理
		y += acs_down * 0.02;

		//上昇処理
		y -= acs_up * 0.02;
	}
	else
	{
		jump_combo = 0;
		acs_down = 0;
		acs_up = 0;
		player_state = IDOL;
	}

	//右入力を検知
	if (PAD_INPUT::GetLStick().ThumbX>10000)
	{
		//浮いているなら加速処理＆浮いていないなら慣性なし移動
		//(ここで地面との当たり判定を取得してきてstateを変える)
		if (y < FLOOR)
		{		
			player_state = FLY_RIGHT;
			if (acs_right < MAX_SPEED)
			{
			acs_right++;
			}

		}
		else
		{
			acs_right = 0;
			player_state = WALK_RIGHT;
			x += 1.5;
		}
	}
	else
	{
		if (acs_right > 0)
		{
			acs_right--;
		}
	}

	//左へ加速
	if (PAD_INPUT::GetLStick().ThumbX < -10000)
	{
		//浮いているなら加速処理＆浮いていないなら慣性なし移動
		//(ここで地面との当たり判定を取得してきてstateを変える)
		if (y < FLOOR)
		{
			player_state = FLY_LEFT;
			if (acs_left < MAX_SPEED) 
			{
			acs_left++;
			}

		}
		else
		{
			acs_left = 0;
			player_state = WALK_LEFT;
			x-=1.5;
		}
	}
	else
	{
		if (acs_left > 0)
		{
			acs_left--;
		}
	}

	//ジャンプ
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_A))
	{
		//Aを押せば押すほど上加速度が上がる
		if (jump_combo < MAX_JUMP)
		{
			if (jump_combo == 0)
			{
				jump_combo += 5;
			}
			jump_combo++;
		}
		acs_up += jump_combo * 10;
	}
	else
	{
		if (acs_up > 0)
		{
			acs_up--;
		}
	}

	//移動
	x = x - (acs_left*0.01) + (acs_right*0.01);
	y = y - (acs_up*0.01);

	//画面端に行くとテレポート
	if (x < 0 - PLAYER_SIZE)
	{
		x = SCREEN_WIDTH + PLAYER_SIZE;
	}
	if (x > SCREEN_WIDTH + PLAYER_SIZE)
	{
		x = 0 - PLAYER_SIZE;
	}

	//画面上に当たると跳ね返る
	if (y < 0)
	{

	}
}

void Player::Draw()const
{
	DrawBox(x, y, x + PLAYER_SIZE, y + PLAYER_SIZE, 0xff0000, TRUE);
	DrawFormatString(0, 20, 0x00ff00, "%d", player_state);

}