#include"SoapBubble.h"

//コンストラクタ
SoapBubble::SoapBubble()
{
	flg = false;
	location.x = 0;
	location.y = UNDER_WATER;
	area.width = 32;
	area.height = 32;
	LoadDivGraph("images/Stage/Stage_BubbleAnimation.png", 4, 4, 1, 64, 64, bubble_image);
	getscore_image = LoadGraph("images/Score/GetScore_500.png");
	getscore_anim = 0;
	getscore_x = 0;
	getscore_y = 0;
	is_getscore = false;
	bubble_anim = 0;
	bubble_get_anim = 3;
	frame = 0;
	acs_left = 0;
	acs_right = 0;
	get_once = false;
}

//デストラクタ
SoapBubble::~SoapBubble()
{
	for (int i = 0; i < 4; i++)
	{
		DeleteGraph(bubble_image[i]);
	}
}

void SoapBubble::Update()
{
	if (flg == true)
	{
		if (frame % 20 == 0)
		{
			bubble_anim++;
			if (bubble_anim > 2)
			{
				bubble_anim = 0;
			}
		}
		if (--location.y < -40)
		{
			flg = false;
		}
		//150フレームごとにフレーム測定リセット
		if (++frame > 150)
		{
			frame = 0;
		}
		//左右に風船を左右に揺らす
		if (frame < 75)
		{
			acs_left++;
			if (acs_right > 0)
			{
				acs_right-=2;
			}
		}
		else
		{
			acs_right++;
			if (acs_left > 0)
			{
				acs_left-=2;
			}
		}
		//横移動
		location.x = location.x + (acs_right * 0.01) - (acs_left * 0.01);
	}
	else
	{
		if (++bubble_get_anim > 3)
		{
			bubble_get_anim =4;
		}
	}
	if (is_getscore == true)
	{
		if (++getscore_anim > 180)
		{
			is_getscore = false;
			get_once == true;
			getscore_anim = 0;
		}
	}
}

void SoapBubble::Draw() const
{
	if (flg == true && get_once == false)
	{
		DrawGraph(location.x-16, location.y-16, bubble_image[bubble_anim], TRUE);
		DrawBox(location.x, location.y, location.x + area.width, location.y + area.height, 0x00ff00, false);
	}
	if (bubble_get_anim < 3 && get_once == false)
	{
		DrawGraph(location.x - 16, location.y - 16, bubble_image[3], TRUE);
	}
	if (is_getscore == true)
	{
		DrawGraph(getscore_x, getscore_y, getscore_image, TRUE);
	}
}
int SoapBubble::HitPlayerCollision(const BoxCollider* box_collider)
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

	if (my_x[0] < sub_x[1] && my_x[1]>sub_x[0] && my_y[0]<sub_y[1] && my_y[1]>sub_y[0] && flg == true && get_once == false)
	{
		is_getscore = true;
		getscore_x = sub_x[0];
		getscore_y = sub_y[0];
		flg = false;
		bubble_get_anim = 0;
		return SOAPBUBBLE_GETPOINT;
	}
	return 0;
}
void SoapBubble::SoapBubbleSpawn(int x)
{
	if (flg == false)
	{
		flg = true;
		location.x = x;
	}
}