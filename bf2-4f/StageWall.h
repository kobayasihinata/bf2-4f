#pragma once
#include "collider/BoxCollider.h"
class StageWall :
    public BoxCollider
{
public:
    //�R���X�g���N�^
    StageWall();
    //�f�X�g���N�^
    ~StageWall();

    //�`��ȊO�̍X�V����������
    void Update();

    //�`��Ɋւ��邱�Ƃ���������
    void Draw()const;

};

