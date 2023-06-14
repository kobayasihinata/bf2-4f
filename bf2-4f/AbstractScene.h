#pragma once

class AbstractScene
{
private:

public:

	//�f�X�g���N�^
	virtual ~AbstractScene();

	//�`��ȊO�̍X�V
	virtual AbstractScene* Update() = 0;

	//�`��̍X�V
	virtual void Draw() const = 0;
};

