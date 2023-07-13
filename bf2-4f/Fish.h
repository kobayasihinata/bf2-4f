#pragma once
#include "collider/BoxCollider.h"

#define SECOND_TO_FRAME(sec) ((sec)*60)
#define IMAGE_SHIFT 10       //�摜�����p
#define SEASURFACE_START_X 159
#define SEASURFACE_END_X 480

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

    float speed;                        //����
    
    bool is_rising;                     //�����Ȃ��C�����яオ���Ă��邩�H
    bool is_falling;                    //�����Ȃ��C�ɗ����Ă��邩�H
    bool is_preyed_on_player;           //�ߐH�����̂̓v���C���[���H
    bool is_preyed_on_enemy;            //�ߐH�����͓̂G���H
    bool reversal_flg;                  //�摜�͔��]���邩�H
    bool respawn_flg;                   //�v���C���[�����X�|�[�������邩�H

public:
    //�R���X�g���N�^
    Fish();

    //�f�X�g���N�^
    ~Fish();

    //�`��ȊO�̍X�V������
    void Update(BoxCollider* boxcollider);

    //�`��Ɋւ��邱�Ƃ�����
    void Draw()const;

    //is_preyed_on_player�̒l���擾����
    bool GetIsPreyedOnPlayer() { return is_preyed_on_player; }

    //respawn_flg�̒l���擾����
    bool GetRespawnFlg() { return respawn_flg; }

    //respawn_flg�̒l�������ɐݒ肷��
    void SetRespawnFlg(const bool flg) { respawn_flg = flg; }
};

