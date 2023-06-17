#include "Dxlib.h"
#include "Player.h"
#include "PadInput.h"

#define FLOOR 400 //床（仮）
#define MAX_SPEED 100 //最高速度

Player::Player()
{
	player_state = IDOL;
	location.x = 0;
	location.y = 0;
	area.height = PLAYER_SIZE;
	area.width = PLAYER_SIZE;
	acs_left = 0;
	acs_right = 0;
	acs_up = 0;
	acs_down = 0;
}

Player::~Player()
{

}

void Player::Update()
{
	//落下 もしくは上昇
	if (location.y < FLOOR)
	{
		player_state = FLY_RIGHT;
		if (acs_down < 100)
		{
			acs_down++;
		}
		location.y += acs_down/20;
		location.y -= acs_up;
	}
	else
	{
		acs_down = 0;
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
	location.x = location.x - (acs_left/20) + (acs_right/20);
	location.y = location.y - acs_up;

}

void Player::Draw()const
{
	BoxCollider::Draw();
	DrawBox(location.x - area.width / 2, location.y - area.height / 2, location.x + PLAYER_SIZE / 2, location.y + PLAYER_SIZE / 2, 0xff0000, TRUE);
	DrawFormatString(0, 50, 0x0000ff, "%d", PAD_INPUT::GetLStick().ThumbX);
}