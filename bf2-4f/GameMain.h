#pragma once
#include "AbstractScene.h"
#include "Player.h"
#include "Enemy.h"
#include "Enemy_AI.h"
#include"StageFloor.h"
#include"StageWall.h"
#include"Fish.h"
#include"Thunder.h"

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
    Thunder* thunder;

    int seaImage;
    bool Pouse;
    int px, py, ex, ey;
    int score;  //���̃X�R�A�i�[�ꏊ
    int max_enemy;      //�G�̐�

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

