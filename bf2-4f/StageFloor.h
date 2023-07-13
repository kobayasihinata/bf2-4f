#pragma once
#include "collider/BoxCollider.h"
class StageFloor :
    public BoxCollider
{
private:
    int shift;        //�摜����

    int landleft;
    int landright;

    int footing1;
    int footing2;
    int footing3;
    int footing4;
    int footing5;

public:
    //�R���X�g���N�^
    StageFloor(const int x, const int y,
        const int heigth, const int width, const int margin);
    //�f�X�g���N�^
    ~StageFloor();

    //�`��ȊO�̍X�V����������
    void Update();

    //�`��Ɋւ��邱�Ƃ���������
    void Draw()const;

    //�摜��\��������
    void DrawLandLeft();
    void DrawLandRight();
    void DrawFooting1();
    void DrawFooting2();
    void DrawFooting3();
    void DrawFooting4();
    void DrawFooting5();
};

