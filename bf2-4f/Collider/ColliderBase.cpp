#include "ColliderBase.h"
#include "BoxCollider.h"

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

	default:
		ret = false;
		break;
	}

	return ret;
}