#include"Balloon.h"

//�R���X�g���N�^
Balloon::Balloon(int x, int y)
{
	flg = true;
	location.x = x;
	location.y = y;
	area.width = 32;
	area.height = 40;
	frame = 0;              //�t���[����
	balloon_anim = 0;        //�A�j���[�V�����p�ϐ�
	acs_left = 0;           //�����x��
	acs_right = 0;          //�����x�E

	LoadDivGraph("images/Title/Title_CursorAnimation.png", 4, 4, 1, 32, 64, balloon_image);
	get_balloon_se = LoadSoundMem("sounds/SE_crack.wav");
}

//�f�X�g���N�^
Balloon::~Balloon()
{
	for (int i = 0; i < 4; i++)
	{
		DeleteGraph(balloon_image[i]);
	}
}

void Balloon::Update()
{
	//150�t���[�����ƂɃt���[�����胊�Z�b�g
	if (++frame > 100)
	{
		frame = 0;
	}

	//���E�ɕ��D�����E�ɗh�炷
	if (frame < 50)
	{
		acs_left += 2;
		if (acs_right > 0)
		{
			acs_right -= 3;
		}
	}
	else
	{
		acs_right += 2;
		if (acs_left > 0)
		{
			acs_left -= 3;
		}
	}

	//�ړ�
	location.x = location.x + (acs_right * 0.01) - (acs_left * 0.01);
	location.y -= 1.2;

	if (location.y < -40)
	{
		flg = false;
	}
	if (frame % 10 == 0)
	{
		if (++balloon_anim > 3)
		{
			balloon_anim = 0;
		}
	}
}

void Balloon::Draw() const
{
	if (flg == true)
	{
		DrawGraph(location.x, location.y-10, balloon_image[balloon_anim], TRUE);
	}
}

int Balloon::HitPlayerCollision(const BoxCollider* box_collider)
{
	//�����̓����蔻��͈̔�
	float my_x[2]{ 0,0 };
	float my_y[2]{ 0,0 };

	//����̓����蔻��͈̔�
	float sub_x[2]{ 0,0 };
	float sub_y[2]{ 0,0 };

	//�����̓����蔻��͈̔͂̌v�Z
	my_x[0] = location.x;
	my_y[0] = location.y;
	my_x[1] = my_x[0] + area.width;
	my_y[1] = my_y[0] + area.height;

	//����̓����蔻��͈̔͂̌v�Z
	sub_x[0] = box_collider->GetLocation().x;
	sub_y[0] = box_collider->GetLocation().y;
	sub_x[1] = sub_x[0] + box_collider->GetArea().width;
	sub_y[1] = sub_y[0] + box_collider->GetArea().height;

	if (my_x[0] < sub_x[1] && my_x[1]>sub_x[0] && my_y[0]<sub_y[1] && my_y[1]>sub_y[0] && flg == true)
	{
		flg = false;
		PlaySoundMem(get_balloon_se, DX_PLAYTYPE_BACK);
		return 1;
	}
	return 0;
}
