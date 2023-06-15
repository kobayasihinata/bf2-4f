#include "ColliderBase.h"
#include "BoxCollider.h"
#include "SphereCollider.h"

//------------------------------------
// 当たり判定チェック
//------------------------------------
bool ColliderBase::HitCheck(const ColliderBase* collider)const
{
	bool ret = false;
	E_Collider colliderType = collider->GetColliderType();

	switch (colliderType)
	{
	case E_Collider::Null:
		ret = false;
		break;

	case E_Collider::Box:
		ret = HitBox(static_cast<const BoxCollider*>(collider));
		break;

	case E_Collider::Sphere:
		ret = HitSphere(static_cast<const SphereCollider*>(collider));
		break;

	default:
		ret = false;
		break;
	}

	return ret;
}

/*
* 2つのベクトルのなす角が鋭角かどうかを求める
*/
bool ColliderBase::CheckIsAcute(Location vector1, Location vector2)const
{
	bool is_acute = false;

	/*
	* 内積の性質 inner puroduct = A・B
	* inner puroduct < 0->鈍角
	* inner puroduct = 0->直角
	* inner puroduct > 0->鋭角を利用する
	*/
	float inner_product = vector1.x * vector2.x + vector1.y * vector2.y;

	if (inner_product >= 0)
	{
		is_acute = true;
	}

	return is_acute;
}