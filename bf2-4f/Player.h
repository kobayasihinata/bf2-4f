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
    THUNDER_DEATH,
    INVINCIBLE,
    SUBMERGED
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
    int jump_cd;    //�W�����v�A�Œ��ɉ��ɗ����鑬�x��x�点��
    bool jump_flg;      //�W�����v�������f

    int frame;      //�t���[���v���p
    int balloon;        //�c�蕗�D
    int life;            //�c�@
    bool death_flg;      //���S���Ă��邩���f
    bool thunder_death_flg; //���Ŏ��S���Ă��邩���f
    int  death_acs;      //���S���̗���������
    int  death_wait;      //���S��̑҂�����
    int  thunder_death_wait;      //���S��̑҂�����
    bool  underwater_flg;      //���v�������f
    int respawn;   //���X�|�[����̖��G�������f
    bool onfloor_flg;   //StageFloor�̏ォ�ǂ���
    bool onshare_flg;   //StageFloor�̏�Ƃ������Ƃ����L���邩�ǂ���
    bool ref_once_left;
    bool ref_once_right;

    int player_image[31];   //�v���C���[�摜
    int splash_image[3];   //�v���C���[�摜
    int player_anim;    //�v���C���[�A�j���[�V�����p
    int splash_anim;    //���v�A�j���[�V�����p
    int turn_anim;    //���v�A�j���[�V�����p
    int anim_boost;     //�A�j���[�V���������p
    int jump_anim_boost;    //�W�����v�A�Ŏ��A�j���[�V���������p
    float last_move_x;    //�ړ������ۑ��p
    int last_input;    //���͕����ۑ��p(-1=�� 0=�ǂ��������Ă��Ȃ��@1=�E)

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

    //�G�Ƃ̓����蔻�菈�� (1=�G���E�ɁA�v���C���[���������ɔ��ˁ@2=�G�����ɁA�v���C���[���E�����ɔ��ˁ@3=�G����ɁA�v���C���[���������ɔ��ˁ@4=�G�����ɁA�v���C���[��������ɔ���)
    int HitEnemyCollision(const BoxCollider* box_collider);

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

    //Y�����Ɉړ����Ă���Ƃ���-Y�����ɔ��˂���
    void ReflectionMY();

    //�v���C���[�̎c�@���擾����
    int GetPlayerLife() { return life; }

    //�v���C���[�̎c�@��ݒ肷��
    void SetPlayerLife(const int life) { this->life = this->life + life; }

    //�v���C���[�����G�����擾����
    int GetPlayerRespawn() { return respawn; }

    //�v���C���[������ł���r�������擾����
    int GetPlayerDeathFlg() { return death_flg; }

    //�v���C���[���X�|�[��
    void PlayerRespawn(float x, float y);

    //�v���C���[�̕��D�����炷
    void BalloonDec();

    //�v���C���[��������Ԃ��擾����
    bool GetThunderDeathFlg() { return thunder_death_flg; }

    //�v���C���[�𗋎���Ԃɐݒ肷��
    void SetThunderDeath(bool flg) { thunder_death_flg = flg; }

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


    Location GetPlayerLocation() { return location; }

    int GetPlayerState() { return player_state; }

    void SetPlayerState(const PLAYER_STATE state) { player_state = state; }
};
