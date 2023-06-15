#include "SphereCollider.h"
#include "BoxCollider.h"
#include "DxLib.h"

#define _USE_MATH_DEFINES
#include <math.h>

//---------------------
// 描画
//---------------------
void SphereCollider::Draw()const
{

	DrawCircleAA(
		GetLocation().x
		, GetLocation().y
		, GetRadius(), 10, GetColor(128, 128, 128), TRUE);
}

//-----------------------------------
// SphereColliderとの当たり判定
//-----------------------------------
bool SphereCollider::HitSphere(const SphereCollider* sphere_collider) const
{

	bool ret = false;//返り値
	float distance;	//中心座標の距離

	//中心座標の距離の計算
	distance = sqrtf(powf(sphere_collider->GetLocation().x - location.x, 2) + powf(sphere_collider->GetLocation().y - location.y, 2));

	if (distance < radius + sphere_collider->GetRadius()) //当たり判定
	{
		ret = true;
	}

	return ret;
}

//-----------------------------------
// BoxColliderとの当たり判定
//-----------------------------------
bool SphereCollider::HitBox(const BoxCollider* box_collider) const
{

	bool ret = false; //返り値
	float rad; //2点の角度
	float sphere_x; //円の座標(x)
	float sphere_y; //円の座標(y)

	//相手の当たり判定の範囲
	float sub_x[2];
	float sub_y[2];

	//角度の計算
	rad = atan2f(box_collider->GetLocation().y - location.y, box_collider->GetLocation().x - location.x);

	//座標の計算
	sphere_x = location.x + (radius * cosf(rad));
	sphere_y = location.y + (radius * sinf(rad));

	//相手の当たり判定の範囲の計算
	sub_x[0] = box_collider->GetLocation().x - (box_collider->GetArea().width / 2);
	sub_y[0] = box_collider->GetLocation().y - (box_collider->GetArea().height / 2);
	sub_x[1] = sub_x[0] + box_collider->GetArea().width;
	sub_y[1] = sub_y[0] + box_collider->GetArea().height;

	if ((sub_x[0] <= sphere_x) && (sphere_x <= sub_x[1]) && (sub_y[0] <= sphere_y) && (sphere_y <= sub_y[1])) //当たり判定
	{
		ret = true;
	}

	return ret;
}