#pragma once
#include"Define.h"
#include"Collider/BoxCollider.h"

#define IMAGE_SHIFT_X 15 //�摜���炵�p
#define IMAGE_SHIFT_Y 6 //�摜���炵�p

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
    int balloon;         //�c�蕗�D
    int life;         //�c�@
    bool onfloor_flg;   //StageFloor�̏ォ�ǂ���
    bool ref_once1;
    bool ref_once2;
    bool respawn_flg;

    int player_image[30];   //�v���C���[�摜
public:

    //�R���X�g���N�^
    Player();

    //�f�X�g���N�^
    ~Player();

    //�`��ȊO�̍X�V�����s
    void Update();

    //�`��Ɋւ��邱�Ƃ�����
    void Draw() const;

    //�X�e�[�W�̃I�u�W�F�N�g�Ƃ̓����蔻��
    void HitStageCollision(const BoxCollider* box_collider);

    //���ɒ��n����
    void OnFloor();

    //X�����Ɉړ����Ă���Ƃ���-X�����ɔ��˂���
    void ReflectionMX();

    //-X�����Ɉړ����Ă���Ƃ���X�����ɔ��˂���
    void ReflectionPX();

    //-Y�����Ɉړ����Ă���Ƃ���Y�����ɔ��˂���
    void ReflectionPY();

    //�v���C���[�̎c�@���擾����
    int GetPlayerLife() { return life; }

};
