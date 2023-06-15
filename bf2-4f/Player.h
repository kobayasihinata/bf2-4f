#pragma once
#include"Define.h"

enum PLAYER_STATE
{
     IDOL = 0,
     WALK_LEFT,
     WALK_RIGHT,
     FLY_LEFT,
     FLY_RIGHT,
     DEATH
};
class Player 
{
private:
    PLAYER_STATE player_state;
    float x, y;   //BoxCollider���o������Ή�����ϐ��ɍ����ւ�
    int acs_left;   //�������x
    int acs_right;  //�E�����x
    int acs_up;     //������x
    int acs_down;   //�������x
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
