#include "Dxlib.h"
#include "Player.h"
#include "PadInput.h"

#define FLOOR 400 //床（仮）

#define MAX_SPEED 250		//最高速度と最低速度の差を調整する用
#define MAX_SPEED_LAND 50	//最高速度と最低速度の差を調整する用（地面）
#define MAX_JUMP 10			//最大連打数
#define JUMP_INTERVAL 40	//ジャンプボタン連打間隔
#define FALL_SPPED 0.002	//最高落下速度
#define MOVE_SPPED 0.005	//最高上昇速度
#define RISE_SPPED 0.01		//最高上昇速度

#define LAND_SPEED 0.02	//最高移動速度（地面）

Player::Player()
{
	player_state = IDOL;
	x = 0;
	y = 0;
	acs_left = 0;
	acs_right = 0;
	acs_up = 0;
	acs_down = 0;
	land_acs_left = 0;
	land_acs_right = 0;
	jump_int = 0;
	jump_combo = 0;
	frame = 0;
	ref_y = 0;

	b_x1 = 300;
	b_y1 = 300;
	b_x2 = 301;
	b_y2 = 480;

	b_x3 = 400;
	b_y3 = 300;
	b_x4 = 401;
	b_y4 = 480;
	ref_once1 = FALSE;
	ref_once2 = FALSE;
}

Player::~Player()
{

}

void Player::Update()
{
	//落下(床と触れていない事を検知する)
	if (y < FLOOR)
	{
		player_state = FLY_RIGHT;

		//落下し続ける程下に加速
		if (acs_down < MAX_SPEED)
		{
			acs_down++;
		}


	}
	else
	{
		jump_combo = 0;
		acs_down = 0;
		acs_up = 0;
		if (acs_left > 0)
		{
			acs_left--;
		}
		else
		{
			acs_left = 0;
		}
		if (acs_right > 0)
		{
			acs_right--;
		}
		else
		{
			acs_right = 0;
		}
		ref_y = 0;
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
				acs_right += 2;
			}

		}
		//地面と接しているなら
		else
		{			
			player_state = WALK_RIGHT;
			if (land_acs_right < MAX_SPEED_LAND)
			{
				land_acs_right++;
			}
		}

	}
	else
	{
		if (acs_right > 0)
		{
			if (frame % 10 == 0)
			{
			acs_right--;
			}
		}
		if (land_acs_right > 0)
		{
			land_acs_right--;
		}
	}

	//左入力を検知
	if (PAD_INPUT::GetLStick().ThumbX < -10000)
	{
		//浮いているなら加速処理＆浮いていないなら慣性なし移動
		//(ここで地面との当たり判定を取得してきてstateを変える)
		if (y < FLOOR)
		{
			player_state = FLY_LEFT;
			if (acs_left < MAX_SPEED) 
			{
				acs_left += 2;
			}

		}
		else
		{
			player_state = WALK_LEFT;
			if (land_acs_left < MAX_SPEED_LAND)
			{
				land_acs_left++;
			}
		}
	
	}
	else
	{
		if (acs_left > 0)
		{
			if (frame % 10 == 0)
			{
				acs_left--;
			}
		}
		if (land_acs_left > 0)
		{
			land_acs_left--;
		}
	}

	//ジャンプ
	if (PAD_INPUT::OnPressed(XINPUT_BUTTON_A))
	{
		if (acs_right > 0)
		{
			acs_right--;
		}
		if (acs_left > 0)
		{
			acs_left--;
		}

		if (jump_int == 0)
		{
			jump_int = JUMP_INTERVAL;
			//Aを押せば押すほど上加速度が上がる
			if (jump_combo < MAX_JUMP)
			{
			if (jump_combo == 0)
			{
				jump_combo += 5;
				}
				jump_combo++;
			}
			acs_up += jump_combo * 8;
			if (PAD_INPUT::GetLStick().ThumbX < -10000)
			{
				if (acs_left < MAX_SPEED)
				{
					acs_left += 10;
				}
			}
			if (PAD_INPUT::GetLStick().ThumbX > 10000)
			{
				if (acs_right < MAX_SPEED)
				{
					acs_right += 10;
				}
			}
		}
		
	}
	else
	{
		if (acs_up > 0)
		{
			acs_up--;
		}
	}

	//ジャンプ連打数を減らす
	if (jump_combo > 0)
	{
		if (frame % 120 == 0)
		{
			jump_combo--;
		}
	}

	//ジャンプ間隔管理
	if (jump_int > 0)
	{
		jump_int--;
	}

	//移動
	x = x - (acs_left * MOVE_SPPED) + (acs_right * MOVE_SPPED) + (land_acs_right * LAND_SPEED) - (land_acs_left * LAND_SPEED);
	y = y - (acs_up* RISE_SPPED) + (acs_down + ref_y) * FALL_SPPED;

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
		ref_y = acs_up * 0.05;
		acs_up -= 200;
	}
	if (ref_y > 0)
	{
		ref_y--;
	}

	//フレームを計測する(10秒ごとにリセット)
	if (++frame > 600)
	{
		frame = 0;
	}

	//左から右反射実験
	if ((x < b_x2) && (x + PLAYER_SIZE > b_x1) && (y < b_y2) && (y + PLAYER_SIZE > b_y1))
	{
		land_acs_right = 0;
		if (ref_once1 == FALSE)
		{
			acs_left = acs_right * 0.8;
			acs_right = 0;
			ref_once1 = TRUE;
		}
	}
	else
	{
		ref_once1 = FALSE;
	}
	//右から左反射実験
	if ((x < b_x4) && (x + PLAYER_SIZE > b_x3) && (y < b_y4) && (y + PLAYER_SIZE > b_y3))
	{
		land_acs_left = 0;
		if (ref_once2 == FALSE)
		{
			acs_right = acs_left * 0.8;
			acs_left = 0;
			ref_once2 = TRUE;
		}
	}
	else
	{
		ref_once2 = FALSE;
	}
}

void Player::Draw()const
{
	DrawBox(x, y, x + PLAYER_SIZE, y + PLAYER_SIZE, 0xff0000, TRUE);
	DrawBox(b_x1, b_y1, b_x2, b_y2, 0xffff00, TRUE);
	DrawBox(b_x3, b_y3, b_x4, b_y4, 0xff00ff, TRUE);
	DrawFormatString(0, 20, 0x00ff00, "%d", player_state);
	DrawFormatString(0, 40, 0x00ff00, "left:%d", acs_left);
	DrawFormatString(0, 60, 0x00ff00, "right:%d", acs_right);

}