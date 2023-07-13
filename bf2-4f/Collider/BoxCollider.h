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

	//BoxColliderとの当たり判定
	bool HitBox(const BoxCollider* box_collider) const override;


	//座標の取得
	Location GetLocation()const;

	//範囲の取得
	Area GetArea()const;

	//左上の座標を取得
	Location GetMin()const
	{
		return Location{ location.x,location.y};
	}
	//右下の座標を取得
	Location GetMax()const
	{
		return Location{ location.x + area.width,location.y + area.height};
	}
};

