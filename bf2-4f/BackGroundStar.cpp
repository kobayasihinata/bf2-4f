#include"BackGroundStar.h"

BackGroundStar::BackGroundStar(int stage)
{
    type = stage;
    star_pos.x = 0;
    star_pos.y = 0;
    star_color = 0;
    star_drawtime = 0;
}

BackGroundStar::~BackGroundStar()
{

}

void BackGroundStar::Update()
{
    if (--star_drawtime <= 0)
    {
        star_pos.x = GetRand(SCREEN_WIDTH);
        star_pos.y = GetRand(SCREEN_HEIGHT);
        star_drawtime = GetRand(30)+30;
        SetColor(type);
    }
}

void BackGroundStar::Draw()const
{
    DrawBoxAA(star_pos.x, star_pos.y, star_pos.x + 2.5f, star_pos.y + 2.5f, star_color, true);
}

void BackGroundStar::SetColor(int type)
{
    //緑色のパターンの中から抽選
    if (type <= 2)
    {
        switch (GetRand(3))
        {
        case 0:
            star_color = GetColor(7,195,35);
            break;
        case 1:
            star_color = GetColor(47, 166, 65);
            break;
        case 2:
            star_color = GetColor(88, 155, 98);
            break;
        case 3:
            star_color = GetColor(180, 207, 178);
            break;
        }
    }
    //茶色のパターンの中から抽選
    else
    {
        switch (GetRand(3))
        {
        case 0:
            star_color = GetColor(151, 71, 10);
            break;
        case 1:
            star_color = GetColor(147, 96, 57);
            break;
        case 2:
            star_color = GetColor(197, 179, 152);
            break;
        case 3:
            star_color = GetColor(70, 52, 36);
            break;
        }
    }
}