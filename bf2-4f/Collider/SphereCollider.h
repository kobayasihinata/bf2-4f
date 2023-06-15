#pragma once
#include "ColliderBase.h"
class SphereCollider :
    public ColliderBase
{
protected:
	/*
	* ColliderBase:
	*	E_Collider colliderType;
	*	Location location;	//’†SÀ•W
	*/
	float radius;			//”¼Œa
public:

	SphereCollider() :ColliderBase()
	{
		SphereCollider({ 5,5 });
	}

	SphereCollider(Location location, float radius = 5.f) :ColliderBase(location)
	{
		colliderType = E_Collider::Sphere;
		this->radius = radius;
	}

	//•`‰æ
	virtual void Draw()const;

	//SphereCollider‚Æ‚Ì“–‚½‚è”»’è
	bool HitSphere(const SphereCollider* sphere_collider) const override;

	//BoxCollider‚Æ‚Ì“–‚½‚è”»’è
	bool HitBox(const BoxCollider* box_collider) const override;

	//’†SÀ•W‚ÌŽæ“¾
	Location GetLocation() const
	{
		return location;
	}

	//”¼Œa‚ÌŽæ“¾
	float GetRadius() const
	{
		return radius;
	}

	//’†SÀ•W‚ÌÝ’è
	void SetLocation(Location location)
	{
		this->location = location;
	}

};

