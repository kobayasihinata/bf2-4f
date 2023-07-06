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
    float acs_left;   //�������x
    float acs_right;  //�E�����x
    int acs_up;     //������x
    int acs_down;   //�������x
    int land_acs_left;  //�������x(�n�ʂɂ���Ƃ�)
    int land_acs_right;  //�E�����x(�n�ʂɂ���Ƃ�)
    int jump_int;   //�㏸�{�^���Ԋu
    int jump_combo;  //�A�Ő�
    int frame;      //�t���[���v���p
    float ref_y;      //�����p�ϐ��i���j
    int balloon;        //�c�蕗�D
    int life;           //�c�@
    bool onfloor_flg;   //StageFloor�̏ォ�ǂ���
    bool onshare_flg;   //StageFloor�̏�Ƃ������Ƃ����L���邩�ǂ���
    bool ref_once1;
    bool ref_once2;
    bool respawn_flg;   //���X�|�[�����邩�ǂ���
public:

    //�R���X�g���N�^
    Player();

    //�f�X�g���N�^
    ~Player();

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

    //�v���C���[�̎c�@���擾����
    int GetPlayerLife() { return life; }

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
};
