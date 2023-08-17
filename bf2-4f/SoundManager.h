#pragma once
#include "DxLib.h"

enum Music_State
{
	Start,
	E_Move,
	Bubble,
	Crack,
	Falling,
	Splash,
	Eatable,
	Restart,
	DefeatTheEnemy,
	StageClear,
	GameOver,
	None
};
class SoundManager
{
protected:
	int OldState;
	int NowState;
	int music_state;
	
	int priority;

	// BGM
	int Para_BGM;               //�G�p���V���[�gBGM
	

	// SE
	int Start_SE;               //�Q�[���X�^�[�gSE
	int PlayerWalk_SE;          //�v���C���[���sSE
	int PlayerJump_SE;          //�v���C���[����SE
	int EnemyMove_SE;           //�G����SE
	int Bubble_SE;              //�o�u���擾SE
	int Falling_SE;             //����SE
	int Splash_SE;              //�����Ԃ�SE
	int Crack_SE;               //���D�j��SE
	int Eatable_SE;             //�T�J�i�ߐHSE
	int Restart_SE;		        //�R���e�j���[SE
	int DefeatTheEnemy_SE;      //�G���jSE
	int StageClear_SE;			//�X�e�[�W�N���ASE
	int GameOver_SE;            //�Q�[���I�[�o�[SE
	
public:
	//�R���X�g���N�^
	SoundManager();

	//�f�X�g���N�^
	~SoundManager();

	//�`��ȊO�̍X�V�����s
	void Update();

	//���̍Đ��͉\��
	void PlayPara_BGM(int i);

	void PlayE_Move_SE();
	void PlayBubble_SE();
	void PlayCrack_SE();
	void PlayFalling_SE();
	void PlaySplash_SE();
	void PlayEatable_SE();
	void PlayRestart_SE();
	void PlayDefeatTheEnemy_SE();
	void PlayStageClear_SE();
	void PlayGameOver_SE();
	
	 
	//�����~�߂�
	void Stop_All_Music();
	void Stop_Fall();
};

