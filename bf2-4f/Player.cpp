#include "Dxlib.h"
#include "Player.h"
#include "PadInput.h"

#define SEA_SURFACE 470 //�C�ʁi���j

#define MAX_SPEED 250		//�ō����x�ƍŒᑬ�x�̍��𒲐�����p
#define MAX_SPEED_LAND 100	//�ō����x�ƍŒᑬ�x�̍��𒲐�����p�i�n�ʁj
#define MAX_JUMP 10			//�ő�A�Ő�
#define JUMP_INTERVAL 40	//�W�����v�{�^���A�ŊԊu
#define FALL_SPPED 0.002f	//�ō��������x
#define MOVE_SPPED 0.005f	//�ō��㏸���x
#define RISE_SPPED 0.01f	//�ō��㏸���x

#define LAND_SPEED 0.01f	//�ō��ړ����x�i�n�ʁj

Player::Player()
{
	player_state = IDOL_RIGHT;
	location.x = 0;
	location.y = 0;
	area.height = PLAYER_HEIGHT;
	area.width = PLAYER_WIDTH;
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
	balloon = 2;
	life = 2;
	death_flg = false;
	onfloor_flg = false;
	onshare_flg = false;

	ref_once1 = FALSE;
	ref_once2 = FALSE;

	LoadDivGraph("images/Player/Player_Animation.png", 30, 8, 4, 64, 64, player_image);
	player_anim = 0;
	anim_boost = 0;

	last_move_x = 0;
	last_input = false;
}

Player::~Player()
{

}

