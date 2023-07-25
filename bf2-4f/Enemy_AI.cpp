#include <stdio.h>
#include "Enemy_AI.h"

ENEMY_AI::ENEMY_AI()
{
	P_x = 100;
	P_y = 100;
	E_x = 200;
	E_y = 200;
	// パターンのリセット
	pattern = 0;
}
ENEMY_AI::~ENEMY_AI()
{

}
int ENEMY_AI::Update(int px, int py, int ex, int ey)
{
	P_x = px;
	P_y = py;
	E_x = ex;
	E_y = ey;

	pattern = 0;

    // プレイヤーがどの方向にいるか(x座標)
	if (E_x > P_x != E_x - P_x >= SCREEN_WIDTH / 2) {
		pattern += 0;
	}
	else
	{
		pattern += 1;
	}

	// プレイヤーがどの方向にいるか(y座標)
	if (E_y >= P_y - 50) {
		pattern += 0;
	}
	else
	{
		pattern += 2;
	}

	// プレイヤーが真下にいるなら回避行動をとる
	if (E_x >= P_x - 30 && E_x <= P_x + 30 && E_y >= P_y)
	{
		pattern = 4;
	}

	//パターンを返す
	return pattern;
}