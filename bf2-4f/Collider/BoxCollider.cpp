#include "BoxCollider.h"
#include "SphereCollider.h"
#include "DxLib.h"

/*
* �R���X�g���N�^
* Location ColliderBase ���S���W
* Area		BoxCollider	 �͈�
*/
BoxCollider::BoxCollider(Location location, Area area)
	:ColliderBase(location)
{
	colliderType = E_Collider::Box;
	this->area = area;

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
		, 0xFFFF00, FALSE, 3.f);
}

//-----------------------------------
// SphereCollider�Ƃ̓����蔻��
//-----------------------------------
bool BoxCollider::HitSphere(const class SphereCollider* sphere_collider) const
{

	bool ret = false;//�Ԃ�l
	float rad; //2�_�̊p�x
	float sphere_x; //�~�̍��W(x)
	float sphere_y; //�~�̍��W(y)

	//�����̓����蔻��͈̔�
	float my_x[2];
	float my_y[2];

	//�p�x�̌v�Z
	rad = atan2f(location.y - sphere_collider->GetLocation().y,
		location.x - sphere_collider->GetLocation().x);

	//���W�̌v�Z
	sphere_x = sphere_collider->GetLocation().x
		+ (sphere_collider->GetRadius() * cosf(rad));
	sphere_y = sphere_collider->GetLocation().y
		+ (sphere_collider->GetRadius() * sinf(rad));

	//�����̓����蔻��͈̔͂̌v�Z
	my_x[0] = location.x - (area.width / 2);
	my_y[0] = location.y - (area.height / 2);
	my_x[1] = my_x[0] + area.width;
	my_y[1] = my_y[0] + area.height;

	if ((my_x[0] <= sphere_x) && (sphere_x <= my_x[1])
		&& (my_y[0] <= sphere_y) && (sphere_y <= my_y[1])) //�����蔻��
	{
		ret = true;
	}

	return ret;
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
	my_x[0] = location.x - (area.width / 2);
	my_y[0] = location.y - (area.height / 2);
	my_x[1] = my_x[0] + area.width;
	my_y[1] = my_y[0] + area.height;

	//����̓����蔻��͈̔͂̌v�Z
	sub_x[0] = box_collider->GetLocation().x - (box_collider->GetArea().width / 2);
	sub_y[0] = box_collider->GetLocation().y - (box_collider->GetArea().height / 2);
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
// ���S���W�̎擾
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