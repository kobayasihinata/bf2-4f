#pragma once
#include "DxLib.h"

enum Music_State
{
	Start,
	E_Move,
	Bubble,
	Crack,
	Falling,
	Splash,
	Eatable,
	Restart,
	DefeatTheEnemy,
	StageClear,
	GameOver,
	None
};
class SoundManager
{
protected:
	int OldState;
	int NowState;
	int music_state;
	
	int priority;

	// BGM
	int Para_BGM;               //敵パラシュートBGM
	

	// SE
	int Start_SE;               //ゲームスタートSE
	int PlayerWalk_SE;          //プレイヤー歩行SE
	int PlayerJump_SE;          //プレイヤー浮上SE
	int EnemyMove_SE;           //敵浮上SE
	int Bubble_SE;              //バブル取得SE
	int Falling_SE;             //落下SE
	int Splash_SE;              //水しぶきSE
	int Crack_SE;               //風船破裂SE
	int Eatable_SE;             //サカナ捕食SE
	int Restart_SE;		        //コンテニューSE
	int DefeatTheEnemy_SE;      //敵撃破SE
	int StageClear_SE;			//ステージクリアSE
	int GameOver_SE;            //ゲームオーバーSE
	
public:
	//コンストラクタ
	SoundManager();

	//デストラクタ
	~SoundManager();

	//描画以外の更新を実行
	void Update();

	//音の再生は可能か
	void PlayPara_BGM(int i);

	void PlayE_Move_SE();
	void PlayBubble_SE();
	void PlayCrack_SE();
	void PlayFalling_SE();
	void PlaySplash_SE();
	void PlayEatable_SE();
	void PlayRestart_SE();
	void PlayDefeatTheEnemy_SE();
	void PlayStageClear_SE();
	void PlayGameOver_SE();
	
	 
	//音を止める
	void Stop_All_Music();
	void Stop_Fall();
};

