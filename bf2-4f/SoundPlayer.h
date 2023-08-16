#pragma once
#include <map>
#include <string>

using namespace std;

struct Sound
{
	int handle;		//メモリに確保したハンドル
	bool isDone = false;	//最後まで再生されたか
};

class SoundPlayer
{
private:
	SoundPlayer();					//コンストラクタ
	static SoundPlayer* instance;	//インスタンス
public:
	~SoundPlayer();
	//シングルトン
	static SoundPlayer* GetInstance();//インスタンスの取得
	static void DeleteThis();		//自分の削除



private:
	map<string, Sound>bgm;			//BGM用配列
	map<string, Sound>se;			//SE用配列

public:
	static int GetBGM(const char*);		//BGMハンドルの取得
	static int GetSE(const char*);		//SEハンドルの取得
	static void PlayBGM(int handle);	//BGMの再生
	static void PlaySE(int handle, bool isSingle);		//SEの再生
};

