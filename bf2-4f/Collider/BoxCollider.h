#pragma once
#include "ColliderBase.h"
#include"../Area.h"

class BoxCollider :
    public ColliderBase
{
private:
	int sava_enemy_level;

protected:
    Area area;
	bool show_flg;		//表示用フラグ
	bool is_player;		//プレイヤーか？

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
	//中心座標を取得
	Location GetCenter()const
	{
		return Location{ location.x + area.width / 2,location.y + area.height / 2 };
	}

	//show_flgを設定
	void SetShowFlg(const bool flg) { show_flg = flg; }

	//is_playerを取得
	bool GetIsPlayer() { return is_player; }

	//save_enemy_levelを設定
	void SetSaveEnemyLevel(int level) { sava_enemy_level = level; }
	//save_enemy_levelを取得
	int GetSaveEnemyLevel()const { return sava_enemy_level; }
};

