#pragma once
#include "AbstractScene.h"
#include "Player.h"
#include"StageFloor.h"
#include"StageWall.h"

class GameMain :
    public AbstractScene
{
private:
    Player* player;
    StageFloor* stagefloor;
    StageWall* staegwall;
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

