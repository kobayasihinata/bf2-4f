#pragma once
#include "AbstractScene.h"
#include "Player.h"
#include "Enemy.h"
#include"StageFloor.h"
#include"StageWall.h"
#include"Fish.h"
#include"UI.h"

class GameMain :
    public AbstractScene
{
private:
    Player* player;
    Enemy* enemy;
    StageFloor* stagefloor[3];
    StageWall* staegwall;
    Fish* fish;
    UI* ui;

    int seaImage;
    bool Pouse;

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

