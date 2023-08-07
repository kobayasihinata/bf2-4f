#include "Thunder.h"
#include<math.h>
#include"DxLib.h"
#include"Define.h"
#include"Player.h"

#define DEBUG

Thunder::Thunder()
{
	LoadDivGraph("images/Stage/Stage_CloudAnimation.png", 3, 3, 1, 128, 64, cloud_image);
	LoadDivGraph("images/Stage/Stage_ThunderAnimation.png", 6, 6, 1, 64, 64, thunder_image);
	LoadDivGraph("images/Stage/Stage_ThunderEffectAnimation.png", 3, 3, 1, 32, 32, thunder_ball_image);

	cloud_anim = 0;
	thunder_anim = 0;
	thunder_ball_anim = 0;

	anim_frame = 0;
#ifdef DEBUG
	fire_timer = SECOND_TO_FRAME(1);
	preliminary_action_time = SECOND_TO_FRAME(1);
#else
	fire_timer = SECOND_TO_FRAME(30);
	preliminary_action_time = SECOND_TO_FRAME(1);

#endif // DEBUG

	speed = 0;
	angle = 0;
	move_x = 0;
	move_y = 0;

	cloud_x = 300;
	cloud_y = 70;
	thunder_direction = 0;
	thunder_ball_state = Stop;

	thunder_ball_flg = false;
	fire_flg = false;
	is_fire_ready = false;
	thunder_direction_flg = false;

	location.x = cloud_x + 50;
	location.y = cloud_y + 20;
	area.height = 21;
	area.width = 21;

	show_flg = false;
	is_die = false;
}

Thunder::~Thunder()
{

}

void Thunder::Update()
{
	//方向が決まってないなら方向をランダムで取得する
	if (thunder_direction_flg == false)
	{
		thunder_direction = GetRand(3);
		thunder_direction_flg = true;
	}

	//一定時間経過で処理開始
	if (--fire_timer < 0)
	{
		is_fire_ready = true;
		//雷を発射してないなら光らせる
		if (fire_flg == false)
		{
			if (++anim_frame % 3 == 0)
			{
				if (cloud_anim < 2)
				{
					cloud_anim++;
				}
				else
				{
					cloud_anim = 1;
				}
			}
		}
		//雷を発射しているなら元の雨雲に戻す
		else
		{
			cloud_anim = 0;
		}
	}

	//雷を発射していいなら予備動作をした後に雷を発射
	if (is_fire_ready == true)
	{
		if (--preliminary_action_time < 0)
		{
			fire_flg = true;		
		}
	}

	//雷を発射しているなら
	if (fire_flg == true)
	{
		if (++anim_frame % 3 == 0)
		{
			if (thunder_anim < 5)
			{
				thunder_anim++;
				thunder_ball_flg = true;
			}
			else
			{
				fire_flg = false;
			}
		}
	}
	
	//雷の玉を発射しているなら
	if (thunder_ball_flg==true)
	{
		thunder_ball_state = Move;
		is_fire_ready = false;
		anim_frame = 0;
		speed = 2.5f;
		switch (thunder_direction)
		{
		case 0:
			//location.x = cloud_x + 95;
			//location.y = cloud_y - 30;
			//angle = 0.875f;
			location.x = cloud_x + 70;
			location.y = cloud_y - 30;
			angle = 0.8f;
			ChangeAngle();
			break;
		case 1:
			//location.x = cloud_x + 100;
			//location.y = cloud_y + 80;
			//angle = 0.125f;
			location.x = cloud_x + 75;
			location.y = cloud_y + 80;
			angle = 0.2f;
			ChangeAngle();
			break;
		case 2:
			//location.x = cloud_x + 5;
			//location.y = cloud_y + 90;
			//angle = 0.375f;
			location.x = cloud_x + 30;
			location.y = cloud_y + 90;
			angle = 0.3f;
			ChangeAngle();
			break;
		case 3:
			//location.x = cloud_x + 10;
			//location.y = cloud_y - 30;
			//angle = 0.625f;
			location.x = cloud_x + 30;
			location.y = cloud_y - 30;
			angle = 0.71f;
			ChangeAngle();
			break;
		default:
			break;
		}
		show_flg = true;
		thunder_ball_flg = false;
	}

	//雷の玉のアニメーション処理
	if (show_flg == true)
	{
		if (++anim_frame % 5 == 0)
		{
			if (thunder_ball_anim < 2)
			{
				thunder_ball_anim++;
			}
			else
			{
				thunder_ball_anim = 1;
			}
		}
	}

	//止まってないなら移動量加算
	if (thunder_ball_state != Stop)
	{
		location.x += move_x;
		location.y += move_y;
	}

	if (location.x < 0 || location.x > SCREEN_WIDTH - area.width)
	{
		//左
		if (location.x < 0)
		{
			location.x = 0;
		}
		//右
		else
		{
			location.x = SCREEN_WIDTH - area.width;
		}

		angle = (1 - angle) + 0.5f;

		if (angle > 1)
		{
			angle -= 1.0f;
		}

		ChangeAngle();
	}

	//上
	if (location.y < THUNDER_BALL_IMAGE_SHIFT)
	{
		angle = (1 - angle);
		ChangeAngle();
	}

	//下
	if (location.y + area.height > SCREEN_HEIGHT)
	{
		is_die = true;
	}

	//下に落ちた場合
	if (is_die == true)
	{
		InitThunder();
	}
}
		

