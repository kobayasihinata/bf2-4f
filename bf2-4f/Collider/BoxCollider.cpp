#include "BoxCollider.h"
#include "SphereCollider.h"
#include "DxLib.h"

/*
* コンストラクタ
* Location ColliderBase 中心座標
* Area		BoxCollider	 範囲
*/
BoxCollider::BoxCollider(Location location, Area area)
	:ColliderBase(location)
{
	colliderType = E_Collider::Box;
	this->area = area;

}

//-----------------------------------
// デストラクタ
//-----------------------------------
BoxCollider::~BoxCollider()
{

}


/*
* 描画関数
* 子クラスから呼ぶことで当たり判定の描画をする
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
// SphereColliderとの当たり判定
//-----------------------------------
bool BoxCollider::HitSphere(const class SphereCollider* sphere_collider) const
{

	bool ret = false;//返り値
	float rad; //2点の角度
	float sphere_x; //円の座標(x)
	float sphere_y; //円の座標(y)

	//自分の当たり判定の範囲
	float my_x[2];
	float my_y[2];

	//角度の計算
	rad = atan2f(location.y - sphere_collider->GetLocation().y,
		location.x - sphere_collider->GetLocation().x);

	//座標の計算
	sphere_x = sphere_collider->GetLocation().x
		+ (sphere_collider->GetRadius() * cosf(rad));
	sphere_y = sphere_collider->GetLocation().y
		+ (sphere_collider->GetRadius() * sinf(rad));

	//自分の当たり判定の範囲の計算
	my_x[0] = location.x - (area.width / 2);
	my_y[0] = location.y - (area.height / 2);
	my_x[1] = my_x[0] + area.width;
	my_y[1] = my_y[0] + area.height;

	if ((my_x[0] <= sphere_x) && (sphere_x <= my_x[1])
		&& (my_y[0] <= sphere_y) && (sphere_y <= my_y[1])) //当たり判定
	{
		ret = true;
	}

	return ret;
}

//-----------------------------------
// BoxColliderとの当たり判定
//-----------------------------------
bool BoxCollider::HitBox(const BoxCollider* box_collider) const
{

	bool ret = false; //返り値

	//自分の当たり判定の範囲
	float my_x[2];
	float my_y[2];

	//相手の当たり判定の範囲
	float sub_x[2];
	float sub_y[2];

	//自分の当たり判定の範囲の計算
	my_x[0] = location.x - (area.width / 2);
	my_y[0] = location.y - (area.height / 2);
	my_x[1] = my_x[0] + area.width;
	my_y[1] = my_y[0] + area.height;

	//相手の当たり判定の範囲の計算
	sub_x[0] = box_collider->GetLocation().x - (box_collider->GetArea().width / 2);
	sub_y[0] = box_collider->GetLocation().y - (box_collider->GetArea().height / 2);
	sub_x[1] = sub_x[0] + box_collider->GetArea().width;
	sub_y[1] = sub_y[0] + box_collider->GetArea().height;

	if ((my_x[0] <= sub_x[1]) &&
		(sub_x[0] <= my_x[1]) &&
		(my_y[0] <= sub_y[1]) &&
		(sub_y[0] <= my_y[1])) //当たり判定
	{
		ret = true;
	}

	return ret;
}

//-----------------------------------
// 中心座標の取得
//-----------------------------------
Location BoxCollider::GetLocation()const
{
	return location;
}

//-----------------------------------
// 半径の取得
//-----------------------------------
Area BoxCollider::GetArea()const
{
	return area;
}