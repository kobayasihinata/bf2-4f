#pragma once

class Enemy_AI {
private:
	int P_x, P_y; // �v���C���[���W
	int E_x, E_y; // �G���W
	int pattern;  // �s���p�^�[��(0:�E��,1:����,2:�E��,3:����,4:���)

public:
	Enemy_AI();
	~Enemy_AI();
	void Update();
};