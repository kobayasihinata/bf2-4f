#pragma once
#include "DxLib.h"


#define SOUND_MAX 14
class SoundManager
{
protected:
	struct Soundflg {
		bool Wait; // �Đ��҂�
		bool Play; // �Đ���
	};
	Soundflg soundflg[SOUND_MAX];

	// BGM
	

	// SE
	int Start_SE;               //�Q�[���X�^�[�gSE(0)
	int PlayerWalk_SE;          //�v���C���[���sSE(1)
	int PlayerJump_SE;          //�v���C���[����SE(2)
	int EnemyMove_SE;           //�G����SE(3)
	int Bubble_SE;              //�o�u���擾SE(4)
	int Crack_SE;               //���D�j��SE(5)
	int Falling_SE;             //����SE(6)
	int Splash_SE;              //�����Ԃ�SE(7)
	int Para_SE;                //�G�p���V���[�gBGM(8)
	int Eatable_SE;             //�T�J�i�ߐHSE(9)
	int Restart_SE;		        //�R���e�j���[SE(10)
	int DefeatTheEnemy_SE;      //�G���jSE(11)
	int StageClear_SE;			//�X�e�[�W�N���ASE(12)
	int GameOver_SE;            //�Q�[���I�[�o�[SE(13)
	
public:
	//�R���X�g���N�^
	SoundManager();

	//�f�X�g���N�^
	~SoundManager();

	//�`��ȊO�̍X�V�����s
	void Update();

	//���̍Đ��͉\��
	
	void PlayP_Walk_SE();
	void PlayP_Jump_SE();
	void PlayE_Move_SE();
	void PlayBubble_SE();
	void PlayCrack_SE();
	void PlayFalling_SE();
	void PlaySplash_SE();
	void PlayPara_SE();
	void PlayEatable_SE();
	void PlayRestart_SE();
	void PlayDefeatTheEnemy_SE();
	void PlayStageClear_SE();
	void PlayGameOver_SE();
	
	 
	//�����~�߂�
	void Stop_All_Sound();
	void Stop_E_Move() { StopSoundMem(EnemyMove_SE); }
	void Stop_Para() { StopSoundMem(Para_SE); }

	void Reset_flg() {
		for (int i = 0; i < SOUND_MAX; i++) {
			soundflg[i].Wait = false;
			soundflg[i].Play = false;
		}
	}
};

