#pragma once
#include "collider/BoxCollider.h"
class StageFloor :
    public BoxCollider
{
public:
    //�R���X�g���N�^
    StageFloor();
    //�f�X�g���N�^
    ~StageFloor();

    //�`��ȊO�̍X�V����������
    void Update();

    //�`��Ɋւ��邱�Ƃ���������
    void Draw()const;

};

