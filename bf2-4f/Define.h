#pragma once

//���̏��ł��g�������ȏ��͂����Ɋi�[

#define SCREEN_WIDTH 640	//��ʂ̉���
#define SCREEN_HEIGHT 480	//��ʂ̍���

#define PLAYER_ENEMY_HEIGHT 50	//�v���C���[�ƓG�̍���
#define PLAYER_ENEMY_WIDTH  32	//�v���C���[�ƓG�̉���

#define BALLOON_HEIGHT  25	//�v���C���[�ƓG�̕��D�̍���

#define PLAYER_RESPAWN_POS_X 100	//�v���C���[�̃��X�|�[���ʒu(X)
#define PLAYER_RESPAWN_POS_Y 370	//�v���C���[�̃��X�|�[���ʒu(Y)

#define MAX_SPEED 250		//�ō����x�ƍŒᑬ�x�̍��𒲐�����p
#define MAX_SPEED_LAND 100	//�ō����x�ƍŒᑬ�x�̍��𒲐�����p�i�n�ʁj
#define MAX_JUMP 10			//�ő�A�Ő�
#define JUMP_INTERVAL 10	//�W�����v�{�^���A�ŊԊu
#define FALL_SPPED 0.02f	//�ō��������x
#define MOVE_SPPED 0.015f	//�ō��ړ����x
#define RISE_SPPED 0.035f	//�ō��㏸���x
#define LAND_SPEED 0.03f	//�ō��ړ����x�i�n�ʁj

#define SEA_SURFACE 445		//�C��
#define UNDER_WATER 470		//�C�̂Ȃ�

#define BREAK_BALLOON_GETPOINT 500		//�G�̕��D�����������̓_��
#define ONFLOOR_KILLPOINT 750			//�n�ʂɗ����Ă���G��|�������̓_��
#define PARA_KILLPOINT 1000				//�p���V���[�g�~�����̓G��|�������̓_��
#define SOAPBUBBLE_GETPOINT 500			//�V���{���ʂ̓_��