#pragma once
#include "Enemy.h"

class ENEMY_AI {
private:
	int P_x, P_y; // プレイヤー座標
	int E_x, E_y; // 敵座標
	int pattern;  // 行動パターン(0:左上,1:右上,2:左下,3:右下)

public:
	ENEMY_AI();
	~ENEMY_AI();
	int Update(int px, int py, int ex, int ey);
	void Reverse();
	int GetPattern() { return pattern; }
};