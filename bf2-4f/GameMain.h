#pragma once
#include "AbstractScene.h"
#include "Player.h"
#include "Enemy.h"
#include "Enemy_AI.h"
#include"StageObject.h"
#include"Fish.h"
#include"SoapBubble.h"
#include"Thunder.h"
#include"UI.h"
#include"BackGroundStar.h"

#define ENEMY_NAMBER 6
#define SECOND_TO_FRAME(sec) ((sec)*60)
#define MAX_FLOOR 7+3
#define MAX_STAR 40     //�w�i�̐��̍ő吔

enum State {
    Normal,
    Clear,
    Over,
};

class GameMain :
    public AbstractScene
{
private:
    Player* player;
    Enemy* enemy[ENEMY_NAMBER];
    ENEMY_AI* enemy_ai[ENEMY_NAMBER];
    StageObject* stageobject[MAX_FLOOR];
    Fish* fish;
    Thunder* thunder[2];
    SoapBubble* soapbubble[6];
    UI* ui;
    BackGroundStar* backgroundstar[MAX_STAR];

    int stage;      //���݂̃X�e�[�W��
    int seaImage;

    int GameStart_BGM;   //�Q�[���X�^�[�gBGM
    int Eatable_SE;
    int StageClear_SE;

    bool Pouse;
    int score;  //���̃X�R�A�i�[�ꏊ
    int max_enemy;      //�G�̐�
    int P_x, P_y;       //�v���C���[���W
    int AI_Pattern[ENEMY_NAMBER];     //Ai�p�^�[��
    bool Avoidance[ENEMY_NAMBER]; // ����t���O
    bool damage_once;   //�d�Ȃ��Ă��鎞��񂾂��_���[�W��^����
    int main_state;
    bool clear_flg;     //���̃X�e�[�W�֑J�ڂ�������𒲂ׂ�p
    int clear_wait;     //���̃X�e�[�W�֑J�ڂ���O�̑҂�����
    int now_floor_max;  //���݂̏��̐�
    int GameOver_Img;
    int GameOver_BGM;   //�Q�[���I�[�o�[BGM
    int WaitTimer;

   
    //BGM
      
    int Continue_BGM;			//�R���e�j���[BGM
    int StageClear_BGM;			//�X�e�[�W�N���ABGM
 		

    //SE
    int EnemuyMove_SE;          //�g������SE
    int BaloonBurst_SE;			//�o���[���j��SE
    				
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

    //�G�̃X�|�[���ʒu���w�肵�����̏�ɐݒ�
    Location SpawnPosSet(StageObject* floor);
};

