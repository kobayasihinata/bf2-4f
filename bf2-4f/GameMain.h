#pragma once
#include "AbstractScene.h"
#include "Player.h"
#include "Enemy.h"
#include "Enemy_AI.h"
#include"StageFloor.h"
#include"StageWall.h"
#include"Fish.h"
#include"SoapBubble.h"
#include"Thunder.h"


class GameMain :
    public AbstractScene
{
private:
    Player* player;
    Enemy* enemy[6];
    ENEMY_AI* enemy_ai[6];
    StageFloor* stagefloor[3];
    //StageWall* staegwall;
    Fish* fish;
    Thunder* thunder;
    SoapBubble* soapbubble[6];

    int seaImage;
    bool Pouse;
    int score;  //���̃X�R�A�i�[�ꏊ
    int max_enemy;      //�G�̐�
    int P_x, P_y;       //�v���C���[���W
    const int Enemy_Move_Cool[3]{ 360,240,120 };
    int move_cooltime;
    bool damage_once;   //�d�Ȃ��Ă��鎞��񂾂��_���[�W��^����
   
    //BGM
    static int GameStartBGM;		//�Q�[���X�^�[�gBGM
    static int MainBGM;				//�Q�[�����C��BGM
    static int Continue;			//�R���e�j���[BGM
    static int StageClear;			//�X�e�[�W�N���ABGM
    static int GameOver;			//�Q�[���I�[�o�[BGM

    //SE
    static int BaloonBurstSE;			//�o���[���j��SE
    static int BirdSE;				//�g������SE
  
  
    

public:

    //�R���X�g���N�^
    GameMain();

    //�f�X�g���N�^
    ~GameMain() final;

    //�`��ȊO�̍X�V�����s
    AbstractScene* Update() override;

    //�`��Ɋւ��邱�Ƃ�����
    void Draw() const override;

    //�G�ƃv���C���[���ڐG�������̃_���[�W����
    void Damage(int i);

    //�T�E���h
    void Sound();

};

