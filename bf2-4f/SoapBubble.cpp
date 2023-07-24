#include"SoapBubble.h"

//コンストラクタ
SoapBubble::SoapBubble()
{
	flg = false;
	location.x = 0;
	location.y = UNDER_WATER;
	area.width = 64;
	area.height = 64;
	LoadDivGraph("images/Stage/Stage_BubbleAnimation.png", 4, 4, 1, 64, 64, bubble_image);
	bubble_anim = 0;
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
		bubble_anim++;
		if (bubble_anim > 2)
		{
			bubble_anim = 0;
		}
		location.y--;
	}
}

void SoapBubble::Draw() const
{
	if (flg == true)
	{
		DrawGraph(location.x, location.y, bubble_image[bubble_anim], TRUE);
	}
}

void SoapBubble::SoapBubbleSpawn(int x)
{
	if (flg == false)
	{
		flg = true;
		location.x = x;
	}
}