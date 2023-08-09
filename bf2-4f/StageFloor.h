#pragma once
#include"StageObject.h"
class StageFloor :
    public StageObject
{
private:
    //int shift;        //�摜����

    //int landleft;
    //int landleft2;
    //int landright;
    //int landright2;

    //int footing1;
    //int footing2;
    //int footing3;
    //int footing5;
    //int footing6;

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
    void DrawLandLeft2();
    void DrawLandRight2();
    void DrawLandRight();
    void DrawFooting1();
    void DrawFooting2();
    void DrawFooting3();
    void DrawFooting5();
    void DrawFooting6();

    //���̍��W���擾
    Location GetLocation() { return location; }
    //���̕��ƍ������擾
    Area GetWidth() { return area; }
};

