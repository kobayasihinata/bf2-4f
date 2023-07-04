#pragma once
#include "AbstractScene.h"

class Stage : 
	public AbstractScene
{
private:
	int stagefloor;
	int landleft;
	int landright;
	int sea;
	int footing1;
	int footing2;
	int footing3;
	int footing4;
	int footing5;


public:
	//�R���X�g���N�^
	Stage();
	//�f�X�g���N�^
	~Stage();

	//�`��ȊO�̏���
	AbstractScene* Update()override;

	//�`�揈��
	void Draw()const override;

};

