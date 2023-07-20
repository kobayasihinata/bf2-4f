#include "Dxlib.h"
#include <math.h>
#include "Enemy.h"
#include "PadInput.h"

Enemy::Enemy(int x,int y,int level)
{
	flg = true;
	location.x = x;
	location.y = y;
	area.height = PLAYER_HEIGHT;
	area.width = PLAYER_WIDTH;
	acs_left = 0;
	acs_right = 0;
	acs_up = 0;
	acs_down = 0;
	jump_int = 0;
	jump_combo = 0;
	jump_cd = 0;
	frame = 0;
	balloon = 0;
	wait_time = 0;
	charge = 0;
	enemy_level = level;
	first_flg = true;
	levelup_once = false;
	para_flg = false;
	death_flg = false;
	death_acs = -120;
	damage = 0;
	protect = -1;
	show_flg = true;
	is_player = false;
	onfloor_flg = false;
	onshare_flg = false;
	move_right_flg = false;
	move_left_flg = false;
	jump_flg = false;
	ref_once_left = false;
	ref_once_right = false;

	switch (level)
	{
	case 1:
		LoadDivGraph("images/Enemy/Enemy_P_Animation.png", 20, 8, 4, 64, 64, enemy_image);
		break;
	case 2:
		LoadDivGraph("images/Enemy/Enemy_G_Animation.png", 20, 8, 4, 64, 64, enemy_image);
		break;
	case 3:
		LoadDivGraph("images/Enemy/Enemy_R_Animation.png", 20, 8, 4, 64, 64, enemy_image);
		break;
	}
	enemy_anim = 0;
	para_anim = 0;
	anim_boost = 0;

	last_move_x = 1;
	last_input = 1;

	test_score = 0;

}

Enemy::~Enemy()
{
	for (int i = 0; i < 20; i++)
	{
		DeleteGraph(enemy_image[i]);
	}
}

