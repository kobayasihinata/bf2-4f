#pragma once
#include"AbstractScene.h"

class Pause 
{
private:
    bool DrawMenu;
public:

    //�R���X�g���N�^
    Pause();

    //�f�X�g���N�^
    ~Pause();

    //�`��ȊO�̍X�V�����s
    void Update();

    //�`��Ɋւ��邱�Ƃ�����
    void Draw() const ;

    bool PauseMenu();

    void NowPause();
};