#include "Dxlib.h"
#include <math.h>
#include <time.h>
#include "Enemy.h"
#include "PadInput.h"

Enemy::Enemy(int x,int y,int level)
{
	flg = true;
	location.x = x;
	location.y = y;
	area.height = PLAYER_ENEMY_HEIGHT;
	area.width = PLAYER_ENEMY_WIDTH;
	acs_left = 0;
	acs_right = 0;
	acs_up = 0;
	acs_down = 0;
	jump_int = 0;
	jump_combo = 0;
	jump_cd = 0;
	for (int i = 0; i < 5; i++)
	{
		getscore_anim[i] = 0;
		is_getscore[i] = false;
		switch (i)
		{
		case 0:
			getscore[i] = 500;
			getscore_image[i] = LoadGraph("images/Score/GetScore_500.png");
			break;
		case 1:
			getscore[i] = 750;
			getscore_image[i] = LoadGraph("images/Score/GetScore_750.png");
			break;
		case 2:
			getscore[i] = 1000;
			getscore_image[i] = LoadGraph("images/Score/GetScore_1000.png");
			break;
		case 3:
			getscore[i] = 1500;
			getscore_image[i] = LoadGraph("images/Score/GetScore_1500.png");
			break;
		case 4:
			getscore[i] = 2000;
			getscore_image[i] = LoadGraph("images/Score/GetScore_2000.png");
			break;
		}
	}
	frame = 0;
	balloon = 0;
	wait_time = 0;
	wait_flg = true;
	charge = 0;
	enemy_level = level;
	first_flg = true;
	levelup_once = false;
	para_flg = false;
	death_flg = false;
	death_acs = -120;
	death_wait = 120;      //死亡後の待ち時間
	underwater_flg = false;      //水没中か判断
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
		LoadDivGraph("images/Enemy/Enemy_P_Animation.png", 18, 6, 3, 64, 64, enemy_image);
		break;
	case 2:
		LoadDivGraph("images/Enemy/Enemy_G_Animation.png", 18, 6, 3, 64, 64, enemy_image);
		break;
	case 3:
		LoadDivGraph("images/Enemy/Enemy_R_Animation.png", 18, 6, 3, 64, 64, enemy_image);
		break;
	}
	LoadDivGraph("images/Stage/Stage_SplashAnimation.png", 3, 3, 1, 64, 32, splash_image);
	enemy_anim = 0;
	para_anim = 0;
	splash_anim = 0;
	anim_boost = 0;

	last_move_x = 1;
	last_input = 1;

	test_score = 0;

}

