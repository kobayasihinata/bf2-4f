#pragma once

#include<DxLib.h>
#include"Define.h"
#include"Collider/BoxCollider.h"

class SoapBubble :public BoxCollider
{
private:
    int flg;
    int bubble_image[4];    //�摜�p�ϐ�
    int getscore_image;     //�X�R�A�l���摜
    int getscore_anim;    //�X�R�A�l�����o�摜�\���p
    int getscore_x;         //�X�R�A�l�����o�pX���W
    int getscore_y;         //�X�R�A�l�����o�pY���W
    bool is_getscore;    //�X�R�A�l�������o�p
    int frame;              //�t���[����
    int bubble_anim;        //�A�j���[�V�����p�ϐ�
    int acs_left;           //�����x��
    int acs_right;          //�����x�E
    int bubble_get_anim;    //�V���{���ʎ擾���A�j���[�V����
    bool get_once;           //������V���{���ʂ�����o�O����(�Վ�)

    //SE
    int GetSoupBubble_SE;	//�V���{���ʔj��SE

    
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

