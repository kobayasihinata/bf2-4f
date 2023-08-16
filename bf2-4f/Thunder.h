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
    int cloud_image[3];                 //�_�̉摜
    int thunder_image[6];               //���̉摜
    int thunder_ball_image[3];          //���̋ʂ̉摜

    int cloud_anim;                     //�_�̃A�j���[�V����
    int thunder_anim;                   //���̃A�j���[�V����
    int thunder_ball_anim;              //���̋ʂ̃A�j���[�V����

    int anim_frame;                     //�A�j���[�V�����𒲐�����t���[��
    int fire_timer;                     //���𔭎˂���܂ł̎���
    int preliminary_action_time;        //�\������̎���

    float speed;                        //����
    float angle;                        //�p�x
    float move_x;                       //x�̈ړ���
    float move_y;                       //y�̈ړ���

    float cloud_x;                      //�_��x���W
    float cloud_y;                      //�_��y���W
    int thunder_direction;              //���̕���
    int thunder_ball_state;             //���̋ʂ̏��
    int probability;                    //�m��
    int frame_count;                    //�t���[���v���p

    bool fire_flg;                      //���𔭎˂��Ă�H
    bool thunder_ball_flg;              //���̋ʂ𔭎˂���?
    bool is_fire_ready;                 //���̏����͂����H
    bool thunder_direction_flg;         //���̕����͌��܂��Ă�H
    bool is_in_game;                    //�Q�[���ɒǉ�����H

    //SE
    static int CreateThunderSE;		//�J�~�i������SE

public:
    //�R���X�g���N�^
    Thunder(float x, float y, bool flg);

    //�f�X�g���N�^
    ~Thunder();

    //�`��Ɋւ��邱�ƈȊO�̍X�V�̎���
    void Update();

    //�`��Ɋւ��邱�Ƃ̎���
    void Draw(bool flg)const;

    void ChangeAngle();

    void Reflection(const BoxCollider* boxcollider);

    bool HitPlayer(const class Player* player);

    void ReInitThunder();
};