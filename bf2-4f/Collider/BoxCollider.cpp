#include "BoxCollider.h"
#include "DxLib.h"

/*
* �R���X�g���N�^
* Location ColliderBase  ���W
* Area		BoxCollider	 �͈�
*/
BoxCollider::BoxCollider(Location location, Area area)
	:ColliderBase(location)
{
	colliderType = E_Collider::Box;
	this->area = area;
	show_flg = true;
	is_player = false;
	is_die = false;
	sava_enemy_level = 0;
}

//-----------------------------------
// �f�X�g���N�^
//-----------------------------------
BoxCollider::~BoxCollider()
{

}


/*
* �`��֐�
* �q�N���X����ĂԂ��Ƃœ����蔻��̕`�������
*/
void BoxCollider::Draw()const
{
	Location min = GetMin();
	Location max = GetMax();
	DrawBoxAA(
		min.x, min.y
		, max.x, max.y
		, 0xFFFF00, FALSE);
}

//-----------------------------------
// BoxCollider�Ƃ̓����蔻��
//-----------------------------------
bool BoxCollider::HitBox(const BoxCollider* box_collider) const
{

	bool ret = false; //�Ԃ�l

	//�����̓����蔻��͈̔�
	float my_x[2];
	float my_y[2];

	//����̓����蔻��͈̔�
	float sub_x[2];
	float sub_y[2];

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

	if ((my_x[0] <= sub_x[1]) &&
		(sub_x[0] <= my_x[1]) &&
		(my_y[0] <= sub_y[1]) &&
		(sub_y[0] <= my_y[1])) //�����蔻��
	{
		ret = true;
	}
	return ret;
}

//-----------------------------------
// ���W�̎擾
//-----------------------------------
Location BoxCollider::GetLocation()const
{
	return location;
}

//-----------------------------------
// ���a�̎擾
//-----------------------------------
Area BoxCollider::GetArea()const
{
	return area;
}