#include "SoundManager.h"
#include "SoundPlayer.h"

SoundManager::SoundManager()
{
	music_state = Start;

	// BGMì«çû
	Para_BGM = SoundPlayer::GetBGM("Parachute");

	// SEì«çû
	Start_SE = SoundPlayer::GetSE("Start");
	PlayerWalk_SE = SoundPlayer::GetSE("PlayerWalk");
	PlayerJump_SE = SoundPlayer::GetSE("PlayerJump");
	EnemyMove_SE = SoundPlayer::GetSE("EnemyMove");
	Bubble_SE = SoundPlayer::GetSE("Bubble");
	Crack_SE = SoundPlayer::GetSE("Crack");
	Falling_SE = SoundPlayer::GetSE("Falling");
	Splash_SE = SoundPlayer::GetSE("Splash");
	Eatable_SE = SoundPlayer::GetSE("Eatable");
	Restart_SE = SoundPlayer::GetSE("Restart");
	DefeatTheEnemy_SE = SoundPlayer::GetSE("DefeatTheEnemy");
	StageClear_SE = SoundPlayer::GetSE("StageClear");
	GameOver_SE = SoundPlayer::GetSE("GameOver");
}
SoundManager::~SoundManager()
{

}

void SoundManager::Update()
{
	OldState = NowState;
	NowState = music_state;
	priority = 0;

	if (NowState != OldState)
	{
		SoundManager::Stop_All_Music();
		switch (music_state)
		{
		case Start:
			SoundPlayer::PlaySE(Start_SE, true);
			priority = 3;
			break;
		case E_Move:
			SoundPlayer::PlaySE(EnemyMove_SE, true);
			priority = 0;
			break;
		case Bubble:
			SoundPlayer::PlaySE(Bubble_SE, true);
			priority = 2;
			break;
		case Crack:
			SoundPlayer::PlaySE(Crack_SE, false);
			priority = 1;
			break;
		case Falling:
			SoundPlayer::PlaySE(Falling_SE, true);
			priority = 3;
			break;
		case Splash:
			SoundPlayer::PlaySE(Splash_SE, false);
			priority = 3;
			break;
		case Eatable:
			SoundPlayer::PlaySE(Eatable_SE, true);
			priority = 3;
			break;
		case Restart:
			SoundPlayer::PlaySE(Restart_SE, true);
			priority = 3;
			break;
		case DefeatTheEnemy:
			SoundPlayer::PlaySE(DefeatTheEnemy_SE, true);
			priority = 3;
			break;
		case StageClear:
			SoundPlayer::PlaySE(StageClear_SE, true);
			priority = 3;
			break;
		case GameOver:
			SoundPlayer::PlaySE(GameOver_SE, true);
			priority = 2;
			break;
		default:
			break;
		};
	}
	else
	{
		switch (music_state)
		{
		case Start:
			if (CheckSoundMem(Start_SE)) priority = 3;
			break;
		case E_Move:
			if (CheckSoundMem(EnemyMove_SE)) priority = 0;
			break;
		case Bubble:
			if (CheckSoundMem(Bubble_SE)) priority = 2;
			break;
		case Crack:
			if (CheckSoundMem(Crack_SE)) priority = 2;
			break;
		case Falling:
			if (CheckSoundMem(Falling_SE)) priority = 2;
			break;
		case Splash:
			if (CheckSoundMem(Splash_SE)) priority = 3;
			break;
		case Eatable:
			if (CheckSoundMem(Eatable_SE)) priority = 3;
			break;
		case Restart:
			if (CheckSoundMem(Restart_SE)) priority = 3;
			break;
		case DefeatTheEnemy:
			if (CheckSoundMem(DefeatTheEnemy_SE)) priority = 3;
			break;
		case StageClear:
			if (CheckSoundMem(StageClear_SE)) priority = 3;
			break;
		case GameOver:
			if (CheckSoundMem(GameOver_SE)) priority = 2;
			break;
		default:
			break;
		};
	}
	if (priority == 0) {
		music_state = None;
	}
}

void SoundManager::PlayPara_BGM(int i) {
	if (i) {
		if (priority < 2)SoundPlayer::PlayBGM(Para_BGM);
	} else {
		StopSoundMem(Para_BGM);
	}
}


void SoundManager::PlayE_Move_SE() {
	if (priority = 0) music_state = E_Move;
}
void SoundManager::PlayBubble_SE() {
	if (priority < 2) music_state = Bubble;
}
void SoundManager::PlayCrack_SE() {
	if (priority < 2) music_state = Crack;
}
void SoundManager::PlayFalling_SE() {
	if (priority < 2) music_state = Falling;
}
void SoundManager::PlaySplash_SE() {
	if (priority < 3) music_state = Splash;
}
void SoundManager::PlayEatable_SE() {
	if (priority < 3) music_state = Eatable;
}
void SoundManager::PlayRestart_SE() {
	if (priority < 2) music_state = Restart;
}
void SoundManager::PlayDefeatTheEnemy_SE() {
	if (priority < 3) music_state = DefeatTheEnemy;
}
void SoundManager::PlayStageClear_SE() {
	if (priority < 3) music_state = StageClear;
}
void SoundManager::PlayGameOver_SE() {
	if (priority < 2) music_state = GameOver;
}

void SoundManager::Stop_All_Music()
{
	StopSoundMem(Start_SE);
	StopSoundMem(Para_BGM);
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

void SoundManager::Stop_Fall() {
	StopSoundMem(Falling_SE);
	music_state = Splash;
}