#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Enemy_AI.h"


ENEMY_AI::ENEMY_AI()
{
	P_x = 0;
	P_y = 0;
	E_x = 0;
	E_y = 0;
	
	//Set_AI_Cool(2);

	pattern = 0;
}
ENEMY_AI::~ENEMY_AI()
{

}
int ENEMY_AI::Update(int px, int py, int ex, int ey)
{
	if (ai_cool_cnt < AI_Cool)
	{
		pattern = 99;
		return pattern;
	}

	P_x = px;
	P_y = py;
	E_x = ex;
	E_y = ey;

	// パターンのリセット
	pattern = 0;

    // プレイヤーがどの方向にいるか(x座標)
	if (E_x > P_x) {
		pattern += 0;
	}
	else
	{
		pattern += 1;
	}

	// 距離が画面の半分以上離れていたら方向反転
	if (abs(E_x - P_x) > SCREEN_WIDTH / 2) {
		Reverse_x();
	}

	// プレイヤーがどの方向にいるか(y座標)
	if (E_y >= P_y - 25) {
		pattern += 0;
	}
	else
	{
		pattern += 2;
	}


	// 3割の確率で移動方向反転(x)
	srand(time(NULL));
	if (rand() % 100 < 30) {
		Reverse_x();
		reverse == 1;
	}

	// 3割の確率で移動方向反転(y)
	srand(time(NULL));
	if (rand() % 100 < 30) {
		Reverse_y();
		reverse = 1;
	}

	//パターンを返す
	return pattern;
}

void ENEMY_AI::Reverse_x(){
	if (pattern % 2 == 0) {
		pattern++;
	}else{
		pattern--;
	}
}

void ENEMY_AI::Reverse_y() {
	if (pattern / 2 == 0) {
		pattern = pattern + 2;
	}
	else {
		pattern = pattern - 2;
	}
}

void ENEMY_AI::Set_AI_Cool(int Level)
{
	srand(time(NULL));
	int percent = (rand() % 100 + 51);
	AI_Cool = (AI_Cool_Base[Level] * percent / 100);
	if (reverse) {
		ai_cool_cnt = AI_Cool_Base[Level] / 2;
		reverse = 0;
	}else{
		ai_cool_cnt = 0;
	}
}

int ENEMY_AI::Move_Rand()
{

}