void Enemy::Update()
{
	if (show_flg == true && flg == true)
	{
		if (death_flg == false)
		{


			//ダメージ実験
			if (PAD_INPUT::OnButton(XINPUT_BUTTON_Y))
			{
				test_score += ApplyDamege();
			}

			//パラシュート着地後の待機時間処理
			if (--wait_time >= 0)
			{
				if (last_input == 0)
				{
					enemy_state = E_IDOL_LEFT;
				}
				else
				{
					enemy_state = E_IDOL_RIGHT;
				}
			}
			//風船を膨らませる	
			else if (charge < 6)
			{
				anim_boost = 0;
				if (last_input == 0)
				{
					enemy_state = CHARGE_LEFT;
				}
				else
				{
					enemy_state = CHARGE_RIGHT;
				}
				if (frame % 22 == 0)
				{
					charge++;
				}
			}
			//風船を膨らませたなら
			else
			{
				//一瞬だけ無敵（ApplyDamegeが反応しないようにしてある）
				if (--protect < 0)protect = -1;
				//最初の風船を膨らませる時はレベルを上げないで、２回目以降はレベルを上げる処理
				if (first_flg == false)
				{
					if (levelup_once == false)
					{
						balloon = 1;
						protect = 4;
						EnemyLevelUp();
						levelup_once = true;
					}
				}
				else
				{
					if (levelup_once == false)
					{
						balloon = 1;
						protect = 4;
						first_flg = false;
						levelup_once = true;
					}
				}

				//落下(床と触れていない事を検知する)
				if (onshare_flg == false)
				{
					if (last_input == 0)
					{
						enemy_state = E_FLY_LEFT;
					}
					else
					{
						enemy_state = E_FLY_RIGHT;
					}

					//落下し続ける程下に加速
					if (acs_down < MAX_SPEED)
					{
						acs_down += 1;
					}
					onfloor_flg = false;
				}
				//床に触れているときの処理
				else
				{
					if (last_input == 0)
					{
						enemy_state = E_FLY_LEFT;
					}
					else
					{
						enemy_state = E_FLY_RIGHT;
					}
					onfloor_flg = true;
					OnFloor();
					if (para_flg == true)
					{
						EnemyReset();
					}
				}

				//右入力されている時の処理
				if (PAD_INPUT::GetLStick().ThumbX > 10000 || move_right_flg == true)
				{
					enemy_state = E_FLY_RIGHT;
					last_input = 0;
					if (acs_right < MAX_SPEED)
					{
						acs_right += 2;
					}
				}
				//右入力されていない時の処理
				else
				{
					if (acs_right > 0)
					{
						if (frame % 10 == 0)
						{
							acs_right--;
						}
						if (para_flg == true)
						{
							acs_right--;
						}
					}
				}

				//左入力されている時の処理
				if (PAD_INPUT::GetLStick().ThumbX < -10000 || move_left_flg == true)
				{
					enemy_state = E_FLY_LEFT;
					last_input = 1;
					if (acs_left < MAX_SPEED)
					{
						acs_left += 2;
					}
				}
				//左入力されていない時の処理
				else
				{
					if (acs_left > 0)
					{
						if (frame % 10 == 0)
						{
							acs_left--;
						}
						if (para_flg == true)
						{
							acs_left--;
						}
					}
				}

				//ジャンプ入力されている時の処理
				if ((PAD_INPUT::OnPressed(XINPUT_BUTTON_B) || jump_flg == true) && para_flg == false)
				{
					if (PAD_INPUT::GetLStick().ThumbX < -10000 || move_left_flg == true)
					{
						if (acs_left < MAX_SPEED)
						{
							acs_left += 4;
							acs_up -= 3;
						}
						if (acs_right > 0)
						{
							acs_right--;
						}
					}
					if (PAD_INPUT::GetLStick().ThumbX > 10000 || move_right_flg == true)
					{
						if (acs_right < MAX_SPEED)
						{
							acs_right += 4;
							acs_up -= 3;
						}
						if (acs_left > 0)
						{
							acs_left--;

						}
					}
					//ジャンプ中のアニメーション
					if (frame % 5 == 0)
					{
						enemy_anim++;
					}
					if (enemy_anim > 3)
					{
						enemy_anim = 0;
					}

					if (jump_int == 0)
					{
						anim_boost = 10;
						jump_int = JUMP_INTERVAL;

						if (jump_combo < MAX_JUMP)
						{
							//初速を上げる
							if (jump_combo == 0)
							{
								jump_combo += 5 + balloon;
							}
							jump_combo += 2;
						}
						acs_up += jump_combo * 3 + balloon;
					}
				}
				//ジャンプ入力されていない時の処理
				else
				{
					anim_boost = 0;
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

				//移動距離を保存
				if ((acs_left * MOVE_SPPED) + (acs_right * MOVE_SPPED) != 0)
				{
					last_move_x = -(acs_left * MOVE_SPPED) + (acs_right * MOVE_SPPED);
				}

				//移動
				location.x = location.x - (acs_left * MOVE_SPPED) + (acs_right * MOVE_SPPED);
				if (para_flg == false)
				{
					location.y = location.y - (acs_up * RISE_SPPED) + (acs_down * FALL_SPPED);
				}
				else
				{
					location.y += 0.8f;
				}

				//画面端に行くとテレポート
				if (location.x < 0 - PLAYER_WIDTH)
				{
					location.x = SCREEN_WIDTH;
				}
				if (location.x > SCREEN_WIDTH)
				{
					location.x = 0 - PLAYER_WIDTH + 2;
				}

				//画面上に当たると跳ね返る
				if (location.y < 0)
				{
					location.y = 0;
					ReflectionPY();
				}

				//風船が0こになったなら
				if (balloon <= 0)
				{
					if (++damage < 10)
					{
						anim_boost = 15;
						if (last_input == 0)
						{
							enemy_state = DEATH_RIGHT;
						}
						else
						{
							enemy_state = DEATH_LEFT;
						}
					}
					else
					{
						//パラシュート状態に変化
						para_flg = true;
						damage = 11;
					}
				}
			}
		}
		else
		{
		para_flg = false;
		anim_boost = 15;
		if (last_move_x > 0)
		{
			enemy_state = DEATH_RIGHT;
		}
		else
		{
			enemy_state = DEATH_LEFT;
		}

		death_acs += 4;

		location.y += death_acs * FALL_SPPED;
		}
	}

	//フレームを計測する(10秒ごとにリセット)
	if (++frame > 600)
	{
		frame = 0;
	}

	//アニメーション
	if (frame % (20 - anim_boost) == 0 && enemy_state != E_FLY_LEFT && enemy_state != E_FLY_RIGHT)
	{
		enemy_anim++;
		if (enemy_anim > 3)
		{
			enemy_anim = 0;
		}
	}
	if (para_flg == true)
	{
		if (last_move_x < 0)
		{
			enemy_state = PARACHUTE_LEFT;
		}
		else
		{
			enemy_state = PARACHUTE_RIGHT;
		}
		if (frame % 15 == 0)
		{
			para_anim++;
			if (para_anim >= 2)para_anim = 2;
		}
	}
	//敵が海面より下へ行くと死亡
	if (location.y > UNDER_WATER && show_flg == true)
	{
		flg = false;
	}
}

void Enemy::Draw()const
{
	////敵の当たり判定の描画
	//DrawBoxAA(location.x, location.y+PLAYER_BALLOON_HEIGHT, location.x + PLAYER_WIDTH, location.y + PLAYER_HEIGHT, 0xff0000, TRUE);
	////敵の風船当たり判定の描画(仮)
	//DrawBox(location.x, location.y, location.x + PLAYER_WIDTH, location.y + PLAYER_BALLOON_HEIGHT, 0x00ff00, TRUE);
	DrawFormatString(0, 20, 0x00ff00, "%d", test_score);
	//DrawFormatString(0, 40, 0x00ff00, "%f", ref_y);
	//DrawFormatString(0, 60, 0x00ff00, "%d", balloon);
	//DrawFormatString(0, 80, 0xffff00, "%d", onshare_flg);

	if (show_flg == true)
	{
		if (flg == true)
		{
			//プレイヤーの描画
			switch (enemy_state)
			{
			case E_IDOL_RIGHT:
				DrawGraph(location.x - IMAGE_SHIFT_X, location.y - IMAGE_SHIFT_Y, enemy_image[0], TRUE);
				break;
			case E_IDOL_LEFT:
				DrawTurnGraph(location.x - IMAGE_SHIFT_X, location.y - IMAGE_SHIFT_Y, enemy_image[0], TRUE);
				break;
			case CHARGE_RIGHT:
				DrawGraph(location.x - IMAGE_SHIFT_X, location.y - IMAGE_SHIFT_Y, enemy_image[0 + (enemy_anim % 2) + charge], TRUE);
				break;
			case CHARGE_LEFT:
				DrawTurnGraph(location.x - IMAGE_SHIFT_X, location.y - IMAGE_SHIFT_Y, enemy_image[0 + (enemy_anim % 2) + charge], TRUE);
				break;
			case E_FLY_RIGHT:
				DrawTurnGraph(location.x - IMAGE_SHIFT_X, location.y - IMAGE_SHIFT_Y, enemy_image[8 + enemy_anim], TRUE);
				break;
			case E_FLY_LEFT:
				DrawGraph(location.x - IMAGE_SHIFT_X, location.y - IMAGE_SHIFT_Y, enemy_image[8 + enemy_anim], TRUE);
				break;
			case PARACHUTE_RIGHT:
				DrawTurnGraph(location.x - IMAGE_SHIFT_X, location.y - IMAGE_SHIFT_Y, enemy_image[16 + para_anim], TRUE);
				break;
			case PARACHUTE_LEFT:
				DrawGraph(location.x - IMAGE_SHIFT_X, location.y - IMAGE_SHIFT_Y, enemy_image[16 + para_anim], TRUE);
				break;
			case DEATH_RIGHT:
				DrawTurnGraph(location.x - IMAGE_SHIFT_X, location.y - IMAGE_SHIFT_Y, enemy_image[13 + (enemy_anim % 2)], TRUE);
				break;
			case DEATH_LEFT:
				DrawGraph(location.x - IMAGE_SHIFT_X, location.y - IMAGE_SHIFT_Y, enemy_image[13 + (enemy_anim % 2)], TRUE);
				break;
			}
		}
	}

}

void Enemy::HitStageCollision(const BoxCollider* box_collider)
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
	else if (my_y[0] < sub_y[1] &&
		sub_y[0] < my_y[1])
	{
		//PlayerがStageFloorより右へ行こうとした場合
		if (my_x[1] > sub_x[0] &&
			my_x[0] < sub_x[0])
		{
			//StageFloorより右には行けないようにする
			location.x = sub_x[0] - area.width-5;
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
			location.x = sub_x[1]+5;
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

bool Enemy::IsOnFloor(const BoxCollider* box_collider)const
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
		//敵がStageFloorより下へ行こうとした場合
		if (my_y[1] > sub_y[0] - 2 &&
			my_y[0] < sub_y[0])
		{
			ret = true;
		}
	}
	return ret;
}

void Enemy::OnFloor()
{
	acs_down = 0;
}
void Enemy::ReflectionMX()
{
	acs_left = fabsf(acs_right - acs_left) * 0.8f;
	acs_right = 0;
}

void Enemy::ReflectionPX()
{
	acs_right = fabsf(acs_right - acs_left) * 0.8f;
	acs_left = 0;
}

void Enemy::ReflectionPY()
{
	acs_down = fabsf(acs_up - acs_down) * 1.8f;
	acs_up = 0;
}

int Enemy::ApplyDamege()
{
	if (protect < 0)
	{
		if (balloon > 0)
		{
			BalloonDec();
			return 500;
		}
		else
		{
			if (enemy_state == PARACHUTE_LEFT || enemy_state == PARACHUTE_RIGHT)
			{
				EnemyDeath();
				return 1000;
			}
			if (enemy_state == E_IDOL_LEFT || enemy_state == E_IDOL_RIGHT || enemy_state == CHARGE_LEFT || enemy_state == CHARGE_RIGHT)
			{
				EnemyDeath();
				return 750;
			}
		}
	}
	else
	{
		return 0;
	}
}

void Enemy::BalloonDec()
{
	--balloon;
}

void Enemy::EnemyDeath()
{
	death_flg = true;
}

void Enemy::EnemyMoveRight()
{

	move_right_flg = true;
	move_left_flg = false;
}

void Enemy::EnemyMoveLeft()
{
	move_left_flg = true;
	move_right_flg = false;
}

void Enemy::EnemyMoveStop()
{
	move_left_flg = false;
	move_right_flg = false;
}
void Enemy::EnemyJump()
{
	jump_flg = true;
}

void Enemy::EnemyJumpStop()
{
	jump_flg = false;
}

void Enemy::EnemyReset()
{
	acs_left = 0;
	acs_right = 0;
	acs_up = 0;
	acs_down = 0;
	jump_int = 0;
	jump_combo = 0;
	jump_cd = 0;
	wait_time = (GetRand(100) + 300) - (enemy_level * 30);
	para_flg = false;
	charge = 0;
	damage = 0;
	move_right_flg = false;
	move_left_flg = false;
	jump_flg = false;
	ref_once_left = false;
	ref_once_right = false;
	levelup_once = false;
}

void Enemy::EnemyLevelUp()
{
	if (enemy_level < 3)
	{
		enemy_level++;
	}
	switch (enemy_level)
	{
	case 1:
		LoadDivGraph("images/Enemy/Enemy_P_Animation.png", 20, 8, 4, 64, 64, enemy_image);
		break;
	case 2:
		LoadDivGraph("images/Enemy/Enemy_G_Animation.png", 20, 8, 4, 64, 64, enemy_image);
		break;
	case 3:
		LoadDivGraph("images/Enemy/Enemy_R_Animation.png", 20, 8, 4, 64, 64, enemy_image);
		break;
	}
}