#pragma once
#include"Define.h"
#include"Collider/BoxCollider.h"

#define IMAGE_SHIFT_X 15 //�摜���炵�p
#define IMAGE_SHIFT_Y 13 //�摜���炵�p

enum ENEMY_STATE
{
    E_IDOL_RIGHT = 0,
    E_IDOL_LEFT,
    CHARGE_RIGHT, 
    CHARGE_LEFT, 
    E_FLY_RIGHT,
    E_FLY_LEFT,
    PARACHUTE_RIGHT,
    PARACHUTE_LEFT,
    DEATH_RIGHT,
    DEATH_LEFT
};
class Enemy :public BoxCollider
{
private:

    ENEMY_STATE enemy_state;
    float acs_left;   //�������x
    float acs_right;  //�E�����x
    int acs_up;     //������x
    int acs_down;   //�������x

    int jump_int;   //�㏸�{�^���Ԋu
    int jump_combo;  //�A�Ő�
    int jump_cd;    //�W�����v�A�Œ��ɉ��ɗ����鑬�x��x�点��

    int frame;      //�t���[���v���p

    int charge;     //���D��c��܂��鎞��
    int enemy_level;    //�G�̃��x��
    bool first_flg;     //�G���n�߂ĕ��D��c��܂��邩���f
    bool levelup_once;     //�G���n�߂ĕ��D��c��܂��邩���f
    int balloon;        //�c�蕗�D
    bool death_flg;      //���S���Ă��邩���f
    int  death_acs;      //���S���̗���������

    float ref_y;            //�����p�ϐ��i���j

    int wait_time;           //���D��c��܂���O�����f
    bool onfloor_flg;        //StageFloor�̏ォ�ǂ���
    bool onshare_flg;       //StageFloor�̏�Ƃ������Ƃ����L���邩�ǂ���
    bool move_right_flg;    //�E�ړ��������f
    bool move_left_flg;     //���ړ��������f
    bool jump_flg;          //�W�����v�������f
    bool para_flg;          //�p���V���[�g��Ԃ����f
    bool ref_once_left;     //���ː���p
    bool ref_once_right;    //���ː���p

    int enemy_image[20];   //�G�摜
    int enemy_anim;    //�G�A�j���[�V�����p
    int para_anim;    //�G�A�j���[�V�����p
    int anim_boost;     //�A�j���[�V���������p

    float last_move_x;    //�ړ������ۑ��p
    bool last_input;    //���͕����ۑ��p(0=�E�@1=��)

public:

    //�R���X�g���N�^
    Enemy(int x, int y, int level);

    //�f�X�g���N�^
    ~Enemy();

    //�`��ȊO�̍X�V�����s
    void Update();

    //�`��Ɋւ��邱�Ƃ�����
    void Draw() const;

    //�X�e�[�W�̃I�u�W�F�N�g�Ƃ̓����蔻�菈��
    void HitStageCollision(const BoxCollider* box_collider);

    //���̏ォ�ǂ�������
    bool IsOnFloor(const BoxCollider* box_collider)const;

    //���ɒ��n����
    void OnFloor();

    //X�����Ɉړ����Ă���Ƃ���-X�����ɔ��˂���
    void ReflectionMX();

    //-X�����Ɉړ����Ă���Ƃ���X�����ɔ��˂���
    void ReflectionPX();

    //-Y�����Ɉړ����Ă���Ƃ���Y�����ɔ��˂���
    void ReflectionPY();


    //�G�̕��D�����炷
    void BalloonDec();

    //onshare_flg�̒l��ݒ肷��
    void SetOnShareFlg(const bool flg)
    {
        onshare_flg = flg;
        //onshare_flg��true�Ȃ�onfloor_flg��true�ɂȂ�
        if (onshare_flg == true)
        {
            onfloor_flg = true;
        }
    }

    //�E����
    void EnemyMoveRight();

    //������
    void EnemyMoveLeft();

    //�E���͂������͍����͂���߂�
    void EnemyMoveStop();

    //�W�����v����
    void EnemyJump();

    //�W�����v���͂���߂�
    void EnemyJumpStop();

    //���Z�b�g
    void EnemyReset();

    //���x���A�b�v
    void EnemyLevelUp();

    //enemy_level���擾
    int GetEnemyLevel()const { return enemy_level; }
};
