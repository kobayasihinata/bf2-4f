#include "Dxlib.h"
#include <math.h>
#include "Player.h"
#include "PadInput.h"

static int balloon;        //�c�蕗�D
static int life;            //�c�@

Player::Player()
{
	player_state = IDOL_RIGHT;
	location.x = PLAYER_RESPAWN_POS_X;
	location.y = PLAYER_RESPAWN_POS_Y;
	area.height = PLAYER_ENEMY_HEIGHT;
	area.width = PLAYER_ENEMY_WIDTH;
	acs_left = 0;
	acs_right = 0;
	acs_up = 0;
	acs_down = 0;
	land_acs_left = 0;
	land_acs_right = 0;
	walk_SE_flg = false;
	jump_int = 0;
	jump_combo = 0;
	jump_cd = 0;
	jump_flg = false;
	jump_SE_flg = false;
	frame = 0;
	respawn = 600;
	death_flg = false;
	thunder_death_flg = false;
	death_acs = -120;
	death_wait = 120;
	thunder_death_wait = 60;
	underwater_flg = false;
	show_flg = true;
	is_player = true;
	onfloor_flg = false;
	onshare_flg = false;

	ref_once_left = FALSE;
	ref_once_right = FALSE;

	LoadDivGraph("images/Player/Player_Animation.png", 31, 8, 4, 64, 64, player_image);
	LoadDivGraph("images/Stage/Stage_SplashAnimation.png", 3, 3, 1, 64, 32, splash_image);
	fall_SE_flg = false;
	Splash_SE_flg = false;
	Restart_SE_flg = false;
	player_anim = 0;
	splash_anim = 0;
	turn_anim = 0;
	anim_boost = 0;
	jump_anim_boost = 0;

	last_move_x = 0;
	last_input = 1;

	
}

Player::~Player()
{
	for (int i = 0; i < 31; i++)
	{
		DeleteGraph(player_image[i]);
	}
	for (int i = 0; i < 3; i++)
	{
		DeleteGraph(splash_image[i]);
	}
}

