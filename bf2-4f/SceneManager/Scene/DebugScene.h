#include "../AbstractScene.h"
#include "../../attack.h"
#include "../../Collider/BoxCollider.h"
#include"../../Player.h"
#include"../../Result.h"
#pragma once
class DebugScene:
	public AbstractScene
{
public:
	DebugScene();
	~DebugScene();

	//描画以外の更新を実行
	AbstractScene* Update()override;

	//描画に関することを実装
	void Draw() const override;

private:
	BoxCollider* box;
	Player* player;
	Result* result;
	int back;
};

