#pragma once
#include"Define.h"
#include"Collider/BoxCollider.h"

#define IMAGE_SHIFT_X 15 //�摜���炵�p
#define IMAGE_SHIFT_Y 13 //�摜���炵�p

enum PLAYER_STATE
{
     IDOL_RIGHT = 0,
     IDOL_LEFT,
     WALK_LEFT,
     TURN_LEFT,
     WALK_RIGHT,
     TURN_RIGHT,
     FLY_LEFT,
     FLY_RIGHT,
     DEATH,
     THUNDER_DEATH
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

    int balloon;        //�c�蕗�D
    int life;            //�c�@
    bool death_flg;      //���S���Ă��邩���f

    float ref_y;      //�����p�ϐ��i���j
    bool onfloor_flg;   //StageFloor�̏ォ�ǂ���
    bool ref_once1;
    bool ref_once2;

    int player_image[30];   //�v���C���[�摜
    int player_anim;    //�v���C���[�A�j���[�V�����p
    int anim_boost;     //�A�j���[�V���������p

    float last_move_x;    //�ړ������ۑ��p
    bool last_input;    //�ړ������ۑ��p(0=���@1=�E)

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

    //�v���C���[���X�|�[��
    void PlayerRespawn(int x,int y);

    //�v���C���[�̕��D�����炷
    void BalloonDec();
};
