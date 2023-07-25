#pragma once
#include "DxLib.h"

class AbstractScene
{
protected:
	int numbers_image[10];	//�����̉摜
	int dammy = LoadDivGraph("images/UI/UI_NumAnimation.png", 10, 10, 1, 32, 32, numbers_image);
public:

	//�f�X�g���N�^
	virtual ~AbstractScene();

	//�`��ȊO�̍X�V
	virtual AbstractScene* Update() = 0;

	//�`��̍X�V
	virtual void Draw() const = 0;

	//�����̕`��(UI.h��cpp�ɏ����̂��L��)
	void DrawNumber(int x, int y, int score)const;
};

