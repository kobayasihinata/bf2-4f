#pragma once
#include "AbstractScene.h"

#define SECOND_TO_FRAME(sec) ((sec)*60)

class GameOver :
    public AbstractScene
{
private:
    int GameOver_Img;
    int WaitTimer;
public:

    //�R���X�g���N�^
    GameOver();

    //�f�X�g���N�^
    ~GameOver();

    //�`��ȊO�̍X�V�����s
    AbstractScene* Update() override;

    //�`��Ɋւ��邱�Ƃ�����
    void Draw() const override;
};
