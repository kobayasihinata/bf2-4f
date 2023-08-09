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
#define SECOND_TO_FRAME(sec) ((sec)*60)

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
    int main_state;
    bool clear_flg;     //���̃X�e�[�W�֑J�ڂ�������𒲂ׂ�p
    int clear_wait;     //���̃X�e�[�W�֑J�ڂ���O�̑҂�����
    int now_floor_max;  //���݂̏��̐�
    int GameOver_Img;
    int GameOver_BGM;
    int WaitTimer;

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

