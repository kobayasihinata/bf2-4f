#pragma once
#include"AbstractScene.h"
class Pouse :
    public AbstractScene
{
private:
    bool DrawMenu;
public:

    //�R���X�g���N�^
    Pouse();

    //�f�X�g���N�^
    ~Pouse() ;

    //�`��ȊO�̍X�V�����s
    AbstractScene* Update() override;

    //�`��Ɋւ��邱�Ƃ�����
    void Draw() const override;
};