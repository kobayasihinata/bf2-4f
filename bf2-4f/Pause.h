#pragma once
#include"AbstractScene.h"

class Pouse 
{
private:
    bool DrawMenu;
public:

    //�R���X�g���N�^
    Pouse();

    //�f�X�g���N�^
    ~Pouse();

    //�`��ȊO�̍X�V�����s
    void Update();

    //�`��Ɋւ��邱�Ƃ�����
    void Draw() const ;

    bool PouseMenu();

    void NowPouse();
};