#pragma once
#include "AbstractScene.h"
#include "Player.h"
#include "Enemy.h"
#include "Enemy_AI.h"
#include"StageFloor.h"
#include"StageWall.h"
#include"Fish.h"
#include"SoapBubble.h"

class GameMain :
    public AbstractScene
{
private:
    Player* player;
    Enemy* enemy[4];
    ENEMY_AI* enemy_ai[4];
    StageFloor* stagefloor[3];
    StageWall* staegwall;
    Fish* fish;
    SoapBubble* soapbubble[4];

    int seaImage;
    bool Pouse;
    int score;  //���̃X�R�A�i�[�ꏊ
    int max_enemy;      //�G�̐�
    int P_x, P_y;       //�v���C���[���W
    const int Enemy_Move_Cool[3]{ 120,80,40 };
    int move_cooltime;

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
    void Damege(int i);
};

