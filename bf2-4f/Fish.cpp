#include "Fish.h"
#include"DxLib.h"
#include"Define.h"

Fish::Fish()
{
	LoadDivGraph("images/Enemy/Enemy_FishAnimation.png", 10, 6, 2, 64, 64, fish_image);
	location.x = 160;
	location.y = 430;
	area.height = 55;
	area.width = 60;
	probability = 0;
	speed = 2 * 1.7f;
	fps_timer = 0;
	player_flying_timer = SECOND_TO_FRAME(3);
	fish_state = Rising_Fish_3;
	is_rising = false;
	is_preyed_on_any = false;
	is_preyey_on_enemy = false;
}

Fish::~Fish()
{

}

void Fish::Update(const BoxCollider* boxcollider)
{
	if (is_rising == false && is_preyed_on_any == false)
	{
		if (++fps_timer % 10 == 0)
		{
			probability = GetRand(99);
		}
	}

	//ŠC–Ê‚É‚¢‚é‚Æ‚«
	if (boxcollider->GetMin().x > SEASURFACE_START_X && boxcollider->GetMax().x < SEASURFACE_END_X &&
		/*		boxcollider->GetMax().y>SEA_SURFACE - boxcollider->GetArea().height &&*/
		is_preyed_on_any == false)
	{
		if (--player_flying_timer < 0 && probability < 10)
		{
			is_rising = true;
			if (boxcollider->GetMax().y - boxcollider->GetArea().height / 2 < location.y)
			{
				location.x = (boxcollider->GetLocation().x + boxcollider->GetArea().width / 2) - area.width / 2;
				location.y -= speed;

			}
			else
			{
				fish_state = PreyingOn_Player;
				is_rising = false;
				is_preyed_on_any = true;
			}
		}
	}
	else
	{
		player_flying_timer = SECOND_TO_FRAME(3);
	}
	
	if (is_preyed_on_any == true)
	{
		location.y += speed;
	}
}

void Fish::Draw()const
{
	BoxCollider::Draw();
	DrawFormatString(0, 100, 0xff00ff, "%d", player_flying_timer);
	DrawGraph(location.x, location.y - IMAGE_SHIFT, fish_image[fish_state], TRUE);
}