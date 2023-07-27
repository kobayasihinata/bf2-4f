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

	// �p�^�[���̃��Z�b�g
	pattern = 0;

    // �v���C���[���ǂ̕����ɂ��邩(x���W)
	if (E_x > P_x) {
		pattern += 0;
	}
	else
	{
		pattern += 1;
	}

	// ��������ʂ̔����ȏ㗣��Ă�����������]
	if (abs(E_x - P_x) > SCREEN_WIDTH / 2) {
		Reverse();
	}

	// 3���̊m���ňړ��������]
	srand(time(NULL));
	if (rand() % 100 < 3) {
		Reverse();
	}


	// �v���C���[���ǂ̕����ɂ��邩(y���W)
	if (E_y >= P_y - 25) {
		pattern += 0;
	}
	else
	{
		pattern += 2;
	}



	//�p�^�[����Ԃ�
	return pattern;
}

void ENEMY_AI::Reverse(){
	if (pattern % 2 == 0) {
		pattern++;
	}else{
		pattern--;
	}
}