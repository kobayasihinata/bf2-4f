#include "Dxlib.h"
#include "Player.h"
#include "PadInput.h"

#define FLOOR 400 //���i���j

#define MAX_SPEED 1000 //�ō����x
#define MAX_JUMP 10	   //�ő�㏸���x

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
	//���� �������͏㏸
	if (y < FLOOR)
	{
		player_state = FLY_RIGHT;

		//����������������ɉ���
		if (acs_down < MAX_SPEED)
		{
			acs_down++;
		}

		//���~����
		y += acs_down * 0.02;

		//�㏸����
		y -= acs_up * 0.02;
	}
	else
	{
		jump_combo = 0;
		acs_down = 0;
		acs_up = 0;
		player_state = IDOL;
	}

	//�E���͂����m
	if (PAD_INPUT::GetLStick().ThumbX>10000)
	{
		//�����Ă���Ȃ���������������Ă��Ȃ��Ȃ犵���Ȃ��ړ�
		//(�����Œn�ʂƂ̓����蔻����擾���Ă���state��ς���)
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

	//���։���
	if (PAD_INPUT::GetLStick().ThumbX < -10000)
	{
		//�����Ă���Ȃ���������������Ă��Ȃ��Ȃ犵���Ȃ��ړ�
		//(�����Œn�ʂƂ̓����蔻����擾���Ă���state��ς���)
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

	//�W�����v
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_A))
	{
		//A�������Ή����قǏ�����x���オ��
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

	//�ړ�
	x = x - (acs_left*0.01) + (acs_right*0.01);
	y = y - (acs_up*0.01);

	//��ʒ[�ɍs���ƃe���|�[�g
	if (x < 0 - PLAYER_SIZE)
	{
		x = SCREEN_WIDTH + PLAYER_SIZE;
	}
	if (x > SCREEN_WIDTH + PLAYER_SIZE)
	{
		x = 0 - PLAYER_SIZE;
	}

	//��ʏ�ɓ�����ƒ��˕Ԃ�
	if (y < 0)
	{

	}
}

void Player::Draw()const
{
	DrawBox(x, y, x + PLAYER_SIZE, y + PLAYER_SIZE, 0xff0000, TRUE);
	DrawFormatString(0, 20, 0x00ff00, "%d", player_state);

}