#pragma once
#include "DxLib.h"


#define SOUND_MAX 14
class SoundManager
{
protected:
	struct Soundflg {
		bool Wait; // 再生待ち
		bool Play; // 再生中
	};
	Soundflg soundflg[SOUND_MAX];

	// BGM
	

	// SE
	int Start_SE;               //ゲームスタートSE(0)
	int PlayerWalk_SE;          //プレイヤー歩行SE(1)
	int PlayerJump_SE;          //プレイヤー浮上SE(2)
	int EnemyMove_SE;           //敵浮上SE(3)
	int Bubble_SE;              //バブル取得SE(4)
	int Crack_SE;               //風船破裂SE(5)
	int Falling_SE;             //落下SE(6)
	int Splash_SE;              //水しぶきSE(7)
	int Para_SE;                //敵パラシュートBGM(8)
	int Eatable_SE;             //サカナ捕食SE(9)
	int Restart_SE;		        //コンテニューSE(10)
	int DefeatTheEnemy_SE;      //敵撃破SE(11)
	int StageClear_SE;			//ステージクリアSE(12)
	int GameOver_SE;            //ゲームオーバーSE(13)
	
public:
	//コンストラクタ
	SoundManager();

	//デストラクタ
	~SoundManager();

	//描画以外の更新を実行
	void Update();

	//音の再生は可能か
	
	void PlayP_Walk_SE();
	void PlayP_Jump_SE();
	void PlayE_Move_SE();
	void PlayBubble_SE();
	void PlayCrack_SE();
	void PlayFalling_SE();
	void PlaySplash_SE();
	void PlayPara_SE();
	void PlayEatable_SE();
	void PlayRestart_SE();
	void PlayDefeatTheEnemy_SE();
	void PlayStageClear_SE();
	void PlayGameOver_SE();
	
	 
	//音を止める
	void Stop_All_Sound();
	void Stop_E_Move() { StopSoundMem(EnemyMove_SE); }
	void Stop_Para() { StopSoundMem(Para_SE); }

	void Reset_flg() {
		for (int i = 0; i < SOUND_MAX; i++) {
			soundflg[i].Wait = false;
			soundflg[i].Play = false;
		}
	}
};

