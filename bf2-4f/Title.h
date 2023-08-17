#pragma once
#include "AbstractScene.h"

#define TITLEMODESELECT_X 165
#define TITLEMODESELECT_Y 270

class Title :
    public AbstractScene
{
private:
    int titlelogo;
    int titlecredit;
    int titlemodeselect;
    int titlecursor[4];

    int cursor_y;
    int cursor_num;
    int interval;
    int cursor_anim;
    int frame;
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
