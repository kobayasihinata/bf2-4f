#pragma once
#include"../Location.h"
#include "../E_Collider.h"

class BoxCollider;

class ColliderBase
{

public:

	ColliderBase(Location location = { 100,100 })
	{
		this->location = location;
	}

protected:

	E_Collider colliderType;
	Location location;	//���S���W

public:

	//���S���W�̎擾
	Location GetLocation()const
	{
		return location;
	}
	//���S���W�̐ݒ�
	virtual void SetLocation(Location location)
	{
		this->location = location;
	}

	//BoxCollider�Ƃ̓����蔻��
	virtual bool HitBox(const BoxCollider* box_collider) const = 0;

	bool HitCheck(const ColliderBase* collider)const;

	virtual void Draw()const = 0;

	E_Collider GetColliderType()const { return colliderType; };

};