Enemy::~Enemy()
{
	for (int i = 0; i < 18; i++)
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
			//パラシュート着地後の待機時間処理
			if (--wait_time >= 0)
			{
				wait_flg = true;
				if (last_input == -1)
				{
					enemy_state = E_IDOL_LEFT;
				}
				else if(last_input == 1)
				{
					enemy_state = E_IDOL_RIGHT;
				}
			}
			//風船を膨らませる	
			else if (charge < 6)
			{
				anim_boost = 0;
				if (last_input == -1)
				{
					enemy_state = CHARGE_LEFT;
				}
				else if(last_input == 1)
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
						wait_flg = false;
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
						wait_flg = false;
					}
				}

				//落下(床と触れていない事を検知する)
				if (onshare_flg == false)
				{
					if (last_input < 0)
					{
						enemy_state = E_FLY_LEFT;
					}
					else if(last_input > 0)
					{
						enemy_state = E_FLY_RIGHT;
					}

					//落下し続ける程下に加速
					if (acs_down < E_Max_Speed[enemy_level - 1])
					{
						acs_down += 1;
					}
					onfloor_flg = false;
				}
				//床に触れているときの処理
				else
				{
					if (last_input == -1)
					{
						enemy_state = E_FLY_LEFT;
						EnemyMoveLeft();
						EnemyJump();
						SetNot_AI(50);
					}
					else if(last_input == 1)
					{
						enemy_state = E_FLY_RIGHT;
						EnemyMoveRight();
						EnemyJump();
						SetNot_AI(50);
					}
					onfloor_flg = true;
					OnFloor();
					if (para_flg == true)
					{
						EnemyReset();
					}
				}

				//右入力されている時の処理
				if (/*PAD_INPUT::GetLStick().ThumbX > 10000 || */move_right_flg == true)
				{
					last_input = 1;
					if (acs_right < E_Max_Speed[enemy_level - 1])
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
				if (/*PAD_INPUT::GetLStick().ThumbX < -10000 || */move_left_flg == true)
				{
					last_input = -1;
					if (acs_left < E_Max_Speed[enemy_level - 1])
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
				if (/*PAD_INPUT::OnPressed(XINPUT_BUTTON_B) || */jump_flg == true && para_flg == false)
				{
					if (/*PAD_INPUT::GetLStick().ThumbX > 10000 || */move_left_flg == true)
					{
						if (acs_left < E_Max_Speed[enemy_level - 1])
						{
							acs_left += 3;
							acs_up -= 2;
						}
						if (acs_right > 0)
						{
							acs_right--;
						}
					}
					if (/*PAD_INPUT::GetLStick().ThumbX < -10000 || */move_right_flg == true)
					{
						if (acs_right < E_Max_Speed[enemy_level - 1])
						{
							acs_right += 3;
							acs_up -= 2;
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
						if (acs_up < E_Max_Speed[enemy_level - 1] / 2)
						{
							acs_up += jump_combo * 3 + balloon;
						}
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
				if (underwater_flg == false)
				{
					location.x = location.x - (acs_left * MOVE_SPPED) + (acs_right * MOVE_SPPED);
					if (para_flg == false)
					{
						location.y = location.y - (acs_up * RISE_SPPED) + (acs_down * FALL_SPPED);
					}
					else
					{
						location.y = location.y - (acs_up * RISE_SPPED) + (acs_down * (FALL_SPPED/2));
					}
					
				}

				//画面端に行くとテレポート
				if (location.x < 0 - PLAYER_ENEMY_WIDTH)
				{
					location.x = SCREEN_WIDTH;
				}
				if (location.x > SCREEN_WIDTH)
				{
					location.x = 0 - PLAYER_ENEMY_WIDTH + 2;
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
						if (last_input == 1)
						{
							enemy_state = DEATH_RIGHT;
						}
						else if (last_input == -1)
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
		//スコア取得時演出用
		for (int i = 0; i < 5; i++)
		{
			if (is_getscore[i] == true)
			{
				if (++getscore_anim[i] > 180)
				{
					is_getscore[i] = false;
					getscore_anim[i] = 0;
				}

			}
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
		underwater_flg = true;
		is_die = true;
		enemy_state = E_SUBMERGED;
		location.y = 471;
		if (frame % 10 == 0)
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
			flg = false;
			show_flg = false;
		}
	}
}

void Enemy::Draw()const
{

	if (show_flg == true)
	{
		if (flg == true)
		{
			//敵の描画
			switch (enemy_state)
			{
			case E_IDOL_RIGHT:
				DrawGraphF(location.x - IMAGE_SHIFT_X, location.y - IMAGE_SHIFT_Y, enemy_image[0], TRUE);
				break;
			case E_IDOL_LEFT:
				DrawTurnGraphF(location.x - IMAGE_SHIFT_X, location.y - IMAGE_SHIFT_Y, enemy_image[0], TRUE);
				break;
			case CHARGE_RIGHT:
				DrawGraphF(location.x - IMAGE_SHIFT_X, location.y - IMAGE_SHIFT_Y, enemy_image[0 + (enemy_anim % 2) + charge], TRUE);
				break;
			case CHARGE_LEFT:
				DrawTurnGraphF(location.x - IMAGE_SHIFT_X, location.y - IMAGE_SHIFT_Y, enemy_image[0 + (enemy_anim % 2) + charge], TRUE);
				break;
			case E_FLY_RIGHT:
				DrawTurnGraphF(location.x - IMAGE_SHIFT_X, location.y - IMAGE_SHIFT_Y, enemy_image[8 + enemy_anim], TRUE);
				break;
			case E_FLY_LEFT:
				DrawGraphF(location.x - IMAGE_SHIFT_X, location.y - IMAGE_SHIFT_Y, enemy_image[8 + enemy_anim], TRUE);
				break;
			case PARACHUTE_RIGHT:
				DrawTurnGraphF(location.x - IMAGE_SHIFT_X, location.y - IMAGE_SHIFT_Y, enemy_image[15 + para_anim], TRUE);
				break;
			case PARACHUTE_LEFT:
				DrawGraphF(location.x - IMAGE_SHIFT_X, location.y - IMAGE_SHIFT_Y, enemy_image[15 + para_anim], TRUE);
				break;
			case DEATH_RIGHT:
				DrawTurnGraphF(location.x - IMAGE_SHIFT_X, location.y - IMAGE_SHIFT_Y, enemy_image[13 + (enemy_anim % 2)], TRUE);
				break;
			case DEATH_LEFT:
				DrawGraphF(location.x - IMAGE_SHIFT_X, location.y - IMAGE_SHIFT_Y, enemy_image[13 + (enemy_anim % 2)], TRUE);
				break;
			case E_SUBMERGED:
				DrawGraphF(location.x - IMAGE_SHIFT_X, location.y - IMAGE_SHIFT_Y-45, splash_image[0 + splash_anim], TRUE);
				break;
			}
			for (int i = 0; i < 5; i++)
			{
				if (is_getscore[i] == true)
				{
					DrawGraph(getscore_x[i], getscore_y[i], getscore_image[i], TRUE);
				}
			}
		}
	}
	DrawFormatString(location.x, location.y, 0xffff00, "%d", enemy_state);
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

int Enemy::HitEnemyCollision(const BoxCollider* box_collider)
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

	//敵の横の範囲内
	if (my_x[0] < sub_x[1] - 5 &&
		sub_x[0] + 5 < my_x[1])
	{
		//敵が他の敵より下へ行こうとした場合
		if (my_y[1] > sub_y[0] &&
			my_y[0] < sub_y[0])
		{
			//敵より下には行けないようにする
			location.y = sub_y[0] - area.height;
			return 4;
		}

		//敵が他の敵より上へ行こうとした場合
		if (my_y[0] < sub_y[1] &&
			my_y[1] > sub_y[1])
		{
			return 3;
		}
	}

	//敵の縦の範囲内
	if (my_y[0] < sub_y[1] - 5 &&
		sub_y[0] + 5 < my_y[1])
	{
		//敵が他の敵より右へ行こうとした場合
		if (my_x[1] > sub_x[0] &&
			my_x[0] < sub_x[0])
		{
			//敵より右には行けないようにする
			location.x = sub_x[0] - area.width - 1;
			return 1;
		}

		//敵が他の敵より左へ行こうとした場合
		if (my_x[0] < sub_x[1] &&
			my_x[1]>sub_x[1])
		{
			//敵より左には行けないようにする
			location.x = sub_x[1] + 1;
			return 2;
		}
	}
	return 0;
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
	last_input *= -1;
	acs_left = fabsf(acs_right - acs_left) * 0.8f;
	acs_right = 0;
}

void Enemy::ReflectionPX()
{
	last_input *= -1;
	acs_right = fabsf(acs_right - acs_left) * 0.8f;
	acs_left = 0;
}

void Enemy::ReflectionPY()
{
	acs_down = fabsf(acs_up - acs_down) * 1.8f;
	acs_up = 0;
}

void Enemy::ReflectionMY()
{
	acs_up = fabsf(acs_up - acs_down) * 1.1f;
	acs_down = 0;
}

int Enemy::ApplyDamege()
{
	if (protect < 0)
	{
		if (balloon > 0)
		{
			BalloonDec();
			GetScoreStart(0);
			return getscore[0+enemy_level-1];
		}
		else
		{
			if (enemy_state == PARACHUTE_LEFT || enemy_state == PARACHUTE_RIGHT)
			{
				EnemyDeath();
				GetScoreStart(2);
				return getscore[2 + enemy_level-1];
			}
			if (enemy_state == E_IDOL_LEFT || enemy_state == E_IDOL_RIGHT || enemy_state == CHARGE_LEFT || enemy_state == CHARGE_RIGHT)
			{
				EnemyDeath();
				GetScoreStart(1);
				return getscore[1 + enemy_level - 1];
			}
		}
	}
	return 0;
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
	death_acs = -120;
	death_wait = 120;
	charge = 0;
	damage = 0;
	move_right_flg = false;
	move_left_flg = false;
	jump_flg = false;
	ref_once_left = false;
	ref_once_right = false;
	levelup_once = false;
	underwater_flg = false;
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
		LoadDivGraph("images/Enemy/Enemy_P_Animation.png", 18, 6, 3, 64, 64, enemy_image);
		break;
	case 2:
		LoadDivGraph("images/Enemy/Enemy_G_Animation.png", 18, 6, 3, 64, 64, enemy_image);
		break;
	case 3:
		LoadDivGraph("images/Enemy/Enemy_R_Animation.png", 18, 6, 3, 64, 64, enemy_image);
		break;
	}
}

void Enemy::SetNot_AI(int No_time)
{
	srand(time(NULL));
	int percent = (rand() % 100 + 51);
	no_ai_time = ( No_time * percent / 100);
}

int Enemy::No_AI_Flg() {
	if (--no_ai_time > 0) {
		return true;
	}
	else
	{
		no_ai_time = 0;
		return false;
	}
}

void Enemy::GetScoreStart(int i)
{
	is_getscore[i + enemy_level - 1] = true;
	getscore_x[i + enemy_level - 1] = location.x;
	getscore_y[i + enemy_level - 1] = location.y;
}