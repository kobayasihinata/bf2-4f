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

	//BoxCollider�Ƃ̓����蔻��
	bool HitBox(const BoxCollider* box_collider) const override;


	//���W�̎擾
	Location GetLocation()const;

	//�͈͂̎擾
	Area GetArea()const;

	//����̍��W���擾
	Location GetMin()const
	{
		return Location{ location.x,location.y};
	}
	//�E���̍��W���擾
	Location GetMax()const
	{
		return Location{ location.x + area.width,location.y + area.height};
	}
};

