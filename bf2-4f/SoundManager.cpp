#include "SoundManager.h"
#include "SoundPlayer.h"

SoundManager::SoundManager()
{
	// BGM読込
	

	// SE読込
	Start_SE = SoundPlayer::GetSE("Start");
	PlayerWalk_SE = SoundPlayer::GetSE("PlayerWalk");
	PlayerJump_SE = SoundPlayer::GetSE("PlayerJump");
	EnemyMove_SE = SoundPlayer::GetSE("EnemyMove");
	Bubble_SE = SoundPlayer::GetSE("Bubble");
	Crack_SE = SoundPlayer::GetSE("Crack");
	Falling_SE = SoundPlayer::GetSE("Falling");
	Splash_SE = SoundPlayer::GetSE("Splash");
	Para_SE = SoundPlayer::GetSE("Parachute");
	Eatable_SE = SoundPlayer::GetSE("Eatable");
	Restart_SE = SoundPlayer::GetSE("Restart");
	DefeatTheEnemy_SE = SoundPlayer::GetSE("DefeatTheEnemy");
	StageClear_SE = SoundPlayer::GetSE("StageClear");
	GameOver_SE = SoundPlayer::GetSE("GameOver");

	for (int i = 0; i < SOUND_MAX; i++) {
		soundflg[i].Wait = false;
		soundflg[i].Play = false;
	}
	soundflg[0].Wait = true;
}
SoundManager::~SoundManager()
{

}

void SoundManager::Update()
{
	//各サウンドの再生条件と再生する際の処理

	if (soundflg[0].Wait) {
		Stop_All_Sound();
		SoundPlayer::PlaySE(Start_SE, true);
		soundflg[0].Play = true;
	}
	if (soundflg[1].Wait) {
		if (soundflg[0].Play == false && soundflg[4].Play == false && soundflg[9].Play == false &&
			soundflg[10].Play == false && soundflg[11].Play == false) {
			SoundPlayer::PlaySE(PlayerWalk_SE, true);
			soundflg[1].Play = true;
		}
	}
	if (soundflg[2].Wait) {
		if (soundflg[0].Play == false && soundflg[4].Play == false && soundflg[9].Play == false &&
			soundflg[10].Play == false && soundflg[11].Play == false) {
			SoundPlayer::PlaySE(PlayerJump_SE, true);
			soundflg[2].Play = true;
		}
	}
	if (soundflg[3].Wait) {
		if (soundflg[0].Play == false && soundflg[4].Play == false && soundflg[8].Play == false &&
			soundflg[9].Play == false && soundflg[10].Play == false && soundflg[11].Play == false) {
			SoundPlayer::PlaySE(EnemyMove_SE, true);
			soundflg[3].Play = true;
		}
	}
	if (soundflg[4].Wait) {
		if (soundflg[9].Play == false && soundflg[10].Play == false ) {
			StopSoundMem(Para_SE);
			SoundPlayer::PlaySE(Bubble_SE, false);
			soundflg[4].Play = true;
		}
	}
	if (soundflg[5].Wait) {
		if (soundflg[0].Play == false && soundflg[4].Play == false && soundflg[9].Play == false &&
			soundflg[10].Play == false && soundflg[11].Play == false) {
			SoundPlayer::PlaySE(Crack_SE, false);
			soundflg[5].Play = true;
		}
	}
	if (soundflg[6].Wait) {
		StopSoundMem(Start_SE);
		StopSoundMem(Bubble_SE);
		StopSoundMem(Eatable_SE);
		StopSoundMem(Restart_SE);
		StopSoundMem(DefeatTheEnemy_SE);
		SoundPlayer::PlaySE(Falling_SE, true);
		soundflg[6].Play = true;
	}
	if (soundflg[7].Wait) {
		StopSoundMem(Start_SE);
		StopSoundMem(Bubble_SE);
		StopSoundMem(Falling_SE);
		StopSoundMem(Eatable_SE);
		StopSoundMem(Restart_SE);
		SoundPlayer::PlaySE(Splash_SE, true);
		soundflg[7].Play = true;
	}
	if (soundflg[8].Wait) {
		if (soundflg[0].Play == false && soundflg[4].Play == false && soundflg[9].Play == false &&
			soundflg[10].Play == false && soundflg[11].Play == false) {
			StopSoundMem(EnemyMove_SE);
			SoundPlayer::PlaySE(Para_SE, true);
			soundflg[8].Play = true;
		}
	}
	if (soundflg[9].Wait) {
		Stop_All_Sound();
		SoundPlayer::PlaySE(Eatable_SE, true);
		soundflg[9].Play = true;
	}
	if (soundflg[10].Wait) {
		Stop_All_Sound();
		SoundPlayer::PlaySE(Restart_SE, true);
		soundflg[10].Play = true;
	}
	if (soundflg[11].Wait) {
		Stop_All_Sound();
		SoundPlayer::PlaySE(DefeatTheEnemy_SE, false);
		soundflg[11].Play = true;
	}
	if (soundflg[12].Wait) {
		Stop_All_Sound();
		SoundPlayer::PlaySE(StageClear_SE, true);
		soundflg[12].Play = true;
	}
	if (soundflg[13].Wait) {
		Stop_All_Sound();
		SoundPlayer::PlaySE(GameOver_SE, true);
		soundflg[13].Play = true;
	}

	//サウンド終了時に再生中フラグを消す
	if (CheckSoundMem(Start_SE) == false) soundflg[0].Play = false;
	if (CheckSoundMem(PlayerWalk_SE) == false) soundflg[1].Play = false;
	if (CheckSoundMem(PlayerJump_SE) == false) soundflg[2].Play = false;
	if (CheckSoundMem(EnemyMove_SE) == false) soundflg[3].Play = false;
	if (CheckSoundMem(Bubble_SE) == false) soundflg[4].Play = false;
	if (CheckSoundMem(Crack_SE) == false) soundflg[5].Play = false;
	if (CheckSoundMem(Falling_SE) == false) soundflg[6].Play = false;
	if (CheckSoundMem(Splash_SE) == false) soundflg[7].Play = false;
	if (CheckSoundMem(Para_SE) == false) soundflg[8].Play = false;
	if (CheckSoundMem(Eatable_SE) == false) soundflg[9].Play = false;
	if (CheckSoundMem(Restart_SE) == false) soundflg[10].Play = false;
	if (CheckSoundMem(DefeatTheEnemy_SE) == false) soundflg[11].Play = false;
	if (CheckSoundMem(StageClear_SE) == false) soundflg[12].Play = false;
	if (CheckSoundMem(GameOver_SE) == false) soundflg[13].Play = false;


	for (int i = 0; i < SOUND_MAX; i++) {
		soundflg[i].Wait = false;
	}
}

