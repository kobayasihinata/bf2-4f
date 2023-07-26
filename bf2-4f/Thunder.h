#pragma once
#include "Collider/BoxCollider.h"

#define _USE_MATH_DEFINES

#define SECOND_TO_FRAME(sec) ((sec)*60)
#define THUNDER_BALL_IMAGE_SHIFT 5

enum Thunder_Ball_State
{
    Stop = 0,
    Move,
    Hit
}; 

class Thunder :
    public BoxCollider
{
private:
    int cloud_image[3];
    int thunder_image[6];
    int thunder_ball_image[3];

    int cloud_anim;
    int thunder_anim;
    int thunder_ball_anim;

    int anim_frame;
    int fire_timer;
    int preliminary_action_time;        //�\������̎���

    float speed;
    float angle;
    float move_x;
    float move_y;

    float cloud_x;
    float cloud_y;
    int thunder_state;
    int thunder_ball_state;

    bool fire_flg;
    bool thunder_ball_flg;
    bool is_fire_ready;
    bool thunder_state_flg;

public:
    //�R���X�g���N�^
    Thunder();

    //�f�X�g���N�^
    ~Thunder();

    //�`��Ɋւ��邱�ƈȊO�̍X�V�̎���
    void Update();

    //�`��Ɋւ��邱�Ƃ̎���
    void Draw()const;

    void ChangeAngle();

    void Reflection(const BoxCollider* boxcollider);
};

