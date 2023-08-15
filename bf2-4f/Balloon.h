#pragma once
#include"DxLib.h"
#include"Define.h"
#include"Collider/BoxCollider.h"

class Balloon :public BoxCollider {
private:

    int flg;                //����ď������A�������͉�ʊO�܂ŏオ���Ă��������̔���
    int frame;              //�t���[����
    int balloon_anim;        //�A�j���[�V�����p�ϐ�
    int acs_left;           //�����x��
    int acs_right;          //�����x�E

	int balloon_image[4];   //�摜�p�ϐ�
	int get_balloon_se;   //���D�擾��SE
public:
    //�R���X�g���N�^
    Balloon(int x,int y);

    //�f�X�g���N�^
    ~Balloon();

    //�`��ȊO�̍X�V�����s
    void Update();

    //�`��Ɋւ��邱�Ƃ�����
    void Draw() const;

    //�v���C���[�Ƃ̓����蔻�菈��
    int HitPlayerCollision(const BoxCollider* box_collider);

    //���D�����邩�擾
    int GetFlg() { return flg; }
};
