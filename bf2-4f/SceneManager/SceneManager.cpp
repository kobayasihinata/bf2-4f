#include "SceneManager.h"
#include <stdio.h>
#include <time.h>
#include "../System/KeyManager/KeyManager.h"
#include "../System/PadInput/PadInput.h"

SceneManager* SceneManager::instance = nullptr;

/*
* デストラクタ
*/
SceneManager::~SceneManager()
{
	delete mScene;
	instance = nullptr; //外から呼ばれる場合既にdeleteされてる為、nullptrを入れるだけでOK
}

/*
* 更新
* 戻り値 次のフレームで更新するシーンのポインタ
*/
AbstractScene* SceneManager::Update()
{
	PAD_INPUT::UpdateKey();
	KeyManager::Update();

	if (KeyManager::OnKeyClicked(KEY_INPUT_ESCAPE)||
		PAD_INPUT::OnButton(XINPUT_BUTTON_BACK))
	{
		return nullptr;
	}

	AbstractScene* nextScene;
	try
	{
		nextScene = mScene->Update();
		if (nextScene != mScene)
		{
			delete mScene;
			mScene = nextScene;
		}
	}
	catch (const char* error_log)
	{
		FILE* fp = NULL;
		time_t timer = time(NULL);
		struct tm date;
		localtime_s(&date, &timer);


		//ファイルオープン
		fopen_s(&fp, "ErrorLog.txt", "a");
		//エラーデータの書き込み
		fprintf_s(fp, "%02d時 %02d分 : %s\n", date.tm_hour, date.tm_min, error_log);
		fclose(fp);

		return nullptr;

	}


	return mScene;
}

/*
* 描画
*/
void SceneManager::Draw()const
{
	mScene->Draw();
}

/*
* 自クラスの作成
* 最初に更新するシーン
*/
SceneManager* SceneManager::Create(AbstractScene* scene)
{
	if (instance == nullptr)
	{
		instance = new SceneManager(scene);
	}
	return instance;
}

/*
* インスタンスの取得
*/
SceneManager* SceneManager::GetInstance()
{
	if (instance != nullptr)
	{
		return instance;
	}
	else
	{
		return nullptr;
	}
}

/*
* インスタンスの削除
*/
void SceneManager::Delete()
{
	if (instance)
	{
		delete instance;
		instance = nullptr;
	}
}