#pragma once
#include "AbstractScene.h"
#include"StageBox.h"

class Title :
    public AbstractScene
{
private:
    StageBox* stagebox;

public:

    //�R���X�g���N�^
    Title();

    //�f�X�g���N�^
    ~Title() final;

    //�`��ȊO�̍X�V�����s
    AbstractScene* Update() override;

    //�`��Ɋւ��邱�Ƃ�����
    void Draw() const override;
};
