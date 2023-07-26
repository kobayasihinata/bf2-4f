#include "BoxCollider.h"
#include "DxLib.h"

/*
* コンストラクタ
* Location ColliderBase  座標
* Area		BoxCollider	 範囲
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
		, 0xFFFF00, FALSE);
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
	my_x[0] = location.x;
	my_y[0] = location.y;
	my_x[1] = my_x[0] + area.width;
	my_y[1] = my_y[0] + area.height;

	//相手の当たり判定の範囲の計算
	sub_x[0] = box_collider->GetLocation().x;
	sub_y[0] = box_collider->GetLocation().y;
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
// 座標の取得
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