#pragma once

class Enemy_AI {
private:
	int P_x, P_y; // プレイヤー座標
	int E_x, E_y; // 敵座標
	int pattern;  // 行動パターン(0:右上,1:左上,2:右下,3:左下,4:回避)

public:
	Enemy_AI();
	~Enemy_AI();
	void Update();
};