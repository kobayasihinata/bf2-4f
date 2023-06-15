#include "SphereCollider.h"
#include "BoxCollider.h"
#include "DxLib.h"

#define _USE_MATH_DEFINES
#include <math.h>

//---------------------
// •`‰æ
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

	bool ret = false;//•Ô‚è’l
	float distance;	//’†SÀ•W‚Ì‹——£

	//’†SÀ•W‚Ì‹——£‚ÌŒvŽZ
	distance = sqrtf(powf(sphere_collider->GetLocation().x - location.x, 2) + powf(sphere_collider->GetLocation().y - location.y, 2));

	if (distance < radius + sphere_collider->GetRadius()) //“–‚½‚è”»’è
	{
		ret = true;
	}

	return ret;
}

bool SphereCollider::HitBox(const BoxCollider* box_collider) const
{

	bool ret = false; //•Ô‚è’l
	float rad; //2“_‚ÌŠp“x
	float sphere_x; //‰~‚ÌÀ•W(x)
	float sphere_y; //‰~‚ÌÀ•W(y)

	//‘ŠŽè‚Ì“–‚½‚è”»’è‚Ì”ÍˆÍ
	float sub_x[2];
	float sub_y[2];

	//Šp“x‚ÌŒvŽZ
	rad = atan2f(box_collider->GetLocation().y - location.y, box_collider->GetLocation().x - location.x);

	//À•W‚ÌŒvŽZ
	sphere_x = location.x + (radius * cosf(rad));
	sphere_y = location.y + (radius * sinf(rad));

	//‘ŠŽè‚Ì“–‚½‚è”»’è‚Ì”ÍˆÍ‚ÌŒvŽZ
	sub_x[0] = box_collider->GetLocation().x - (box_collider->GetArea().width / 2);
	sub_y[0] = box_collider->GetLocation().y - (box_collider->GetArea().height / 2);
	sub_x[1] = sub_x[0] + box_collider->GetArea().width;
	sub_y[1] = sub_y[0] + box_collider->GetArea().height;

	if ((sub_x[0] <= sphere_x) && (sphere_x <= sub_x[1]) && (sub_y[0] <= sphere_y) && (sphere_y <= sub_y[1])) //“–‚½‚è”»’è
	{
		ret = true;
	}

	return ret;
}