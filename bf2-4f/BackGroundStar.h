#pragma once
#include"Dxlib.h"
#include"Define.h"
#include"Location.h"

class BackGroundStar
{
private:
	int type;			//���̐F�^�C�v
    Location star_pos;	//���̕`��ʒu
    int star_color;		//���̐F
    int star_drawtime;  //���̈ʒu�X�V�܂ł̎���

public:
	//�R���X�g���N�^
	BackGroundStar(int stage);

	//�f�X�g���N�^
	~BackGroundStar();

	//�`��ȊO�̏���
	void Update();

	//�`�揈��
	void Draw()const;

	//���̐F�𒊑I����
	void SetColor(int type);

	//���݂̃X�e�[�W�����󂯎��
	void GetType(int stage) { type = stage; }
};
