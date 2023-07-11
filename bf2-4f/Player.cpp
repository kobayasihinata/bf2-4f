#include "Dxlib.h"
#include "Player.h"
#include "PadInput.h"

#define SEA_SURFACE 470 //海面（仮）

#define MAX_SPEED 250		//最高速度と最低速度の差を調整する用
#define MAX_SPEED_LAND 100	//最高速度と最低速度の差を調整する用（地面）
#define MAX_JUMP 10			//最大連打数
#define JUMP_INTERVAL 40	//ジャンプボタン連打間隔
#define FALL_SPPED 0.002f	//最高落下速度
#define MOVE_SPPED 0.005f	//最高上昇速度
#define RISE_SPPED 0.01f	//最高上昇速度

#define LAND_SPEED 0.01f	//最高移動速度（地面）

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

		//落下(床と触れていない事を検知する)
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

			//落下し続ける程下に加速
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

		//右入力を検知
		if (PAD_INPUT::GetLStick().ThumbX > 10000 || CheckHitKey(KEY_INPUT_D))
		{
			//浮いているなら加速処理＆浮いていないなら慣性なし移動
			//(ここで地面との当たり判定を取得してきてstateを変える)
			if (onfloor_flg != true)
			{
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

		//左入力を検知
		if (PAD_INPUT::GetLStick().ThumbX < -10000 || CheckHitKey(KEY_INPUT_A))
		{
			//浮いているなら加速処理＆浮いていないなら慣性なし移動
			//(ここで地面との当たり判定を取得してきてstateを変える)
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

		//急転回判断
		if ((PAD_INPUT::GetLStick().ThumbX > 10000 || CheckHitKey(KEY_INPUT_D)) && last_move_x < 0 && onfloor_flg == TRUE)
		{
			player_state = TURN_LEFT;
		}
		if ((PAD_INPUT::GetLStick().ThumbX < -10000 || CheckHitKey(KEY_INPUT_A)) && last_move_x > 0 && onfloor_flg == TRUE)
		{
			player_state = TURN_RIGHT;
		}

		//ジャンプ
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
				//Aを押せば押すほど上加速度が上がる
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
		if ((acs_left * MOVE_SPPED) + (acs_right * MOVE_SPPED) + (land_acs_right * LAND_SPEED) - (land_acs_left * LAND_SPEED) != 0)
		{
			last_move_x = -(acs_left * MOVE_SPPED) + (acs_right * MOVE_SPPED) + (land_acs_right * LAND_SPEED) - (land_acs_left * LAND_SPEED);
		}
		//移動
		location.x = location.x - (acs_left * MOVE_SPPED) + (acs_right * MOVE_SPPED) + (land_acs_right * LAND_SPEED) - (land_acs_left * LAND_SPEED);
		location.y = location.y - (acs_up * RISE_SPPED) + (acs_down + ref_y) * FALL_SPPED;

		//画面端に行くとテレポート
		if (location.x < 0 - PLAYER_WIDTH)
		{
			location.x = SCREEN_WIDTH;
		}
		if (location.x > SCREEN_WIDTH)
		{
			location.x = 0 - PLAYER_WIDTH+2;
		}

		//画面上に当たると跳ね返る
		if (location.y < 0)
		{
			ReflectionPY();
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

		//アニメーション
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
	//死亡中の演出
	else
	{
		location.y++;
	}
	//プレイヤーが海面より下へ行くと残機 -1
	if (location.y > SEA_SURFACE)
	{
		life = life - 1;
		PlayerRespawn(100, 350);
	}
}

void Player::Draw()const
{
	//プレイヤーの描画
	DrawBoxAA(location.x, location.y+PLAYER_BALLOON_HEIGHT, location.x + PLAYER_WIDTH, location.y + PLAYER_HEIGHT, 0xff0000, TRUE);
	//プレイヤーの風船の描画(仮)
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
	if (my_y[0] < sub_y[1] &&
		sub_y[0] < my_y[1])
	{
		//PlayerがStageFloorより右へ行こうとした場合
		if (my_x[1] > sub_x[0] &&
			my_x[0] < sub_x[0])
		{
			//StageFloorより右には行けないようにする
			location.x = sub_x[0] - area.width;
			//1回だけ左へ跳ね返る
			if (ref_once1 == FALSE)
			{
				//跳ね返る
				ReflectionMX();
				ref_once1 = TRUE;
			}		
		}
		else
		{
			ref_once1 = FALSE;
		}
		//PlayerがStageFloorより左へ行こうとした場合
		if (my_x[0] < sub_x[1] &&
			my_x[1]>sub_x[1])
		{
			//StageFloorより左には行けないようにする
			location.x = sub_x[1];
			//1回だけ右へ跳ね返る
			if (ref_once2 == FALSE)
			{
				//跳ね返る
				ReflectionPX();
				ref_once2 = TRUE;
			}
		}
		else
		{
			ref_once2 = FALSE;
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