#include "DebugScene.h"
#include "../../System/SoundPlayer/SoundPlayer.h"
#include "../../System/KeyManager/KeyManager.h"

#include "DxLib.h"
/*
* コンストラクタ
*/
DebugScene::DebugScene()
{
	//attack = new Attack();
	box = new BoxCollider({300,250},{25,25});
	player = new Player();
	//result = new Result(0,0);
}

/*
* デストラクタ
*/
DebugScene::~DebugScene()
{
	delete box;
	delete player;
	delete result;
}

/*
* 更新
* 戻り値 次のフレームで更新するシーンのポインタ
*/
AbstractScene* DebugScene::Update()
{
	player->Update();
	return this;
}

/*
* 描画
*/
void DebugScene::Draw()const
{
	//attack->Draw();
	//box->Draw();
	//result->Draw();
	player->DrawPlayer();
	const Attack* attack = player->GetAttack();
	if (attack != nullptr && attack->HitCheck(box))
	{
		DrawString(0, 0, "HIT", 0xFFFFFF);
	}
}