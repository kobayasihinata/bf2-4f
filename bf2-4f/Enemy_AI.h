#pragma once
#include "Define.h"

class ENEMY_AI {
private:
	int P_x, P_y; // �v���C���[���W
	int E_x, E_y; // �G���W
	int pattern;  // �s���p�^�[��(0:����,1:�E��,2:����,3:�E��)
	const int AI_Cool_Base[3]{ 360,240,120 }; // �G���x�����Ƃ�AI�̎擾����
	int AI_Cool;     // AI�擾�҂�����
	int ai_cool_cnt; // AI�擾�҂�����(�J�E���g�p)
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