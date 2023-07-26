#include "Thunder.h"
#include<math.h>
#include"DxLib.h"
#include"Define.h"

#define DEBUG

Thunder::Thunder()
{
	location.x = 100;
	location.y = 100;
	area.height = 21;
	area.width = 21;

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
	thunder_state = 3;
	thunder_ball_state = Stop;

	thunder_ball_flg = false;
	fire_flg = false;
	is_fire_ready = false;
	thunder_state_flg = false;

	show_flg = true;

}

Thunder::~Thunder()
{

}

void Thunder::Update()
{
	if (thunder_state_flg == false)
	{
		thunder_state = GetRand(3);
		thunder_state_flg = true;
	}

	if (--fire_timer < 0)
	{
		is_fire_ready = true;
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
		else
		{
			cloud_anim = 0;
		}
	}

	if (is_fire_ready == true)
	{
		if (--preliminary_action_time < 0)
		{
			fire_flg = true;		
		}
	}

	if (fire_flg == true)
	{
		is_fire_ready = false;
		if (++anim_frame % 3 == 0)
		{
			if (thunder_anim < 5)
			{
				thunder_anim++;
			}
			else
			{
				thunder_ball_flg = true;
			}
		}
	}

	if (thunder_ball_flg==true)
	{
		fire_flg = false;
		//thunder_state_flg = false;
		fire_timer = SECOND_TO_FRAME(30);
		preliminary_action_time = SECOND_TO_FRAME(1);
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

	if (thunder_ball_state != Stop)
	{
		location.x += move_x;
		location.y += move_y;
	}
	else
	{
		//show_flg = false;
	}
}

void Thunder::Draw()const
{
#ifdef DEBUG
	DrawFormatString(0, 200, 0xff00ff, "%d", fire_timer);
	DrawFormatString(0, 220, 0xff00ff, "%d", preliminary_action_time);
	DrawFormatString(0, 240, 0xff00ff, "%d", thunder_state);
	BoxCollider::Draw();
#endif // DEBUG

	DrawGraphF(cloud_x, cloud_y, cloud_image[cloud_anim], TRUE);
	if (fire_flg == true)
	{
		//•\Ž¦êŠ‚ÍŽžŒv‰ñ‚è
		switch (thunder_state)
		{
		case 0:
			DrawRotaGraphF(cloud_x + 100, cloud_y - 10, 1, M_PI / 180 * 190, thunder_image[thunder_anim], TRUE);
			break;
		case 1:
			DrawRotaGraphF(cloud_x + 100, cloud_y + 80, 1, M_PI / 180 * 340, thunder_image[thunder_anim], TRUE, TRUE);
			break;
		case 2:
			DrawRotaGraphF(cloud_x+25, cloud_y + 80, 1, M_PI / 180 * 20, thunder_image[thunder_anim], TRUE);
			break;
		case 3:
			DrawRotaGraphF(cloud_x + 20, cloud_y - 10 , 1, M_PI / 180 * 170, thunder_image[thunder_anim], TRUE, TRUE);
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

void Thunder::ChangeAngle()
{
	float rad = angle * (float)M_PI * 2;
	move_x = speed * cosf(rad);
	move_y = speed * sinf(rad);
}

void Thunder::Reflection(const BoxCollider* boxcollider)
{
	if (location.x < 0 || location.x > SCREEN_WIDTH - area.width)
	{
		if (location.x < 0)
		{
			location.x = 0;
		}
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
}