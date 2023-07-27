#pragma once
#include "Enemy.h"

class ENEMY_AI {
private:
	int P_x, P_y; // �v���C���[���W
	int E_x, E_y; // �G���W
	int pattern;  // �s���p�^�[��(0:����,1:�E��,2:����,3:�E��)

public:
	ENEMY_AI();
	~ENEMY_AI();
	int Update(int px, int py, int ex, int ey);
	void Reverse();
	int GetPattern() { return pattern; }
};