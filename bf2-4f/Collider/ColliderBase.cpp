#include "ColliderBase.h"
#include "BoxCollider.h"
#include "SphereCollider.h"

//------------------------------------
// �����蔻��`�F�b�N
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
* 2�̃x�N�g���̂Ȃ��p���s�p���ǂ��������߂�
*/
bool ColliderBase::CheckIsAcute(Location vector1, Location vector2)const
{
	bool is_acute = false;

	/*
	* ���ς̐��� inner puroduct = A�EB
	* inner puroduct < 0->�݊p
	* inner puroduct = 0->���p
	* inner puroduct > 0->�s�p�𗘗p����
	*/
	float inner_product = vector1.x * vector2.x + vector1.y * vector2.y;

	if (inner_product >= 0)
	{
		is_acute = true;
	}

	return is_acute;
}