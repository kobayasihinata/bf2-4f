#pragma once
#include "AbstractScene.h"

class Stage : public AbstractScene
{
private:
	int stageimage;


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

