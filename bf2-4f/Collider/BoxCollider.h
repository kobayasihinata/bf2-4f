#pragma once
#include "ColliderBase.h"
#include"../Area.h"

class BoxCollider :
    public ColliderBase
{
protected:
    Area area;

public:
	BoxCollider(Location location = Location{}, Area area = Area{ 100,100 });
	~BoxCollider();

	virtual void Draw()const;

	//SphereColliderとの当たり判定
	bool HitSphere(const class SphereCollider* sphere_collider) const override;

	//BoxColliderとの当たり判定
	bool HitBox(const class BoxCollider* box_collider) const override;

	//中心座標の取得
	Location GetLocation()const;

	//範囲の取得
	Area GetArea()const;

	//左上の座標を取得
	Location GetMin()const
	{
		return Location{ location.x - area.width / 2,location.y - area.height / 2 };
	}
	//右下の座標を取得
	Location GetMax()const
	{
		return Location{ location.x + area.width / 2,location.y + area.height / 2 };
	}
};

