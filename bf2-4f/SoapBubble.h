#pragma once

#include<DxLib.h>
#include"Define.h"
#include"Collider/BoxCollider.h"



class SoapBubble :public BoxCollider
{
private:
    int flg;
    int bubble_image[4];    //�摜�p�ϐ�
    int frame;              //�t���[����
    int bubble_anim;        //�A�j���[�V�����p�ϐ�
public:

    //�R���X�g���N�^
    SoapBubble();

    //�f�X�g���N�^
    ~SoapBubble();

    //�`��ȊO�̍X�V�����s
    void Update();

    //�`��Ɋւ��邱�Ƃ�����
    void Draw() const;

    //�v���C���[�Ƃ̓����蔻�菈��
    int HitPlayerCollision(const BoxCollider* box_collider);

    //�V���{���ʂ��X�|�[��������
    void SoapBubbleSpawn(int x);
};

