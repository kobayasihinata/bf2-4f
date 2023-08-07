#pragma once
#include "Define.h"

class ENEMY_AI {
private:
	int P_x, P_y; // プレイヤー座標
	int E_x, E_y; // 敵座標
	int pattern;  // 行動パターン(0:左上,1:右上,2:左下,3:右下)
	const int AI_Cool_Base[3]{ 360,240,120 }; // 敵レベルごとのAIの取得時間
	int AI_Cool;     // AI取得待ち時間
	int ai_cool_cnt; // AI取得待ち時間(カウント用)
public:
	ENEMY_AI();
	~ENEMY_AI();
	int Update(int px, int py, int ex, int ey);
	void Update_AI_Cool() { ++ai_cool_cnt; }
	void Reverse();
	void Set_AI_Cool(int Level);
	void Set_AI_Cool_Cnt(int Cnt) { ai_cool_cnt = Cnt; }
	int GetPattern() { return pattern; }
};