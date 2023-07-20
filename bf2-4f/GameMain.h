#pragma once
#include "AbstractScene.h"
#include "Player.h"
#include "Enemy.h"
#include"StageFloor.h"
#include"StageWall.h"
#include"Fish.h"

class GameMain :
    public AbstractScene
{
private:
    Player* player;
    Enemy* enemy[3];
    StageFloor* stagefloor[3];
    StageWall* staegwall;
    Fish* fish;

    int seaImage;
    bool Pouse;

    int score;  //���̃X�R�A�i�[�ꏊ

public:

    //�R���X�g���N�^
    GameMain();

    //�f�X�g���N�^
    ~GameMain() final;

    //�`��ȊO�̍X�V�����s
    AbstractScene* Update() override;

    //�`��Ɋւ��邱�Ƃ�����
    void Draw() const override;

};

