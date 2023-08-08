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

#define ENEMY_NAMBER 6
#define FLOOR_MAX 7

class GameMain :
    public AbstractScene
{
private:
    Player* player;
    Enemy* enemy[ENEMY_NAMBER];
    ENEMY_AI* enemy_ai[ENEMY_NAMBER];
    StageFloor* stagefloor[FLOOR_MAX];
    //StageWall* staegwall;
    Fish* fish;
    Thunder* thunder;
    SoapBubble* soapbubble[6];

    int stage;      //���݂̃X�e�[�W��
    int seaImage;
    int GameStart_BGM;
    int EnemuyMove_SE;
    bool Pouse;
    int score;  //���̃X�R�A�i�[�ꏊ
    int max_enemy;      //�G�̐�
    int P_x, P_y;       //�v���C���[���W
    bool Avoidance[ENEMY_NAMBER]; // ����t���O
    bool damage_once;   //�d�Ȃ��Ă��鎞��񂾂��_���[�W��^����
    bool clear_flg;     //���̃X�e�[�W�֑J�ڂ�������𒲂ׂ�p
    int clear_wait;     //���̃X�e�[�W�֑J�ڂ���O�̑҂�����
    int now_floor_max;  //���݂̏��̐�

   
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

    //���̃X�e�[�W��
    int NextStage();

    //�G�ƒn�ʂ𐶐�����
    void CreateStage(int stage);
};