//再生待ちフラグの取得
void SoundManager::PlayP_Walk_SE() {
	soundflg[1].Wait = true;
}
void SoundManager::PlayP_Jump_SE() {
	soundflg[2].Wait = true;
}
void SoundManager::PlayE_Move_SE() {
	soundflg[3].Wait = true;
}
void SoundManager::PlayBubble_SE() {
	soundflg[4].Wait = true;
}
void SoundManager::PlayCrack_SE() {
	soundflg[5].Wait = true;
}
void SoundManager::PlayFalling_SE() {
	soundflg[6].Wait = true;
}
void SoundManager::PlaySplash_SE() {
	soundflg[7].Wait = true;
}
void SoundManager::PlayPara_SE() {
	soundflg[8].Wait = true;
}
void SoundManager::PlayEatable_SE() {
	soundflg[9].Wait = true;
}
void SoundManager::PlayRestart_SE() {
	soundflg[10].Wait = true;
}
void SoundManager::PlayDefeatTheEnemy_SE() {
	soundflg[11].Wait = true;
}
void SoundManager::PlayStageClear_SE() {
	soundflg[12].Wait = true;
}
void SoundManager::PlayGameOver_SE() {
	soundflg[13].Wait = true;
}

//全サウンドの停止
void SoundManager::Stop_All_Sound()
{
	StopSoundMem(Start_SE);
	StopSoundMem(Para_SE);
	StopSoundMem(Eatable_SE);
	StopSoundMem(Restart_SE);
	StopSoundMem(StageClear_SE);
	StopSoundMem(GameOver_SE);
	StopSoundMem(PlayerWalk_SE);
	StopSoundMem(PlayerJump_SE);
	StopSoundMem(EnemyMove_SE);
	StopSoundMem(Bubble_SE);
	StopSoundMem(Falling_SE);
	StopSoundMem(Splash_SE);
	StopSoundMem(Crack_SE);
	StopSoundMem(DefeatTheEnemy_SE);
}