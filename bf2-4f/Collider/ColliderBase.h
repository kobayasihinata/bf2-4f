#pragma once
#include"../Location.h"
#include "../E_Collider.h"

#define _USE_MATH_DEFINES
#include <math.h>

class SphereCollider;
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
	Location location;	//中心座標

	//2つのベクトルのなす角が鋭角かどうかを求める
	bool CheckIsAcute(Location vector1, Location vector2)const;

public:

	//中心座標の取得
	Location GetLocation()const
	{
		return location;
	}
	//中心座標の設定
	virtual void SetLocation(Location location)
	{
		this->location = location;
	}

	//SphereColliderとの当たり判定
	virtual bool HitSphere(const SphereCollider* sphere_collider) const = 0;

	//BoxColliderとの当たり判定
	virtual bool HitBox(const BoxCollider* box_collider) const = 0;

	bool HitCheck(const ColliderBase* collider)const;

	virtual void Draw()const = 0;

	E_Collider GetColliderType()const { return colliderType; };

};

