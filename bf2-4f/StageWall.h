#pragma once
#include "collider/BoxCollider.h"
class StageWall :
    public BoxCollider
{
private:
    int shift;

    int footing4;
    int footing7;
    int footing8;

public:
    //�R���X�g���N�^
    StageWall(int x, int y, int height, int width, int shift);
    //�f�X�g���N�^
    ~StageWall();

    //�`��ȊO�̍X�V����������
    void Update();

    //�`��Ɋւ��邱�Ƃ���������
    void Draw()const;

    void DrawFooting4();
    void DrawFooting7();
    void DrawFooting8();


};

