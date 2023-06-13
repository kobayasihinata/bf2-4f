#pragma once
#include "../../common.h"
#include "../AbstractScene.h"
#include "../../ObstacleManager.h"
#include "../../Player.h"
#include "../../UI.h"

class GameMain :public AbstractScene
{

public:
	GameMain();
	~GameMain();

	//描画以外の更新を実行
	AbstractScene* Update()override;

	//描画に関することを実装
	void Draw() const override;
	//void Updata() override;

private:
	AbstractScene* mScene;
	ObstacleManager* obstacleManager;
	Player* player;
	UI* ui;

	int gameMainBGM;
	int boomSE;
	int eatSE;
	int imageBack;
	int CutInFont;
	bool CutInFlg;
	int CutInTime;
	int MoveString;

	int score;
	int killCount;
	int eatCount;

	int frameCount;
	bool isGameEnd;

public:
	void CheckHit();	//当たり判定
};

