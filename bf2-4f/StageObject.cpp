#include "StageObject.h"
#include"DxLib.h"

int StageObject::landleft = NULL;
int StageObject::landleft2 = NULL;
int StageObject::landright = NULL;
int StageObject::landright2 = NULL;

int StageObject::footing1 = NULL;
int StageObject::footing2 = NULL;
int StageObject::footing3 = NULL;
int StageObject::footing4 = NULL;
int StageObject::footing5 = NULL;
int StageObject::footing6 = NULL;
int StageObject::footing7 = NULL;
int StageObject::footing8 = NULL;

StageObject::StageObject()
{
	shift = 0;

	landleft = LoadGraph("images/Stage/Stage_Land_Left01.png");
	landleft2 = LoadGraph("images/Stage/Stage_Land_Left02.png");
	landright = LoadGraph("images/Stage/Stage_Land_Right01.png");
	landright2 = LoadGraph("images/Stage/Stage_Land_Right02.png");

	footing1 = LoadGraph("images/Stage/Stage_Footing01.png");
	footing2 = LoadGraph("images/Stage/Stage_Footing02.png");
	footing3 = LoadGraph("images/Stage/Stage_Footing03.png");
	footing5 = LoadGraph("images/Stage/Stage_Footing05.png");
	footing6 = LoadGraph("images/Stage/Stage_Footing06.png");

	footing4 = LoadGraph("images/Stage/Stage_Footing04.png");
	footing7 = LoadGraph("images/Stage/Stage_Footing07.png");
	footing8 = LoadGraph("images/Stage/Stage_Footing08.png");

}

StageObject::~StageObject()
{
	DeleteGraph(landleft);
	DeleteGraph(landleft2);
	DeleteGraph(landright);
	DeleteGraph(landright2);

	DeleteGraph(footing1);
	DeleteGraph(footing2);
	DeleteGraph(footing3);
	DeleteGraph(footing5);

	DeleteGraph(footing4);
	DeleteGraph(footing7);
	DeleteGraph(footing8);

}