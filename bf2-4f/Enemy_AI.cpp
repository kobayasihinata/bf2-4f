#include <stdio.h>
#include "Enemy_AI.h"

Enemy_AI::Enemy_AI()
{
	// やること:プレイヤー座標と敵の座標を更新
	P_x = 100;
	P_y = 100;
	E_x = 200;
	E_y = 200;
	// パターンのリセット
	pattern = 0;
}
Enemy_AI::~Enemy_AI()
{

}
void Enemy_AI::Update()
{
    // プレイヤーがどの方向にいるか(x座標)
	if (E_x > P_x) {
		pattern += 0;
	}
	else
	{
		pattern += 1;
	}

	// プレイヤーがどの方向にいるか(y座標)
	if (E_y >= P_y) {
		pattern += 0;
	}
	else
	{
		pattern += 2;
	}

	// プレイヤーが真下にいるなら回避行動をとる
	if (E_x >= P_x - 30 && E_x <= P_x + 30 && E_y >= P_y && E_y <= P_y + 50)
	{
		pattern = 4;
	}

	//パターンを返す
	return;
}