void Player::Update()
{
	if (death_flg == false)
	{

		//����(���ƐG��Ă��Ȃ��������m����)
		if (onfloor_flg != true)
		{
			if (last_input == 0)
			{
				player_state = FLY_LEFT;
			}
			else
			{
				player_state = FLY_RIGHT;
			}

			//����������������ɉ���
			if (acs_down < MAX_SPEED)
			{
				acs_down += (3 - balloon);
			}
			acs_left += land_acs_left;
			acs_right += land_acs_right;
			land_acs_left = 0;
			land_acs_right = 0;
			onfloor_flg = false;
		}
		else
		{
			onfloor_flg = true;
			OnFloor();
		}

		//�E���͂����m
		if (PAD_INPUT::GetLStick().ThumbX > 10000 || CheckHitKey(KEY_INPUT_D))
		{
			//�����Ă���Ȃ���������������Ă��Ȃ��Ȃ犵���Ȃ��ړ�
			//(�����Œn�ʂƂ̓����蔻����擾���Ă���state��ς���)
			if (onfloor_flg != true)
			{
				last_input = 1;
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
				player_state = WALK_RIGHT;
				land_acs_right--;
			}
		}

		//�����͂����m
		if (PAD_INPUT::GetLStick().ThumbX < -10000 || CheckHitKey(KEY_INPUT_A))
		{
			//�����Ă���Ȃ���������������Ă��Ȃ��Ȃ犵���Ȃ��ړ�
			//(�����Œn�ʂƂ̓����蔻����擾���Ă���state��ς���)
			if (onfloor_flg != true)
			{
				last_input = 0;
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
				player_state = WALK_LEFT;
				land_acs_left--;
			}
		}

		//�}�]�񔻒f
		if ((PAD_INPUT::GetLStick().ThumbX > 10000 || CheckHitKey(KEY_INPUT_D)) && last_move_x < 0 && onfloor_flg == TRUE)
		{
			player_state = TURN_LEFT;
		}
		if ((PAD_INPUT::GetLStick().ThumbX < -10000 || CheckHitKey(KEY_INPUT_A)) && last_move_x > 0 && onfloor_flg == TRUE)
		{
			player_state = TURN_RIGHT;
		}

		//�W�����v
		if (PAD_INPUT::OnButton(XINPUT_BUTTON_A) || PAD_INPUT::OnPressed(XINPUT_BUTTON_B) || CheckHitKey(KEY_INPUT_SPACE))
		{
			if (PAD_INPUT::GetLStick().ThumbX < -10000 || CheckHitKey(KEY_INPUT_A))
			{
				if (acs_left < MAX_SPEED)
				{
					acs_left += 1;
				}
				if (acs_right > 0)
				{
					if (frame % 3 == 0)
					{
						acs_right--;
					}
				}
			}
			if (PAD_INPUT::GetLStick().ThumbX > 10000 || CheckHitKey(KEY_INPUT_D))
			{
				if (acs_right < MAX_SPEED)
				{
					acs_right += 1;
				}
				if (acs_left > 0)
				{
					if (frame % 3 == 0)
					{
						acs_left--;
					}
				}
			}


			if (jump_int == 0)
			{
				anim_boost = 30;
				jump_int = JUMP_INTERVAL;
				//A�������Ή����قǏ�����x���オ��
				if (jump_combo < MAX_JUMP)
				{
					if (jump_combo == 0)
					{
						jump_combo += 5;
					}
					jump_combo+=2;
				}
				acs_up += jump_combo * 3 + balloon;
			}

		}
		else
		{
			anim_boost = 0;
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

		//�ړ�������ۑ�
		if ((acs_left * MOVE_SPPED) + (acs_right * MOVE_SPPED) + (land_acs_right * LAND_SPEED) - (land_acs_left * LAND_SPEED) != 0)
		{
			last_move_x = -(acs_left * MOVE_SPPED) + (acs_right * MOVE_SPPED) + (land_acs_right * LAND_SPEED) - (land_acs_left * LAND_SPEED);
		}
		//�ړ�
		location.x = location.x - (acs_left * MOVE_SPPED) + (acs_right * MOVE_SPPED) + (land_acs_right * LAND_SPEED) - (land_acs_left * LAND_SPEED);
		location.y = location.y - (acs_up * RISE_SPPED) + (acs_down + ref_y) * FALL_SPPED;

		//��ʒ[�ɍs���ƃe���|�[�g
		if (location.x < 0 - PLAYER_WIDTH)
		{
			location.x = SCREEN_WIDTH;
		}
		if (location.x > SCREEN_WIDTH)
		{
			location.x = 0 - PLAYER_WIDTH+2;
		}

		//��ʏ�ɓ�����ƒ��˕Ԃ�
		if (location.y < 0)
		{
			ReflectionPY();
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

		//�A�j���[�V����
		if (frame % (45 - anim_boost) == 0)
		{
			player_anim++;
			if (player_anim > 3)
			{
				player_anim = 0;
			}
		}

		if (PAD_INPUT::OnButton(XINPUT_BUTTON_X))BalloonDec();
	}
	//���S���̉��o
	else
	{
		location.y++;
	}
	//�v���C���[���C�ʂ�艺�֍s���Ǝc�@ -1
	if (location.y > SEA_SURFACE)
	{
		life = life - 1;
		PlayerRespawn(100, 350);
	}
}

void Player::Draw()const
{
	//�v���C���[�̕`��
	DrawBoxAA(location.x, location.y+PLAYER_BALLOON_HEIGHT, location.x + PLAYER_WIDTH, location.y + PLAYER_HEIGHT, 0xff0000, TRUE);
	//�v���C���[�̕��D�̕`��(��)
	DrawBox(location.x, location.y, location.x + PLAYER_WIDTH, location.y + PLAYER_BALLOON_HEIGHT, 0x00ff00, TRUE);
	DrawFormatString(0, 20, 0x00ff00, "%f", acs_down);
	DrawFormatString(0, 40, 0x00ff00, "%d", onfloor_flg);
	DrawFormatString(0, 60, 0x00ff00, "%d", life);
	DrawFormatString(0, 80, 0xffff00, "%d", onshare_flg);

	switch (player_state)
	{
	case IDOL_RIGHT:
		DrawTurnGraph(location.x - IMAGE_SHIFT_X, location.y - IMAGE_SHIFT_Y, player_image[0 + (player_anim % 3) + ((2 - balloon) * 4) ], TRUE);
		break;
	case IDOL_LEFT:
		DrawGraph(location.x - IMAGE_SHIFT_X, location.y - IMAGE_SHIFT_Y, player_image[0 + (player_anim % 3) + ((2 - balloon) * 4)], TRUE);
		break;
	case WALK_LEFT:
		DrawGraph(location.x - IMAGE_SHIFT_X, location.y - IMAGE_SHIFT_Y, player_image[8 + player_anim + ((2 - balloon) * 4)], TRUE);
		break;
	case TURN_LEFT:
		DrawGraph(location.x - IMAGE_SHIFT_X, location.y - IMAGE_SHIFT_Y, player_image[11 + ((2 - balloon) * 4)], TRUE);
		break;
	case WALK_RIGHT:
		DrawTurnGraph(location.x - IMAGE_SHIFT_X, location.y - IMAGE_SHIFT_Y,player_image[8 + player_anim + ((2 - balloon) * 4)], TRUE);
		break;
	case TURN_RIGHT:
		DrawTurnGraph(location.x - IMAGE_SHIFT_X, location.y - IMAGE_SHIFT_Y, player_image[11 + ((2 - balloon) * 4)], TRUE);
		break;
	case FLY_LEFT:
		DrawGraph(location.x - IMAGE_SHIFT_X, location.y - IMAGE_SHIFT_Y, player_image[16 + player_anim + ((2 - balloon) * 8)], TRUE);
		break;
	case FLY_RIGHT:
		DrawTurnGraph(location.x - IMAGE_SHIFT_X, location.y - IMAGE_SHIFT_Y, player_image[16 + player_anim + ((2 - balloon) * 8)], TRUE);
		break;
	case DEATH:
		DrawGraph(location.x - IMAGE_SHIFT_X, location.y - IMAGE_SHIFT_Y, player_image[21 + (player_anim%3)], TRUE);
		break;
	}

}

void Player::HitStageCollision(const BoxCollider* box_collider)
{
	//�����̓����蔻��͈̔�
	float my_x[2]{ 0,0 };
	float my_y[2]{ 0,0 };

	//����̓����蔻��͈̔�
	float sub_x[2]{ 0,0 };
	float sub_y[2]{ 0,0 };

	//�����̓����蔻��͈̔͂̌v�Z
	my_x[0] = location.x;
	my_y[0] = location.y;
	my_x[1] = my_x[0] + area.width;
	my_y[1] = my_y[0] + area.height;

	//����̓����蔻��͈̔͂̌v�Z
	sub_x[0] = box_collider->GetLocation().x;
	sub_y[0] = box_collider->GetLocation().y;
	sub_x[1] = sub_x[0] + box_collider->GetArea().width;
	sub_y[1] = sub_y[0] + box_collider->GetArea().height;

	//StageFloor�̉��͈͓̔�
	if (my_x[0] < sub_x[1] - 5 &&
		sub_x[0] + 5 < my_x[1])
	{
		//Player��StageFloor��艺�֍s�����Ƃ����ꍇ
		if (my_y[1] > sub_y[0] &&
			my_y[0] < sub_y[0])
		{
			//StageFloor��艺�ɂ͍s���Ȃ��悤�ɂ���
			location.y = sub_y[0] - area.height;
		}

		//Player��StageFloor����֍s�����Ƃ����ꍇ
		if (my_y[0] < sub_y[1] &&
			my_y[1] > sub_y[1])
		{
			//StageFloor����ɂ͍s���Ȃ��悤�ɂ���
			location.y = sub_y[1];
			//���˕Ԃ�
			ReflectionPY();
		}
	}

	//StaegFloor�̏c�͈͓̔�
	if (my_y[0] < sub_y[1] &&
		sub_y[0] < my_y[1])
	{
		//Player��StageFloor���E�֍s�����Ƃ����ꍇ
		if (my_x[1] > sub_x[0] &&
			my_x[0] < sub_x[0])
		{
			//StageFloor���E�ɂ͍s���Ȃ��悤�ɂ���
			location.x = sub_x[0] - area.width;
			//1�񂾂����֒��˕Ԃ�
			if (ref_once1 == FALSE)
			{
				//���˕Ԃ�
				ReflectionMX();
				ref_once1 = TRUE;
			}		
		}
		else
		{
			ref_once1 = FALSE;
		}
		//Player��StageFloor��荶�֍s�����Ƃ����ꍇ
		if (my_x[0] < sub_x[1] &&
			my_x[1]>sub_x[1])
		{
			//StageFloor��荶�ɂ͍s���Ȃ��悤�ɂ���
			location.x = sub_x[1];
			//1�񂾂��E�֒��˕Ԃ�
			if (ref_once2 == FALSE)
			{
				//���˕Ԃ�
				ReflectionPX();
				ref_once2 = TRUE;
			}
		}
		else
		{
			ref_once2 = FALSE;
		}

	}

	//onfloor_flg�̔���
	if (my_x[0] < sub_x[1] &&
		sub_x[0] < my_x[1] &&
		my_y[1] > sub_y[0] - 2 &&	//-�Q��StaegFloor��艺�֍s���Ȃ������ɑ΂��钲��
		my_y[0] < sub_y[0])
	{
		onfloor_flg = true;
	}
	else
	{
		onfloor_flg = false;
	}
}

bool Player::IsOnFloor(const BoxCollider* box_collider)const
{
	bool ret = false;

	//�����̓����蔻��͈̔�
	float my_x[2]{ 0,0 };
	float my_y[2]{ 0,0 };

	//����̓����蔻��͈̔�
	float sub_x[2]{ 0,0 };
	float sub_y[2]{ 0,0 };

	//�����̓����蔻��͈̔͂̌v�Z
	my_x[0] = location.x;
	my_y[0] = location.y;
	my_x[1] = my_x[0] + area.width;
	my_y[1] = my_y[0] + area.height;

	//����̓����蔻��͈̔͂̌v�Z
	sub_x[0] = box_collider->GetLocation().x;
	sub_y[0] = box_collider->GetLocation().y;
	sub_x[1] = sub_x[0] + box_collider->GetArea().width;
	sub_y[1] = sub_y[0] + box_collider->GetArea().height;

	//StageFloor�̉��͈͓̔�
	if (my_x[0] < sub_x[1] &&
		sub_x[0] < my_x[1])
	{
		//Player��StageFloor��艺�֍s�����Ƃ����ꍇ
		if (my_y[1] > sub_y[0] - 2 &&
			my_y[0] < sub_y[0])
		{
			ret = true;
		}
	}
	return ret;
}

void Player::OnFloor()
{
	jump_combo = 0;
	acs_down = 0;
	acs_up = 0;

	//�A�j���[�V������������
	if (last_move_x > 0)
	{
		player_state = IDOL_RIGHT;
	}
	if (last_move_x < 0)
	{
		player_state = IDOL_LEFT;
	}
	if (acs_left > 0)
	{
		player_state = WALK_LEFT;
		acs_left--;
	}
	else
	{
		acs_left = 0;
	}
	if (acs_right > 0)
	{
		player_state = WALK_RIGHT;
		acs_right--;
	}
	else
	{
		acs_right = 0;
	}
	ref_y = 0;
}

void Player::ReflectionMX()
{
	land_acs_right = 0;
	acs_left = acs_right * 0.8f;
	acs_right = 0;
}

void Player::ReflectionPX()
{
	land_acs_left = 0;
	acs_right = acs_left * 0.8f;
	acs_left = 0;
}

void Player::ReflectionPY()
{
	ref_y = acs_up * 0.05f;
	acs_up -= 200;
}

void Player::PlayerRespawn(int x,int y) 
{
	player_state = IDOL_RIGHT;
	location.x = x;
	location.y = y;
	acs_left = 0;
	acs_right = 0;
	acs_up = 0;
	acs_down = 0;
	land_acs_left = 0;
	land_acs_right = 0;
	jump_int = 0;
	jump_combo = 0;
	ref_y = 0;
	balloon = 2;
	death_flg = FALSE;
}

void Player::BalloonDec()
{
	if (--balloon <= 0)
	{
		death_flg = TRUE;
	}
}