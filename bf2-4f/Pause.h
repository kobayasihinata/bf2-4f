#pragma once
#include "AbstractScene.h"

class Pause :
    public AbstractScene
{
private:


public:

    //�R���X�g���N�^
    Pause();

    //�f�X�g���N�^
    ~Pause() final;

    //�`��ȊO�̍X�V�����s
    AbstractScene* Update() override;

    //�`��Ɋւ��邱�Ƃ�����
    void Draw() const override;
};
