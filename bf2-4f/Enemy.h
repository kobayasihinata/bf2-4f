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
    DEATH_LEFT,
    E_SUBMERGED
};
class Enemy :public BoxCollider
{
private:
    ENEMY_STATE enemy_state;

    bool flg;                    //�G�������Ă��邩
    float acs_left;              //�������x
    float acs_right;             //�E�����x
    int acs_up;                  //������x
    int acs_down;                //�������x
    const int E_Max_Speed[3]{ 50,125,200 };    //�G���x���ʂ̍ō����x

    int jump_int;                //�㏸�{�^���Ԋu
    int jump_combo;              //�A�Ő�
    int jump_cd;                 //�W�����v�A�Œ��ɉ��ɗ����鑬�x��x�点��

    int getscore[5];             //�l���_���z��
    int frame;                   //�t���[���v���p

    int charge;                  //���D��c��܂��鎞��
    int enemy_level;             //�G�̃��x��
    bool first_flg;              //�G���n�߂ĕ��D��c��܂��邩���f
    bool levelup_once;           //�G���n�߂ĕ��D��c��܂��邩���f
    int balloon;                 //�c�蕗�D
    bool death_flg;              //���S���Ă��邩���f
    int death_acs;               //���S���̗���������
    int death_wait;              //���S��̑҂�����
    bool underwater_flg;         //���v�������f
    int damage;                  //���ꃂ�[�V�������ҋ@
    int protect;                 //�������u�������G(�o�O�����̂���)
    int wait_time;               //���D��c��܂���O�̑ҋ@����
    int wait_flg;                //���D��c��܂���O�����f
    bool onfloor_flg;            //StageFloor�̏ォ�ǂ���
    bool onshare_flg;            //StageFloor�̏�Ƃ������Ƃ����L���邩�ǂ���
    bool move_right_flg;         //�E�ړ��������f
    bool move_left_flg;          //���ړ��������f
    bool jump_flg;               //�W�����v�������f
    int no_ai_time;              //AI����������
    bool para_flg;               //�p���V���[�g��Ԃ����f
    bool splash_SE_flg;
    bool ref_once_left;          //���ː���p
    bool ref_once_right;         //���ː���p

    int enemy_image[18];         //�G�摜
    int splash_image[3];         //�G���v�摜
    int getscore_image[5];       //�X�R�A�l�����o�摜
    int enemy_anim;              //�G�A�j���[�V�����p
    int para_anim;               //�G�p���V���[�g�A�j���[�V�����p
    int splash_anim;             //�G���v�A�j���[�V�����p
    int getscore_anim[5];        //�X�R�A�l�����o�摜�\���p
    int getscore_x[5];           //�X�R�A�l�����o�pX���W
    int getscore_y[5];           //�X�R�A�l�����o�pY���W     
    bool is_getscore[5];         //�X�R�A�l�������o�p
    int anim_boost;              //�A�j���[�V���������p
    int crack;                   //

    float last_move_x;           //�ړ������ۑ��p
    int last_input;              //���͕����ۑ��p(-1=�� 0=�ǂ��������Ă��Ȃ��@1=�E)

    int test_score;              //�_�����Z�m�F�p

    //SE
    static int enemy_landing_se; //�G���nSE
    static int crush_enemy;		 //�G���jSE
    static int create_baloon_se; //�G���D��c��܂���SE
    int enemy_move_se;           //
    int crack_se;                //��_���[�WSE
    int para_se;                 //�p���V���[�gSE
    int defeat_the_enemy_se;     //

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

    //�G�Ƃ̓����蔻�菈��
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

    //�_���[�W��^���ēG�̏�ԂɑΉ������������s���A�Ή������X�R�A��Ԃ�
    int ApplyDamege();

    //�G�̕��D�����炷
    void BalloonDec();

    //�G�����S���[�V�����Ɉڍs������
    void EnemyDeath();

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

    /******************************
     AI�ňړ�������Ƃ��Ɏg���֐�
     ******************************/
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
    /******************************/

    //���Z�b�g
    void EnemyReset();

    //���x���A�b�v
    void EnemyLevelUp();

    //AI����(����)
    void SetNot_AI(int time);
    int No_AI_Flg();

    //enemy_level���擾
    int GetEnemyLevel()const { return enemy_level; }

    //�G�W�����v�t���O���擾
    int GetEnemyJumpflg() { return jump_flg; }

    //�G�̐i�s�������擾
    int GetEnemyMove() { return move_left_flg; }

    //�G�����S���[�V���������擾
    int GetEnemyDeathFlg() { return death_flg; }

    //�G���p���V���[�g��Ԃ��擾
    int GetEnemyParaFlg() { return para_flg; }

    //�G�����v�����擾
    int GetEnemyUnderWaterFlg() { return underwater_flg; }

    //�G�����v�����ݒ�
    void SetEnemyUnderWaterFlg(int flg) { underwater_flg = flg; }

    //�G�������Ă��邩�擾
    int GetFlg() { return flg; }

    //�G�̐����Ă��邩�̔����ݒ�
    void SetFlg(bool getflg) { flg = getflg; }

    //�G�����D��c��܂���O���擾
    int GetWaitFlg() { return wait_flg; }

    //�G�̈ʒu���擾
    Location GetEnemyLocation() { return location; }

    //�X�R�A�l�����o�J�n
    void GetScoreStart(int i);

    //�G�̏�Ԃ��擾
    int GetEnemyState() { return enemy_state; }

    // SE�t���O
    int GetE_Splash_SE_flg() { return splash_SE_flg; }
    void Reset_SE_flg1() { splash_SE_flg = false; }

    void reset_flg() { jump_flg = false; }
};
