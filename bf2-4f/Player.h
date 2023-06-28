#pragma once
#include"Define.h"
#include"Collider/BoxCollider.h"

enum PLAYER_STATE
{
     IDOL = 0,
     WALK_LEFT,
     WALK_RIGHT,
     FLY_LEFT,
     FLY_RIGHT,
     DEATH
};
class Player :public BoxCollider
{
private:
    PLAYER_STATE player_state;
    int acs_left;   //�������x
    int acs_right;  //�E�����x
    int acs_up;     //������x
    int acs_down;   //�������x
    int land_acs_left;  //�������x(�n�ʂɂ���Ƃ�)
    int land_acs_right;  //�E�����x(�n�ʂɂ���Ƃ�)
    int jump_int;   //�㏸�{�^���Ԋu
    int jump_combo;  //�A�Ő�
    int frame;      //�t���[���v���p
    float ref_y;      //�����p�ϐ��i���j
    int life;         //�c�@

    bool isOnFloor;     //�f�o�b�O�p

    //���ˎ����p
    int b_x1, b_y1, b_x2, b_y2;
    int b_x3, b_y3, b_x4, b_y4;
    int b_x5, b_y5, b_x6, b_y6;
    bool ref_once1;
    bool ref_once2;
public:

    //�R���X�g���N�^
    Player();

    //�f�X�g���N�^
    ~Player();

    //�`��ȊO�̍X�V�����s
    void Update();

    //�`��Ɋւ��邱�Ƃ�����
    void Draw() const;

    bool GetOnFloor()
    {
        return &isOnFloor;
    }

    bool SetOnFloor(bool flg)
    {
        isOnFloor = flg;
        return isOnFloor;
    }
   
    void OnHitCollision(const BoxCollider* box_collider);
    void HitCollision(const BoxCollider* box_collider);


    //X�����Ɉړ����Ă���Ƃ���-X�����ɔ��˂���
    void ReflectionMX();

    //-X�����Ɉړ����Ă���Ƃ���X�����ɔ��˂���
    void ReflectionPX();

    //-Y�����Ɉړ����Ă���Ƃ���Y�����ɔ��˂���
    void ReflectionPY();
};
