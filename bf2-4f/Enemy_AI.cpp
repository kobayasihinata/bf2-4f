#include <stdio.h>
#include "Enemy_AI.h"

Enemy_AI::Enemy_AI()
{
	// ��邱��:�v���C���[���W�ƓG�̍��W���X�V
	P_x = 100;
	P_y = 100;
	E_x = 200;
	E_y = 200;
	// �p�^�[���̃��Z�b�g
	pattern = 0;
}
Enemy_AI::~Enemy_AI()
{

}
void Enemy_AI::Update()
{
    // �v���C���[���ǂ̕����ɂ��邩(x���W)
	if (E_x > P_x) {
		pattern += 0;
	}
	else
	{
		pattern += 1;
	}

	// �v���C���[���ǂ̕����ɂ��邩(y���W)
	if (E_y >= P_y) {
		pattern += 0;
	}
	else
	{
		pattern += 2;
	}

	// �v���C���[���^���ɂ���Ȃ����s�����Ƃ�
	if (E_x >= P_x - 30 && E_x <= P_x + 30 && E_y >= P_y && E_y <= P_y + 50)
	{
		pattern = 4;
	}

	//�p�^�[����Ԃ�
	return;
}