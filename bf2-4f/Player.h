#pragma once
#include"Define.h"

class Player 
{
private:
    short x, y;   //BoxCollider���o������Ή�����ϐ��ɍ����ւ�
    int acs_left;   //�������x
    int acs_right;  //�E�����x
    int acs_up;     //������x
public:

    //�R���X�g���N�^
    Player();

    //�f�X�g���N�^
    ~Player();

    //�`��ȊO�̍X�V�����s
    void Update();

    //�`��Ɋւ��邱�Ƃ�����
    void Draw() const;
};
