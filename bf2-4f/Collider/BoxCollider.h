#pragma once
#include "ColliderBase.h"
#include"../Area.h"

class BoxCollider :
    public ColliderBase
{
private:
	int sava_enemy_level;	//�G�̃��x���ۑ��p�i�]�T������ΏC���j

protected:
    Area area;
	bool show_flg;		//�\���p�t���O
	bool is_player;		//�v���C���[�H
	bool is_die;		//����ł���H

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
	//���S���W���擾
	Location GetCenter()const
	{
		return Location{ location.x + area.width / 2,location.y + area.height / 2 };
	}
	//show_flg���擾
	int GetShowFlg() { return show_flg; }

	//show_flg��ݒ�
	void SetShowFlg(const bool flg) { show_flg = flg; }

	//is_player���擾
	bool GetIsPlayer() { return is_player; }

	//is_die���擾
	bool GetIsDie() { return is_die; }

	//is_die��ݒ�
	void SetIsDie(const bool flg) { is_die = flg; }

	//save_enemy_level���擾
	int GetSaveEnemyLevel()const { return sava_enemy_level; }

	//save_enemy_level��ݒ�
	void SetSaveEnemyLevel(int level) { sava_enemy_level = level; }
};

