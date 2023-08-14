#pragma once
#include "Define.h"

class ENEMY_AI {
private:
	int P_x, P_y; // �v���C���[���W
	int E_x, E_y; // �G���W
	int pattern;  // �s���p�^�[��(0:����,1:�E��,2:����,3:�E��)
	bool reverse;
	const int AI_Cool_Base[4]{ 0,600,400,200 }; // �G���x�����Ƃ�AI�̎擾����
	int AI_Cool;     // AI�擾�҂�����
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