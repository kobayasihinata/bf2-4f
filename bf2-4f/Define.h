#pragma once

//���̏��ł��g�������ȏ��͂����Ɋi�[

#define SCREEN_WIDTH 640	//��ʂ̉���
#define SCREEN_HEIGHT 480	//��ʂ̍���

#define PLAYER_HEIGHT 50	//�v���C���[�̍���
#define PLAYER_WIDTH  32	//�v���C���[�̉���

#define PLAYER_BALLOON_HEIGHT  25	//�v���C���[�̕��D�̍���

#define PLAYER_RESPAWN_POS_X 100	//�v���C���[�̃��X�|�[���ʒu(X)
#define PLAYER_RESPAWN_POS_Y 369	//�v���C���[�̃��X�|�[���ʒu(Y)

#define MAX_SPEED 250		//�ō����x�ƍŒᑬ�x�̍��𒲐�����p
#define MAX_SPEED_LAND 100	//�ō����x�ƍŒᑬ�x�̍��𒲐�����p�i�n�ʁj
#define MAX_JUMP 10			//�ő�A�Ő�
#define JUMP_INTERVAL 40	//�W�����v�{�^���A�ŊԊu
#define FALL_SPPED 0.008f	//�ō��������x
#define MOVE_SPPED 0.020f	//�ō��ړ����x
#define RISE_SPPED 0.04f	//�ō��㏸���x
#define LAND_SPEED 0.04f	//�ō��ړ����x�i�n�ʁj

#define SEA_SURFACE 450		//�C��
#define UNDER_WATER 470		//�C�̂Ȃ