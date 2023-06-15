#include "SphereCollider.h"
#include "BoxCollider.h"
#include "DxLib.h"

#define _USE_MATH_DEFINES
#include <math.h>

//---------------------
// �`��
//---------------------
void SphereCollider::Draw()const
{

	DrawCircleAA(
		GetLocation().x
		, GetLocation().y
		, GetRadius(), 10, GetColor(128, 128, 128), TRUE);
}

bool SphereCollider::HitSphere(const SphereCollider* sphere_collider) const
{

	bool ret = false;//�Ԃ�l
	float distance;	//���S���W�̋���

	//���S���W�̋����̌v�Z
	distance = sqrtf(powf(sphere_collider->GetLocation().x - location.x, 2) + powf(sphere_collider->GetLocation().y - location.y, 2));

	if (distance < radius + sphere_collider->GetRadius()) //�����蔻��
	{
		ret = true;
	}

	return ret;
}

bool SphereCollider::HitBox(const BoxCollider* box_collider) const
{

	bool ret = false; //�Ԃ�l
	float rad; //2�_�̊p�x
	float sphere_x; //�~�̍��W(x)
	float sphere_y; //�~�̍��W(y)

	//����̓����蔻��͈̔�
	float sub_x[2];
	float sub_y[2];

	//�p�x�̌v�Z
	rad = atan2f(box_collider->GetLocation().y - location.y, box_collider->GetLocation().x - location.x);

	//���W�̌v�Z
	sphere_x = location.x + (radius * cosf(rad));
	sphere_y = location.y + (radius * sinf(rad));

	//����̓����蔻��͈̔͂̌v�Z
	sub_x[0] = box_collider->GetLocation().x - (box_collider->GetArea().width / 2);
	sub_y[0] = box_collider->GetLocation().y - (box_collider->GetArea().height / 2);
	sub_x[1] = sub_x[0] + box_collider->GetArea().width;
	sub_y[1] = sub_y[0] + box_collider->GetArea().height;

	if ((sub_x[0] <= sphere_x) && (sphere_x <= sub_x[1]) && (sub_y[0] <= sphere_y) && (sphere_y <= sub_y[1])) //�����蔻��
	{
		ret = true;
	}

	return ret;
}