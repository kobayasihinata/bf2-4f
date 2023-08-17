#include "Dxlib.h"
#include <math.h>
#include "Player.h"
#include "PadInput.h"

static int balloon;        //残り風船
static int life;            //残機

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
		//死んでいないなら
		if (death_flg == false && thunder_death_flg == false)
		{
			//リスポーン後の無敵状態でないなら
			if (--respawn <= 0)
			{
				//落下(床と触れていない事を検知する)
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

					//落下し続ける程下に加速
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

				//右入力を検知
				if (PAD_INPUT::GetLStick().ThumbX > 10000)
				{
					//浮いているなら加速処理＆浮いていないなら慣性なし移動
					//(ここで地面との当たり判定を取得してきてstateを変える)
					if (onfloor_flg != true)
					{
						player_state = FLY_RIGHT;
						last_input = 1;
						if (acs_right < MAX_SPEED)
						{
							acs_right += 2;
						}

					}
					//地面と接しているなら
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

				//左入力を検知
				if (PAD_INPUT::GetLStick().ThumbX < -10000)
				{
					//浮いているなら加速処理＆浮いていないなら慣性なし移動
					//(ここで地面との当たり判定を取得してきてstateを変える)
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

				//急転回判断
				if (PAD_INPUT::GetLStick().ThumbX > -10000 && last_move_x < 0 && onfloor_flg == TRUE)
				{
					player_state = TURN_LEFT;
				}
				if (PAD_INPUT::GetLStick().ThumbX < 10000 && last_move_x > 0 && onfloor_flg == TRUE)
				{
					player_state = TURN_RIGHT;
				}

				//ジャンプ（長押し）
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

					//ジャンプ中のアニメーション
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
						//Aを押せば押すほど上加速度が上がる
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
						//上昇時に左入力がされていたら左に加速する
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
						//上昇時に右入力がされていたら右に加速する
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
				//ジャンプ（連打）
				else if (PAD_INPUT::OnButton(XINPUT_BUTTON_A))
				{
					jump_SE_flg = true;

					//上昇時に左入力がされていたら左に加速する
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
					//上昇時に右入力がされていたら右に加速する
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
						//Aを押せば押すほど上加速度が上がる
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
				//連打中に上昇値が減らないようにする
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
				//ジャンプ連打時アニメーション処理
				if (jump_anim_boost > 0 && frame % 3 == 0)
				{
					player_anim++;
					jump_anim_boost--;
					if (player_anim > 3)
					{
						player_anim = 0;
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

				//移動距離を保存
				last_move_x = -(acs_left * MOVE_SPPED) + (acs_right * MOVE_SPPED) + (land_acs_right * LAND_SPEED) - (land_acs_left * LAND_SPEED);
				

				//移動
				if (underwater_flg == false)
				{
					location.x = location.x - (acs_left * MOVE_SPPED) + (acs_right * MOVE_SPPED) + (land_acs_right * LAND_SPEED) - (land_acs_left * LAND_SPEED);
					location.y = location.y - (acs_up * RISE_SPPED) + (acs_down * FALL_SPPED);
				}

				//画面端に行くとテレポート
				if (location.x < 0 - PLAYER_ENEMY_WIDTH)
				{
					location.x = SCREEN_WIDTH - 2;
				}
				if (location.x > SCREEN_WIDTH - 1)
				{
					location.x = 0 - PLAYER_ENEMY_WIDTH + 2;
				}

				//画面上に当たると跳ね返る
				if (location.y < 0)
				{
					location.y = 0;
					ReflectionPY();
				}
			}
			//リスポーン後の無敵状態なら
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
		//死亡中の演出(雷)
		else if (thunder_death_flg == true)
		{
			player_state = THUNDER_DEATH;
			death_acs += 2;
			//感電中のアニメーション
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

		//死亡中の演出(通常)
		else
		{
			player_state = DEATH;

			death_acs += 4;

			location.y += death_acs * FALL_SPPED;

			fall_SE_flg = true;
		}
	}
	//フレームを計測する(10秒ごとにリセット)
	if (++frame > 600)
	{
		frame = 0;
	}

	//アニメーション
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

	//プレイヤーが海面より下へ行くと残機 -1
	if (location.y > UNDER_WATER && show_flg == true)
	{
		underwater_flg = true;
		is_die = true;
		Splash_SE_flg = true;
		//プレイヤーを水没中に設定
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
		//プレイヤーの描画
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
	//自分の当たり判定の範囲
	float my_x[2]{ 0,0 };
	float my_y[2]{ 0,0 };

	//相手の当たり判定の範囲
	float sub_x[2]{ 0,0 };
	float sub_y[2]{ 0,0 };

	//自分の当たり判定の範囲の計算
	my_x[0] = location.x;
	my_y[0] = location.y;
	my_x[1] = my_x[0] + area.width;
	my_y[1] = my_y[0] + area.height;

	//相手の当たり判定の範囲の計算
	sub_x[0] = box_collider->GetLocation().x;
	sub_y[0] = box_collider->GetLocation().y;
	sub_x[1] = sub_x[0] + box_collider->GetArea().width;
	sub_y[1] = sub_y[0] + box_collider->GetArea().height;

	//StageFloorの横の範囲内
	if (my_x[0] < sub_x[1] - 5 &&
		sub_x[0] + 5 < my_x[1])
	{
		//PlayerがStageFloorより下へ行こうとした場合
		if (my_y[1] > sub_y[0] &&
			my_y[0] < sub_y[0])
		{
			//StageFloorより下には行けないようにする
			location.y = sub_y[0] - area.height;
		}

		//PlayerがStageFloorより上へ行こうとした場合
		if (my_y[0] < sub_y[1] &&
			my_y[1] > sub_y[1])
		{
			//StageFloorより上には行けないようにする
			location.y = sub_y[1];
			//跳ね返る
			ReflectionPY();
		}
	}

	//StaegFloorの縦の範囲内
	if (my_y[0] < sub_y[1] - 5 &&
		sub_y[0] + 5 < my_y[1])
	{
		//PlayerがStageFloorより右へ行こうとした場合
		if (my_x[1] > sub_x[0] &&
			my_x[0] < sub_x[0])
		{
			//StageFloorより右には行けないようにする
			location.x = sub_x[0] - area.width - 5;
			//1回だけ左へ跳ね返る
			if (ref_once_left == FALSE)
			{
				//跳ね返る
				ReflectionMX();
				ref_once_left = TRUE;
			}		
		}
		else
		{
			ref_once_left = FALSE;
		}
		//PlayerがStageFloorより左へ行こうとした場合
		if (my_x[0] < sub_x[1] &&
			my_x[1]>sub_x[1])
		{
			//StageFloorより左には行けないようにする
			location.x = sub_x[1] + 5;
			//1回だけ右へ跳ね返る
			if (ref_once_right == FALSE)
			{
				//跳ね返る
				ReflectionPX();
				ref_once_right = TRUE;
			}
		}
		else
		{
			ref_once_right = FALSE;
		}

	}

	//onfloor_flgの判定
	if (my_x[0] < sub_x[1] &&
		sub_x[0] < my_x[1] &&
		my_y[1] > sub_y[0] - 2 &&	//-２はStaegFloorより下へ行けない処理に対する調整
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
	//自分の当たり判定の範囲
	float my_x[2]{ 0,0 };
	float my_y[2]{ 0,0 };

	//相手の当たり判定の範囲
	float sub_x[2]{ 0,0 };
	float sub_y[2]{ 0,0 };

	//自分の当たり判定の範囲の計算
	my_x[0] = location.x;
	my_y[0] = location.y;
	my_x[1] = my_x[0] + area.width;
	my_y[1] = my_y[0] + area.height;

	//相手の当たり判定の範囲の計算
	sub_x[0] = box_collider->GetLocation().x;
	sub_y[0] = box_collider->GetLocation().y;
	sub_x[1] = sub_x[0] + box_collider->GetArea().width;
	sub_y[1] = sub_y[0] + box_collider->GetArea().height;

	//敵の縦の範囲内
	if (my_y[0] < sub_y[1] - 5 &&
		sub_y[0] + 5 < my_y[1])
	{
		//Playerが敵より右へ行こうとした場合
		if (my_x[1] > sub_x[0] &&
			my_x[0] < sub_x[0])
		{
			//敵より右には行けないようにする
			location.x = sub_x[0] - area.width - 1;
			return 1;
		}

		//Playerが敵より左へ行こうとした場合
		if (my_x[0] < sub_x[1] &&
			my_x[1]>sub_x[1])
		{
			//敵より左には行けないようにする
			location.x = sub_x[1] + 1;
			return 2;
		}
	}
	//敵の横の範囲内
	if (my_x[0] < sub_x[1] - 5 &&
		sub_x[0] + 5 < my_x[1])
	{
		//Playerが敵より下へ行こうとした場合
		if (my_y[1] > sub_y[0] &&
			my_y[0] < sub_y[0])
		{
			//敵より下には行けないようにする
			location.y = sub_y[0] - area.height;
			return 4;
		}

		//Playerが敵より上へ行こうとした場合
		if (my_y[0] < sub_y[1] &&
			my_y[1] > sub_y[1])
		{
			//敵より上には行けないようにする
			location.y = sub_y[1];
			return 3;
		}
	}
	return 0;
}

bool Player::IsOnFloor(const BoxCollider* box_collider)const
{
	bool ret = false;

	//自分の当たり判定の範囲
	float my_x[2]{ 0,0 };
	float my_y[2]{ 0,0 };

	//相手の当たり判定の範囲
	float sub_x[2]{ 0,0 };
	float sub_y[2]{ 0,0 };

	//自分の当たり判定の範囲の計算
	my_x[0] = location.x;
	my_y[0] = location.y;
	my_x[1] = my_x[0] + area.width;
	my_y[1] = my_y[0] + area.height;

	//相手の当たり判定の範囲の計算
	sub_x[0] = box_collider->GetLocation().x;
	sub_y[0] = box_collider->GetLocation().y;
	sub_x[1] = sub_x[0] + box_collider->GetArea().width;
	sub_y[1] = sub_y[0] + box_collider->GetArea().height;

	//StageFloorの横の範囲内
	if (my_x[0] < sub_x[1] &&
		sub_x[0] < my_x[1])
	{
		//PlayerがStageFloorより下へ行こうとした場合
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

	//アニメーション方向判定
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

//プレイヤーの残機を取得する
int Player::GetPlayerLife() { return life; }

//プレイヤーの残機を設定する
void Player::SetPlayerLife(const int setlife) {life = life + setlife; }

void Player::ResetPlayerLife()
{
	life = 2;
	balloon = 2;
}