void Player::Update()
{
	if (show_flg == true)
	{
		//����ł��Ȃ��Ȃ�
		if (death_flg == false && thunder_death_flg == false)
		{
			//���X�|�[����̖��G��ԂłȂ��Ȃ�
			if (--respawn <= 0)
			{
				//����(���ƐG��Ă��Ȃ��������m����)
				if (onfloor_flg != true)
				{
					if (last_input < 0) 
					{
						player_state = FLY_LEFT;
					}
					else if(last_input > 0)
					{
						player_state = FLY_RIGHT; 
					}

					//����������������ɉ���
					if (jump_flg == false)
					{
						if (acs_down < MAX_SPEED)
						{
							acs_down += 9 - (balloon*3);
						}
						else
						{
							acs_down = MAX_SPEED;
						}
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
				if (PAD_INPUT::GetLStick().ThumbX > 10000)
				{
					//�����Ă���Ȃ���������������Ă��Ȃ��Ȃ犵���Ȃ��ړ�
					//(�����Œn�ʂƂ̓����蔻����擾���Ă���state��ς���)
					if (onfloor_flg != true)
					{
						player_state = FLY_RIGHT;
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
						walk_SE_flg = true;
						last_input = 1;
						if (land_acs_right < MAX_SPEED_LAND)
						{
							land_acs_right+=4;
						}
					}

				}
				else
				{
					if (acs_right > 0)
					{
						if (frame % 3 == 0)
						{
							acs_right--;
						}
					}
					if (land_acs_right > 0)
					{
						player_state = WALK_RIGHT;
						land_acs_right-=4;
					}
				}

				//�����͂����m
				if (PAD_INPUT::GetLStick().ThumbX < -10000)
				{
					//�����Ă���Ȃ���������������Ă��Ȃ��Ȃ犵���Ȃ��ړ�
					//(�����Œn�ʂƂ̓����蔻����擾���Ă���state��ς���)
					if (onfloor_flg != true)
					{
						player_state = FLY_LEFT;
						last_input = -1;
						if (acs_left < MAX_SPEED)
						{
							acs_left += 2;
						}

					}
					else
					{
						player_state = WALK_LEFT;
						walk_SE_flg = true;
						last_input = -1;
						if (land_acs_left < MAX_SPEED_LAND)
						{
							land_acs_left+=4;
						}
					}

				}
				else
				{
					if (acs_left > 0)
					{
						if (frame % 3 == 0)
						{
							acs_left--;
						}
					}
					if (land_acs_left > 0)
					{
						player_state = WALK_LEFT;
						land_acs_left-=4;
					}
				}

				//�}�]�񔻒f
				if (PAD_INPUT::GetLStick().ThumbX > -10000 && last_move_x < 0 && onfloor_flg == TRUE)
				{
					player_state = TURN_LEFT;
				}
				if (PAD_INPUT::GetLStick().ThumbX < 10000 && last_move_x > 0 && onfloor_flg == TRUE)
				{
					player_state = TURN_RIGHT;
				}

				//�W�����v�i�������j
				if (PAD_INPUT::OnPressed(XINPUT_BUTTON_B))
				{
					jump_flg = true;
					jump_SE_flg = true;
					
					if (acs_down >= 0)
					{
						acs_down -= 2;
					}
					else
					{
						acs_down = 0;
					}

					//�W�����v���̃A�j���[�V����
					if (frame % 3 == 0)
					{
						player_anim++;
					}
					if (player_anim > 3)
					{
						player_anim = 0;
					}

					if (jump_int == 0)
					{
						jump_int = JUMP_INTERVAL;
						//A�������Ή����قǏ�����x���オ��
						if (jump_combo < MAX_JUMP)
						{
							if (onfloor_flg == true)
							{
								location.y -= 2;
								jump_combo += 5 + balloon;
							}
							jump_combo += 2;
						}
						if (acs_up < MAX_SPEED / 2)
						{
							acs_up += jump_combo * 3 + balloon;
						}
						else
						{
							acs_up = MAX_SPEED / 2;
						}
						//�㏸���ɍ����͂�����Ă����獶�ɉ�������
						if (PAD_INPUT::GetLStick().ThumbX < -10000)
						{
							if (acs_left < MAX_SPEED)
							{
								acs_left += 40;
								acs_up -= 10;
							}
							else
							{
								acs_left = MAX_SPEED;
							}
							if (acs_right > 0)
							{
								acs_right -= 40;
							}
							else
							{
								acs_right = 0;
							}
						}
						//�㏸���ɉE���͂�����Ă�����E�ɉ�������
						if (PAD_INPUT::GetLStick().ThumbX > 10000)
						{
							if (acs_right < MAX_SPEED)
							{
								acs_right += 40;
								acs_up -= 10;
							}
							else
							{
								acs_right = MAX_SPEED;
							}
							if (acs_left > 0)
							{
								acs_left -= 40;
							}
							else
							{
								acs_left = 0;
							}
						}
					}
				}
				//�W�����v�i�A�Łj
				else if (PAD_INPUT::OnButton(XINPUT_BUTTON_A))
				{
					jump_SE_flg = true;

					//�㏸���ɍ����͂�����Ă����獶�ɉ�������
					if (PAD_INPUT::GetLStick().ThumbX < -10000)
					{
						if (acs_left < MAX_SPEED)
						{
							acs_left += 40;
							acs_up -= 10;
						}
						else
						{
							acs_left = MAX_SPEED;
						}
						if (acs_right > 0)
						{
							acs_right -= 40;
						}
						else
						{
							acs_right = 0;
						}
					}
					//�㏸���ɉE���͂�����Ă�����E�ɉ�������
					if (PAD_INPUT::GetLStick().ThumbX > 10000)
					{
						if (acs_right < MAX_SPEED)
						{
							acs_right += 40;
							acs_up -= 10;
						}
						else
						{
							acs_right = MAX_SPEED;
						}
						if (acs_left > 0)
						{
							acs_left -= 40;
						}
						else
						{
							acs_left = 0;
						}
					}

					jump_anim_boost = 4;
					if (jump_int == 0)
					{
						if (acs_down >= 0)
						{
							acs_down -= 6;
						}
						else
						{
							acs_down = 0;
						}
						jump_int = JUMP_INTERVAL - 3;
						jump_cd = 5;
						//A�������Ή����قǏ�����x���オ��
						if (jump_combo < MAX_JUMP)
						{
							if (onfloor_flg == true)
							{
								location.y -= 2;
								jump_combo += 5 + balloon;
							}
							jump_combo += 3;
						}
						if (acs_up < MAX_SPEED / 1.3)
						{
							acs_up += jump_combo * 3 + balloon;
						}
						else
						{
							acs_up = MAX_SPEED / 1.3;
						}
					}
				}
				//�A�Œ��ɏ㏸�l������Ȃ��悤�ɂ���
				else if (PAD_INPUT::OnPressed(XINPUT_BUTTON_A))
				{

					jump_flg = true;
					if (--jump_cd < 0)
					{
						jump_flg = false;
						jump_cd = -1;
						if (acs_up > 0)
						{
							acs_up -= 2;
						}
						if (acs_down >= 0)
						{
							acs_down -= 2;
						}
						else
						{
							acs_down = 0;
						}
					}
				}
				else
				{
					jump_flg = false;
					if (acs_up > 0)
					{
						acs_up--;
					}
				}
				//�W�����v�A�Ŏ��A�j���[�V��������
				if (jump_anim_boost > 0 && frame % 3 == 0)
				{
					player_anim++;
					jump_anim_boost--;
					if (player_anim > 3)
					{
						player_anim = 0;
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
				last_move_x = -(acs_left * MOVE_SPPED) + (acs_right * MOVE_SPPED) + (land_acs_right * LAND_SPEED) - (land_acs_left * LAND_SPEED);
				

				//�ړ�
				if (underwater_flg == false)
				{
					location.x = location.x - (acs_left * MOVE_SPPED) + (acs_right * MOVE_SPPED) + (land_acs_right * LAND_SPEED) - (land_acs_left * LAND_SPEED);
					location.y = location.y - (acs_up * RISE_SPPED) + (acs_down * FALL_SPPED);
				}

				//��ʒ[�ɍs���ƃe���|�[�g
				if (location.x < 0 - PLAYER_ENEMY_WIDTH)
				{
					location.x = SCREEN_WIDTH - 2;
				}
				if (location.x > SCREEN_WIDTH - 1)
				{
					location.x = 0 - PLAYER_ENEMY_WIDTH + 2;
				}

				//��ʏ�ɓ�����ƒ��˕Ԃ�
				if (location.y < 0)
				{
					location.y = 0;
					ReflectionPY();
				}
			}
			//���X�|�[����̖��G��ԂȂ�
			else
			{
				if (PAD_INPUT::GetLStick().ThumbX > 10000 || PAD_INPUT::GetLStick().ThumbX < -10000 || PAD_INPUT::OnButton(XINPUT_BUTTON_A) || PAD_INPUT::OnButton(XINPUT_BUTTON_B))
			{
				respawn = 0;
			}
				anim_boost = 15;
				player_state = INVINCIBLE;
			}
		}
		//���S���̉��o(��)
		else if (thunder_death_flg == true)
		{
			player_state = THUNDER_DEATH;
			death_acs += 2;
			//���d���̃A�j���[�V����
			if (frame % 3 == 0)
			{
				player_anim++;
			}
			if (player_anim > 3)
			{
				player_anim = 0;
			}
			if (--thunder_death_wait < 0)
			{
				death_flg = true;
				thunder_death_flg = false;
			}
		}

		//���S���̉��o(�ʏ�)
		else
		{
			player_state = DEATH;

			death_acs += 4;

			location.y += death_acs * FALL_SPPED;

			fall_SE_flg = true;
		}
	}
	//�t���[�����v������(10�b���ƂɃ��Z�b�g)
	if (++frame > 600)
	{
		frame = 0;
	}

	//�A�j���[�V����
	if (frame % (20 - anim_boost) == 0 && player_state != FLY_LEFT && player_state != FLY_RIGHT && player_state != TURN_LEFT && player_state != TURN_RIGHT)
	{
		player_anim++;
		if (player_anim > 3)
		{
			player_anim = 0;
		}
	}
	if (player_state != FLY_LEFT && player_state != FLY_RIGHT && player_state != IDOL_LEFT && player_state != IDOL_RIGHT && player_state != THUNDER_DEATH)
	{
		anim_boost = 15;
	}
	else
	{
		anim_boost = 0;
	}
	if (player_state == WALK_LEFT || player_state == WALK_RIGHT)
	{
		anim_boost = 18;
	}
	if (player_state == TURN_LEFT || player_state == TURN_RIGHT)
	{
		if (frame % 15 == 0)
		{
			if (++turn_anim >= 1)
			{
				turn_anim = 1;
			}
		}
	}
	else
	{
		turn_anim = 0;
	}

	//�v���C���[���C�ʂ�艺�֍s���Ǝc�@ -1
	if (location.y > UNDER_WATER && show_flg == true)
	{
		underwater_flg = true;
		is_die = true;
		Splash_SE_flg = true;
		//�v���C���[�𐅖v���ɐݒ�
		player_state = SUBMERGED;
		location.y = 470;
		if (--death_wait < 0)
		{
			underwater_flg = false;
			is_die = false;
			splash_anim = 0;
			life = life - 1;
			PlayerRespawn(PLAYER_RESPAWN_POS_X, PLAYER_RESPAWN_POS_Y);
		}
	}

	if (is_die) {
		player_state = SUBMERGED;
		if (frame % 5 == 0)
		{
			splash_anim++;
			if (splash_anim >= 3)
			{
				splash_anim = 8;
			}
		}
		if (--death_wait < 0)
		{
			underwater_flg = false;
			is_die = false;
			splash_anim = 0;
			life = life - 1;
			PlayerRespawn(PLAYER_RESPAWN_POS_X, PLAYER_RESPAWN_POS_Y);
		}
	}
}

void Player::Draw()const
{
	
	if (show_flg == true)
	{
		//�v���C���[�̕`��
		switch (player_state)
		{
		case IDOL_RIGHT:
			DrawTurnGraphF(location.x - IMAGE_SHIFT_X, location.y - IMAGE_SHIFT_Y, player_image[0 + (player_anim % 3) + ((2 - balloon) * 4)], TRUE);
			break;
		case IDOL_LEFT:
			DrawGraphF(location.x - IMAGE_SHIFT_X, location.y - IMAGE_SHIFT_Y, player_image[0 + (player_anim % 3) + ((2 - balloon) * 4)], TRUE);
			break;
		case WALK_LEFT:
			if (balloon == 1)
			{
				DrawGraphF(location.x - IMAGE_SHIFT_X, location.y - IMAGE_SHIFT_Y, player_image[9 + player_anim + ((2 - balloon) * 4)], TRUE);

			}
			else
			{
				DrawGraphF(location.x - IMAGE_SHIFT_X, location.y - IMAGE_SHIFT_Y, player_image[8 + player_anim + ((2 - balloon) * 4)], TRUE);

			}			
			break;
		case TURN_LEFT:
			if (balloon == 1)
			{
				DrawGraphF(location.x - IMAGE_SHIFT_X, location.y - IMAGE_SHIFT_Y, player_image[16], TRUE);

			}
			else 
			{
				DrawGraphF(location.x - IMAGE_SHIFT_X, location.y - IMAGE_SHIFT_Y, player_image[11 + turn_anim], TRUE);

			}
			break;
		case WALK_RIGHT:
			if (balloon == 1)
			{
				DrawTurnGraphF(location.x - IMAGE_SHIFT_X, location.y - IMAGE_SHIFT_Y, player_image[9 + player_anim + ((2 - balloon) * 4)], TRUE);

			}
			else
			{
				DrawTurnGraphF(location.x - IMAGE_SHIFT_X, location.y - IMAGE_SHIFT_Y, player_image[8 + player_anim + ((2 - balloon) * 4)], TRUE);

			}
			break;
		case TURN_RIGHT:
			if (balloon == 1)
			{
				DrawTurnGraphF(location.x - IMAGE_SHIFT_X, location.y - IMAGE_SHIFT_Y, player_image[16], TRUE);

			}
			else
			{
				DrawTurnGraphF(location.x - IMAGE_SHIFT_X, location.y - IMAGE_SHIFT_Y, player_image[11 + turn_anim], TRUE);

			}
			break;
		case FLY_LEFT:
			DrawGraphF(location.x - IMAGE_SHIFT_X, location.y - IMAGE_SHIFT_Y, player_image[17 + player_anim + ((2 - balloon) * 5)], TRUE);
			break;
		case FLY_RIGHT:
			DrawTurnGraphF(location.x - IMAGE_SHIFT_X, location.y - IMAGE_SHIFT_Y, player_image[17 + player_anim + ((2 - balloon) * 5)], TRUE);
			break;
		case DEATH:
			DrawGraphF(location.x - IMAGE_SHIFT_X, location.y - IMAGE_SHIFT_Y, player_image[27 + (player_anim % 3)], TRUE);
			break;
		case THUNDER_DEATH:
			DrawGraphF(location.x - IMAGE_SHIFT_X, location.y - IMAGE_SHIFT_Y, player_image[27 + (player_anim % 2)*3], TRUE);
			break;
		case INVINCIBLE:
			if (balloon == 2) {
				DrawTurnGraphF(location.x - IMAGE_SHIFT_X, location.y - IMAGE_SHIFT_Y, player_image[2 + (player_anim % 2)], TRUE);
			}
			else
			{
				DrawTurnGraphF(location.x - IMAGE_SHIFT_X, location.y - IMAGE_SHIFT_Y, player_image[6 + (player_anim % 2)], TRUE);
			}
			break;
		case SUBMERGED:
			DrawGraphF(location.x - IMAGE_SHIFT_X, location.y - IMAGE_SHIFT_Y-45, splash_image[0 + splash_anim], TRUE);
			break;
		}
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
	if (my_y[0] < sub_y[1] - 5 &&
		sub_y[0] + 5 < my_y[1])
	{
		//Player��StageFloor���E�֍s�����Ƃ����ꍇ
		if (my_x[1] > sub_x[0] &&
			my_x[0] < sub_x[0])
		{
			//StageFloor���E�ɂ͍s���Ȃ��悤�ɂ���
			location.x = sub_x[0] - area.width - 5;
			//1�񂾂����֒��˕Ԃ�
			if (ref_once_left == FALSE)
			{
				//���˕Ԃ�
				ReflectionMX();
				ref_once_left = TRUE;
			}		
		}
		else
		{
			ref_once_left = FALSE;
		}
		//Player��StageFloor��荶�֍s�����Ƃ����ꍇ
		if (my_x[0] < sub_x[1] &&
			my_x[1]>sub_x[1])
		{
			//StageFloor��荶�ɂ͍s���Ȃ��悤�ɂ���
			location.x = sub_x[1] + 5;
			//1�񂾂��E�֒��˕Ԃ�
			if (ref_once_right == FALSE)
			{
				//���˕Ԃ�
				ReflectionPX();
				ref_once_right = TRUE;
			}
		}
		else
		{
			ref_once_right = FALSE;
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

int Player::HitEnemyCollision(const BoxCollider* box_collider)
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

	//�G�̏c�͈͓̔�
	if (my_y[0] < sub_y[1] - 5 &&
		sub_y[0] + 5 < my_y[1])
	{
		//Player���G���E�֍s�����Ƃ����ꍇ
		if (my_x[1] > sub_x[0] &&
			my_x[0] < sub_x[0])
		{
			//�G���E�ɂ͍s���Ȃ��悤�ɂ���
			location.x = sub_x[0] - area.width - 1;
			return 1;
		}

		//Player���G��荶�֍s�����Ƃ����ꍇ
		if (my_x[0] < sub_x[1] &&
			my_x[1]>sub_x[1])
		{
			//�G��荶�ɂ͍s���Ȃ��悤�ɂ���
			location.x = sub_x[1] + 1;
			return 2;
		}
	}
	//�G�̉��͈͓̔�
	if (my_x[0] < sub_x[1] - 5 &&
		sub_x[0] + 5 < my_x[1])
	{
		//Player���G��艺�֍s�����Ƃ����ꍇ
		if (my_y[1] > sub_y[0] &&
			my_y[0] < sub_y[0])
		{
			//�G��艺�ɂ͍s���Ȃ��悤�ɂ���
			location.y = sub_y[0] - area.height;
			return 4;
		}

		//Player���G����֍s�����Ƃ����ꍇ
		if (my_y[0] < sub_y[1] &&
			my_y[1] > sub_y[1])
		{
			//�G����ɂ͍s���Ȃ��悤�ɂ���
			location.y = sub_y[1];
			return 3;
		}
	}
	return 0;
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
	if (last_input == -1)
	{
		player_state = IDOL_LEFT;
	}
	if (last_input == 1)
	{
		player_state = IDOL_RIGHT;
	}
	if (acs_left > 0)
	{
		player_state = TURN_LEFT;
		acs_left-=7;
	}
	else
	{
		acs_left = 0;
	}
	if (acs_right > 0)
	{
		player_state = TURN_RIGHT;
		acs_right-=7;
	}
	else
	{
		acs_right = 0;
	}
}

void Player::ReflectionMX()
{
	last_input *= -1;
	land_acs_right = 0;
	acs_left = fabsf(acs_right - acs_left) * 0.8f;
	acs_right = 0;
}

void Player::ReflectionPX()
{
	last_input *= -1;
	land_acs_left = 0;
	acs_right = fabsf(acs_right - acs_left) * 1.0f;
	acs_left = 0;
}

void Player::ReflectionPY()
{
	acs_down = fabsf(acs_up - acs_down) * 1.0f;
	acs_up = 0;
	jump_combo = 0;
}

void Player::ReflectionMY()
{
	acs_up = fabsf(acs_up - acs_down) * 0.8f;
	acs_down = 0;
}

void Player::PlayerRespawn(float x, float y)
{
	if (life >= 0) {
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
		balloon = 2;
		splash_anim = 0;
		death_flg = false;
		thunder_death_flg = false;
		death_acs = -120;
		death_wait = 120;
		thunder_death_wait = 60;
		respawn = 600;
		show_flg = true;
		underwater_flg = false;
		Restart_SE_flg = true;
	}
}

void Player::BalloonDec()
{

	if (--balloon <= 0)
	{
		death_flg = true;
	}
}
void Player::ResetPlayerPos(int x,int y)
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
	respawn = 600;
}

//�v���C���[�̎c�@���擾����
int Player::GetPlayerLife() { return life; }

//�v���C���[�̎c�@��ݒ肷��
void Player::SetPlayerLife(const int setlife) {life = life + setlife; }

void Player::ResetPlayerLife()
{
	life = 2;
	balloon = 2;
}