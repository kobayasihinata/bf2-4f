#include "../../System/PadInput/PadInput.h"
#include "ResultScene.h"
#include "DxLib.h"

/*
* コンストラクタ
*/
ResultScene::ResultScene(int score, int kill_count, int avoid_count, int eat_count)
	:score(score),killCount(kill_count),avoidCount(avoid_count),eatCount(eat_count)
{
	imageBack = LoadGraph("images/Result_back.png");
	imageEnemy = LoadGraph("Images/UI_enemy.png");
}

/*
* デストラクタ
*/
ResultScene::~ResultScene()
{

}

/*
* 更新
*/
AbstractScene* ResultScene::Update()
{
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_A))
	{
		return nullptr;
	}
	return this;
}

/*
* 描画
*/
void ResultScene::Draw()const
{
	DrawRotaGraph(D_SCREEN_WIDTH / 2, D_SCREEN_HEIGHT / 2, 1.0, 0, imageBack, TRUE);

	SetFontSize(64);
	DrawFormatString(508, D_SCREEN_HEIGHT / 5, 0, "りざると", 0x000000);

	DrawRotaGraph(350, 350, 2.5, 0, imageEnemy, TRUE);
	DrawString(470, 350, "を切った数", 0, 0xffffff);
	DrawFormatString(840, 350, 0, "%d", killCount);

	DrawString(270, 480, "スコア", 0, 0x000000);
	DrawFormatString(840, 480, 0, "%d", score);

	DrawString(530, 580, "A:進む", 0x000000);

	SetFontSize(16);
}

/*
* 
*/
