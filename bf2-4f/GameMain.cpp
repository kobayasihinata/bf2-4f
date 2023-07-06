#include "Dxlib.h"
#include "GameMain.h"
#include"Title.h"


GameMain::GameMain()
{
	player = new Player();
	stagefloor[0] = new StageFloor(0, 416, 30, 160, 5);
	stagefloor[1] = new StageFloor(479, 416, 30, 160, 5);
	stagefloor[2] = new StageFloor(180, 260, 18, 280, 0);
	staegwall = new StageWall();
	seaImage = LoadGraph("images/Stage/Stage_Sea01.png");
}

GameMain::~GameMain()
{
	delete player;
	delete staegwall;
	delete stagefloor[0];
	delete stagefloor[1];
	delete stagefloor[2];
	DeleteGraph(seaImage);
}

AbstractScene* GameMain::Update()
{
	//stagefloorの範囲だけループする
	for (BoxCollider* stagefloor : stagefloor)
	{
		//各オブジェクトとの当たり判定処理
		player->HitStageCollision(stagefloor);
		//どのオブジェクトとも着地していない場合
		if (player->IsOnFloor(stagefloor) != true) {
			//onshare_flgをfalseにする
			player->SetOnShareFlg(false);
		}
	}
	//各オブジェクトのいずれかに着地している場合
	if (player->IsOnFloor(stagefloor[0]) == true ||
		player->IsOnFloor(stagefloor[1]) == true ||
		player->IsOnFloor(stagefloor[2]) == true)
	{
		//onshare_flgをtrueにする
		player->SetOnShareFlg(true);
	}
	player->Update();
	//プレイヤーの残機が0より小さい場合タイトルに戻る
	if (player->GetPlayerLife() < 0) {
		return new Title();
	}
	return this;
}

void GameMain::Draw()const
{
	player->Draw();
	stagefloor[0]->DrawLandLeft();
	stagefloor[1]->DrawLandRight();
	stagefloor[2]->DrawFooting1();
	//デバッグ用　当たり判定表示
	for (BoxCollider* stagefloor : stagefloor)
	{
		stagefloor->Draw();
	}
	DrawString(0, 0, "ゲームメイン", 0xff0000);
	DrawGraph(159, 444, seaImage, TRUE);
}