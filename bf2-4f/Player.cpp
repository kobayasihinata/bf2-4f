#include "Dxlib.h"
#include "Player.h"
#include "PadInput.h"

#define FLOOR 400 //床（仮）
#define MAX_SPEED 50 //最高速度

Player::Player()
{
	x = 0;
	y = 0;
	acs_left = 0;
	acs_right = 0;
	acs_up = 0;
}

Player::~Player()
{

}

void Player::Update()
{
	//落下
	if (y < FLOOR)
	{
		y = (++y) - acs_up;
	}

	//右へ加速
	if (PAD_INPUT::GetLStick().ThumbX>10000)
	{
		if (acs_right < MAX_SPEED)
		{		
			acs_right++;
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
		if (acs_left < MAX_SPEED)
		{
			acs_left++;
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
		acs_up += 10;
	}
	else
	{
		if (acs_up > 0)
		{
			acs_up--;
		}
	}
	//移動
	x = x - (acs_left/10) + (acs_right/10);
	y = y - acs_up;

}

void Player::Draw()const
{
	DrawBox(x, y, x + PLAYER_SIZE, y + PLAYER_SIZE, 0xff0000, TRUE);
	DrawFormatString(0, 50, 0x0000ff, "%d", PAD_INPUT::GetLStick().ThumbX);
}