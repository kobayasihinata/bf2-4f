#include "GameMain.h"
#include "../../Ranking.h"

#include "../../Title.h"
#include "ResultScene.h"
#include "../../System/SoundPlayer/SoundPlayer.h"
#include "DxLib.h"
#include "../../System/KeyManager/KeyManager.h"

//int sceneCHG = false;
#define TIME_LIMIT 200
#define MOVE_SPEED 15

/*
* コンストラクタ
*/
GameMain::GameMain()
{
	mScene = nullptr;
	player = new Player();
	obstacleManager = new ObstacleManager();
	ui = new UI();
	ui->SetLife(player->GetLife());
	ui->SetKillCount(&killCount);
	ui->SetAvoidCount(obstacleManager->GetCount());
	ui->SetEatCount(&eatCount);

	gameMainBGM = SoundPlayer::GetBGM("GameMain");
	boomSE = SoundPlayer::GetSE("Boom");
	eatSE = SoundPlayer::GetSE("eat");
	imageBack = LoadGraph("images/main.png");
	SoundPlayer::PlayBGM(gameMainBGM);

	CutInFont = CreateFontToHandle("HG行書体", 90, 8, DX_FONTTYPE_ANTIALIASING);
	CutInFlg = TRUE;
	CutInTime = TIME_LIMIT;
	MoveString = 0;

	score = 0;
	killCount = 0;
	eatCount = 0;

	frameCount = 0;
	isGameEnd = false;
}

/*
* デストラクタ
*/
GameMain::~GameMain()
{
	delete obstacleManager;
	delete player;
}

/*
* 更新
* 戻り値 次のフレームで更新するシーンのポインタ
*/
AbstractScene* GameMain::Update()
{
	if (CutInFlg == FALSE)
	{
		if (mScene != nullptr)
		{
			mScene = mScene->Update();
			if (mScene == nullptr)
			{
				delete mScene;
				return new Ranking(score);
			}
			return this;
		}

		if (isGameEnd)
		{
			frameCount--;
			if (frameCount <= 0)
			{
				mScene = new ResultScene(score, killCount, *(obstacleManager->GetCount()), eatCount);
			}
			return this;		//以降の処理を止める
		}
		obstacleManager->Update();
		CheckHit();
	}
	else
	{
		if (CutInTime-- <= 0) {
			CutInFlg = FALSE;
		}
		if (++MoveString >= 140) {
			MoveString = 140;
		}
	}

	player->Update();


	if (*(player->GetLife()) == 0)
	{
		isGameEnd = true;
		frameCount = 2 * 60;
	}
	return this;
}

/*
* 描画
*/
void GameMain::Draw()const
{
	DrawGraph(0, 0, imageBack,TRUE);

	obstacleManager->Draw();

	player->DrawPlayer();

	ui->Draw();

	if (CutInFlg == TRUE)
	{
		int ret = DrawStringToHandle(1200 - MoveString * MOVE_SPEED, 250, "よぉい", 0xffffff, CutInFont);
		DrawStringToHandle (4610 - MoveString * (MOVE_SPEED + 15) , 250, "すたぁと", 0xff0000, CutInFont);

	}

	if (mScene != nullptr)
	{
		mScene->Draw();
	}

	DrawFormatString(0, 0, 0xFF0000, "%d", score, 12);
}

/*
* 当たり判定チェック
*/
void GameMain::CheckHit()
{
	//プレイヤーの攻撃
	Attack* attack = player->GetAttack();
	//降ってくるもの達
	vector<ObstacleBase*> obstacles = obstacleManager->GetObstacles();

	//降ってくるものとの当たり判定
	for (ObstacleBase* obstacle : obstacles)
	{

		// プレイヤーの攻撃との当たり判定
		if (attack != nullptr &&		//プレイヤーが攻撃しているか？
			obstacle->GetIsBroken() == false &&	//対象のものが壊れていない(当たり判定を取る状態)か？
			attack->HitCheck(obstacle))	//当たっているか？
		{
			obstacle->ToggleIsBroken();		//壊す
			obstacle->SetFrameCount();		//アニメーション用のフレーム数を設定する
			score += obstacle->GetScore();	//スコア加算

			if (dynamic_cast<Bomb*>(obstacle) != nullptr)
			{	//	斬ったのがボムならダメージを受ける
				SoundPlayer::PlaySE(boomSE, FALSE);
				player->HitDamage();
			}

			if (dynamic_cast<Enemy*>(obstacle) != nullptr)
			{	//	斬ったのがエネミーならキルカウントする
				killCount++;
			}
		}
		
		// プレイヤー本体との当たり判定
		if (obstacle->GetIsBroken() == false &&					//対象のものが見えている(当たり判定を取る状態)か？
			player->HitCheck(obstacle))					//当たっているか
		{
			if (dynamic_cast<Food*>(obstacle) != nullptr)	//食べ物か？
			{
				SoundPlayer::PlaySE(eatSE, FALSE);
				eatCount++;
				score += obstacle->GetScore();
				obstacle->ToggleIsBroken();
			}
			else if (player->GetIsInvincible() != true)
			{
				player->HitDamage();
				if (dynamic_cast<Enemy*>(obstacle) != nullptr)	//エネミーか？(消えないもの？)
				{
					player->HitEnemy();
					score += (int)(obstacle->GetScore() * -0.5);  //減算用
				}
				else											//それ以外（爆弾）の場合
				{
					if(obstacle != nullptr)
					{
						SoundPlayer::PlaySE(boomSE, FALSE);
						score += obstacle->GetScore();
						obstacle->ToggleIsBroken();				//消す
						obstacle->SetFrameCount();				//アニメーション用のフレーム数を設定する
					}
				}

			}

		}
		
	}
}