void Thunder::Draw(bool flg)const
{
#ifdef DEBUG
	DrawFormatString(0, 200, 0xff00ff, "%d", fire_timer);
	DrawFormatString(0, 220, 0xff00ff, "%d", preliminary_action_time);
	DrawFormatString(0, 240, 0xff00ff, "%d", thunder_direction);
	BoxCollider::Draw();
#endif // DEBUG

	DrawGraphF(cloud_x, cloud_y, cloud_image[cloud_anim], TRUE);
	if (flg == false)
	{
		if (fire_flg == true)
		{
			//表示場所は時計回り
			switch (thunder_direction)
			{
			case 0:
				//DrawRotaGraphF(cloud_x + 100, cloud_y - 10, 1, M_PI / 180 * 190, thunder_image[thunder_anim], TRUE);
				DrawRotaGraphF(cloud_x + 80, cloud_y - 10, 1, M_PI / 180 * 170, thunder_image[thunder_anim], TRUE);
				break;
			case 1:
				DrawRotaGraphF(cloud_x + 90, cloud_y + 80, 1, M_PI / 180 * 10, thunder_image[thunder_anim], TRUE, TRUE);
				break;
			case 2:
				DrawRotaGraphF(cloud_x + 40, cloud_y + 85, 1, M_PI / 180 * -10, thunder_image[thunder_anim], TRUE);
				break;
			case 3:
				DrawRotaGraphF(cloud_x + 40, cloud_y - 10, 1, M_PI / 180 * 180, thunder_image[thunder_anim], TRUE, TRUE);
				break;
			default:
				break;
			}
		}
		if (show_flg == true)
		{
			DrawGraphF(location.x - THUNDER_BALL_IMAGE_SHIFT, location.y - THUNDER_BALL_IMAGE_SHIFT, thunder_ball_image[thunder_ball_anim], TRUE);
		}
	}
}

void Thunder::ChangeAngle()
{
	float rad = angle * (float)M_PI * 2;
	move_x = speed * (float)cos(rad);
	move_y = speed * (float)sin(rad);
}

void Thunder::Reflection(const BoxCollider* boxcollider)
{

	if (this->GetMin().x < boxcollider->GetMax().x - 5 &&
		this->GetMax().x>boxcollider->GetMin().x + 5)
	{
		//下
		if (this->GetMax().y > boxcollider->GetMin().y - 5 &&
			this->GetMin().y < boxcollider->GetMin().y + 5)
		{
			angle = (1 - angle);
			ChangeAngle();
		}

		//上
		if (this->GetMin().y - THUNDER_BALL_IMAGE_SHIFT < boxcollider->GetMax().y &&
			this->GetMax().y > boxcollider->GetMax().y)
		{
			angle = (1 - angle);
			ChangeAngle();
		}
	}

	if (this->GetMin().y < boxcollider->GetMax().y - 5 &&
		this->GetMax().y > boxcollider->GetMin().y + 5)
	{
		//右
		if (this->GetMax().x > boxcollider->GetMin().x &&
			this->GetMin().x < boxcollider->GetMin().x)
		{
			angle = (1 - angle) + 0.5f;
			if (angle > 1)
			{
				angle -= 1.0f;
			}
			ChangeAngle();
		}

		//左
		if (this->GetMin().x < boxcollider->GetMax().x &&
			this->GetMax().x > boxcollider->GetMax().x)
		{
			angle = (1 - angle) + 0.5f;
			if (angle > 1)
			{
				angle -= 1.0f;
			}
			ChangeAngle();
		}
	}
}

bool Thunder::HitPlayer(const Player* player)
{
	bool ret = false;

	if (this->GetMin().x < player->GetMax().x &&
		this->GetMax().x>player->GetMin().x &&
		this->GetMin().y < player->GetMax().y &&
		this->GetMax().y > player->GetMin().y &&
		this->show_flg == true)
	{
		ret = true;
	}

	return	ret;
}

void Thunder::InitThunder()
{
	cloud_anim = 0;
	thunder_anim = 0;
	thunder_ball_anim = 0;

	thunder_ball_flg = false;
	fire_flg = false;
	is_fire_ready = false;
	thunder_direction_flg = false;

#ifdef DEBUG
	fire_timer = SECOND_TO_FRAME(1);
	preliminary_action_time = SECOND_TO_FRAME(1);
#else
	fire_timer = SECOND_TO_FRAME(30);
	preliminary_action_time = SECOND_TO_FRAME(1);
#endif // DEBUG

	show_flg = false;
	speed = 0;
	angle = 0;
	thunder_ball_state = Stop;
	location.x = cloud_x + 50;
	location.y = cloud_y + 20;

	is_die = false;

}