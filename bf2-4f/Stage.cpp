#include "Stage.h"
#include <math.h>
#include"StageFloor.h"
#include "DxLib.h"

Stage::Stage()
{
	landleft = LoadGraph("images/Stage/Stage_Land_Left01.png");
	landleft2 = LoadGraph("images/Stage/Stage_Land_Left02.png");
	landright = LoadGraph("images/Stage/Stage_Land_Right01.png");
	landright2 = LoadGraph("images/Stage/Stage_Land_Right02.png");
	sea = LoadGraph("images/Stage/Stage_Sea01.png");
	footing1 = LoadGraph("images/Stage/Stage_Footing01.png");
	footing2 = LoadGraph("images/Stage/Stage_Footing02.png");
	footing3 = LoadGraph("images/Stage/Stage_Footing03.png");
	footing4 = LoadGraph("images/Stage/Stage_Footing04.png");
	footing5 = LoadGraph("images/Stage/Stage_Footing05.png");
	footing6 = LoadGraph("images/Stage/Stage_Footing06.png");
	footing7 = LoadGraph("images/Stage/Stage_Footing07.png");
	footing8 = LoadGraph("images/Stage/Stage_Footing08.png");
}

Stage::~Stage()
{
	DeleteGraph(stagefloor);
	DeleteGraph(landleft);
	DeleteGraph(landleft2);
	DeleteGraph(landright);
	DeleteGraph(landright2);
	DeleteGraph(sea);
	DeleteGraph(footing1);
	DeleteGraph(footing2);
	DeleteGraph(footing3);
	DeleteGraph(footing4);
	DeleteGraph(footing5);
	DeleteGraph(footing6);
	DeleteGraph(footing7);
	DeleteGraph(footing8);
}

AbstractScene* Stage::Update()
{
	return this;
}

void Stage::Draw() const
{
	//�X�e�[�W�P
	/*DrawGraph(0,416,landleft, TRUE);
	DrawGraph(479,416,landright, TRUE);
	DrawGraph(159,444,sea, TRUE);
	DrawGraph(180,290,footing1, TRUE);*/
	//�X�e�[�W�Q
	//DrawGraph(0,416,landleft, TRUE);
	//DrawGraph(479,416,landright, TRUE);
	//DrawGraph(159,444,sea, TRUE);
	//DrawGraph(180,290,footing1, TRUE);
	//DrawGraph(90,170,footing2, TRUE);	// ��
	//DrawGraph(460,150,footing2, TRUE);	// �E
	//�X�e�[�W�R
	//DrawGraph(0, 416, landleft, TRUE);
	//DrawGraph(479, 416, landright, TRUE);
	//DrawGraph(159, 444, sea, TRUE);
	//DrawGraph(270, 370, footing3, TRUE);
	//DrawGraph(160, 280, footing4, TRUE); //	��
	//DrawGraph(310, 200, footing4, TRUE); //	�^��
	//DrawGraph(490, 100, footing4, TRUE); //	�E
	//DrawGraph(200, 100, footing5, TRUE);
	//�X�e�[�W�T
	DrawGraph(0, 416, landleft2, TRUE);
	DrawGraph(479, 416, landright2, TRUE);
	DrawGraph(159, 444, sea, TRUE);
	DrawGraph(350, 370, footing6, TRUE);
	DrawGraph(390, 320, footing6, TRUE);
}