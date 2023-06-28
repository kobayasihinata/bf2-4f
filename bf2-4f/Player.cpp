#include "Dxlib.h"
#include "Player.h"
#include "PadInput.h"

#define FLOOR 400 //���i���j

#define MAX_SPEED 250		//�ō����x�ƍŒᑬ�x�̍��𒲐�����p
#define MAX_SPEED_LAND 50	//�ō����x�ƍŒᑬ�x�̍��𒲐�����p�i�n�ʁj
#define MAX_JUMP 10			//�ő�A�Ő�
#define JUMP_INTERVAL 40	//�W�����v�{�^���A�ŊԊu
#define FALL_SPPED 0.002	//�ō��������x
#define MOVE_SPPED 0.005	//�ō��㏸���x
#define RISE_SPPED 0.01		//�ō��㏸���x

#define LAND_SPEED 0.02	//�ō��ړ����x�i�n�ʁj

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
	//����(���ƐG��Ă��Ȃ��������m����)
	if (y < FLOOR)
	{
		player_state = FLY_RIGHT;

		//����������������ɉ���
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
				acs_right += 2;
			}

		}
		//�n�ʂƐڂ��Ă���Ȃ�
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

	//�����͂����m
	if (PAD_INPUT::GetLStick().ThumbX < -10000)
	{
		//�����Ă���Ȃ���������������Ă��Ȃ��Ȃ犵���Ȃ��ړ�
		//(�����Œn�ʂƂ̓����蔻����擾���Ă���state��ς���)
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

	//�W�����v
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
			//A�������Ή����قǏ�����x���オ��
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

	//�W�����v�A�Ő������炷
	if (jump_combo > 0)
	{
		if (frame % 120 == 0)
		{
			jump_combo--;
		}
	}

	//�W�����v�Ԋu�Ǘ�
	if (jump_int > 0)
	{
		jump_int--;
	}

	//�ړ�
	x = x - (acs_left * MOVE_SPPED) + (acs_right * MOVE_SPPED) + (land_acs_right * LAND_SPEED) - (land_acs_left * LAND_SPEED);
	y = y - (acs_up* RISE_SPPED) + (acs_down + ref_y) * FALL_SPPED;

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
		ref_y = acs_up * 0.05;
		acs_up -= 200;
	}
	if (ref_y > 0)
	{
		ref_y--;
	}

	//�t���[�����v������(10�b���ƂɃ��Z�b�g)
	if (++frame > 600)
	{
		frame = 0;
	}

	//������E���ˎ���
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
	//�E���獶���ˎ���
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