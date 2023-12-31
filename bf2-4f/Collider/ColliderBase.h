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
		colliderType = E_Collider::Null;
	}

protected:

	E_Collider colliderType;
	Location location;	//座標

public:

	//座標の取得
	Location GetLocation()const
	{
		return location;
	}
	//座標の設定
	virtual void SetLocation(Location location)
	{
		this->location = location;
	}

	//BoxColliderとの当たり判定
	virtual bool HitBox(const BoxCollider* box_collider) const = 0;

	bool HitCheck(const ColliderBase* collider)const;

	virtual void Draw()const = 0;

	E_Collider GetColliderType()const { return colliderType; };

};

