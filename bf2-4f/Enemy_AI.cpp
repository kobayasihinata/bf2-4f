#include "DxLib.h"
#include "Enemy_AI.h"


ENEMY_AI::ENEMY_AI()
{
	P_x = 0;
	P_y = 0;
	E_x = 0;
	E_y = 0;
	
	AI_Cool = 0;

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
	if (GetRand(100) < 10) {
		Reverse_x();
		reverse == 1;
	}

	// 3割の確率で移動方向反転(y)
	if (GetRand(100) < 10) {
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
	int ai_cool_base = AI_Cool_Base[Level];
	if (reverse) {
		ai_cool_base = ai_cool_base / 2;
	}
	int percent = (GetRand(100) + 51);
	AI_Cool = (ai_cool_base * percent / 100);
}

int ENEMY_AI::AI_Cool_Update()
{
	--AI_Cool;
	return AI_Cool;
}

int ENEMY_AI::Move_Rand()
{
	pattern = GetRand(4);
	return pattern;
}