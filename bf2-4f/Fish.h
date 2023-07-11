#pragma once
#include "collider/BoxCollider.h"

#define SECOND_TO_FRAME(sec) ((sec)*60)
#define IMAGE_SHIFT 10       //�摜�����p
#define SEASURFACE_START_X 160
#define SEASURFACE_END_X 479

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
    int fish_image[10];
    int fish_state;
    int probability;
    int fps_timer;
    int player_flying_timer;

    float speed;
    
    bool is_rising;
    bool is_preyed_on_any;
    bool is_preyey_on_enemy;

public:
    //�R���X�g���N�^
    Fish();

    //�f�X�g���N�^
    ~Fish();

    //�`��ȊO�̍X�V������
    void Update(const BoxCollider* boxcollider);

    //�`��Ɋւ��邱�Ƃ�����
    void Draw()const;
};

