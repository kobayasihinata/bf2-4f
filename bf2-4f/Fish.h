#pragma once
#include "collider/BoxCollider.h"

#define SECOND_TO_FRAME(sec) ((sec)*60)
#define IMAGE_SHIFT 10       //�摜�����p
#define SEASURFACE_START_X 158
#define SEASURFACE_END_X 481

class Fish :
    public BoxCollider
{
private:
    enum E_Fish_State
    {
        Rising_Fish_1 = 0,
        Rising_Fish_2,
        Rising_Fish_3,
        Falling_Fish_1,
        Falling_Fish_2,
        Falling_Fish_3,
        PreyingOn_Player,
        PreyingOn_Enemy_1,
        PreyingOn_Enemy_2,
        PreyingOn_Enemy_3,
    };

    int fish_image[10];                 //�摜�p
    int fish_state;                     //�����Ȃ̏��
    int probability;                    //�m��
    int frame_count;                    //�t���[���v���p
    int player_flying_on_sea_timer;     //�v���C���[���C�ʂ���ł��鎞�̌v���p

    const float speed = 1.2f;           //����
    
    bool is_rising;                     //�����Ȃ��C�����яオ���Ă���H
    bool is_falling;                    //�����Ȃ��C�ɗ����Ă���H
    bool is_preying_on_player;          //�ߐH���Ă���̂̓v���C���[�H
    bool is_preying_on_enemy;           //�ߐH���Ă���͓̂G�H
    bool reversal_flg;                  //�摜�͔��]����H
    bool respawn_flg;                   //�v���C���[�����X�|�[��������H
    bool bubble_spawn_flg;              //�V���{���ʂ��X�|�[��������H
    bool target_flg;                    //�ߐH�Ώۂ͂���H

public:
    //�R���X�g���N�^
    Fish();

    //�f�X�g���N�^
    ~Fish();

    //�`��ȊO�̍X�V������
    void Update();

    //�`��Ɋւ��邱�Ƃ�����
    void Draw()const;

    //�ߐH����
    void TargetPrey(BoxCollider* boxcollider);

    //�C�ʂɉ��������邩�`�F�b�N����
    bool CheckSeaSurface(BoxCollider* boxcollider);

    //is_preyed_on_player�̒l���擾����
    bool GetIsPreyedOnPlayer() { return is_preying_on_player; }

    //is_preyed_on_enemy�̒l���擾����
    bool GetIsPreyedOnEnemyr() { return is_preying_on_enemy; }

    //respawn_flg�̒l���擾����
    bool GetRespawnFlg() { return respawn_flg; }

    //respawn_flg�̒l�������ɐݒ肷��
    void SetRespawnFlg(const bool flg) { respawn_flg = flg; }

    //�ߐH�Ώۂ��C�ʂɂ��Ȃ��ꍇ�̏���
    void NotAtSeaSurface();

    //target_flg��ݒ肷��
    void SetTargetFlg(const bool flg) { target_flg = flg; }
};

