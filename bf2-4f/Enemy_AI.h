#pragma once
#include "Define.h"

class ENEMY_AI {
private:
	int P_x, P_y; // プレイヤー座標
	int E_x, E_y; // 敵座標
	int pattern;  // 行動パターン(0:左上,1:右上,2:左下,3:右下)
	bool reverse;
	const int AI_Cool_Base[4]{ 0,600,400,200 }; // 敵レベルごとのAIの取得時間
	int AI_Cool;     // AI取得待ち時間
public:
	ENEMY_AI();
	~ENEMY_AI();
	int Update(int px, int py, int ex, int ey);
	void Reverse_x();
	void Reverse_y();
	void Set_AI_Cool(int Level);
	int AI_Cool_Update();
	int Move_Rand();
	int GetPattern() { return pattern; }
};