#pragma once

class AbstractScene
{
private:

public:

	//デストラクタ
	virtual ~AbstractScene();

	//描画以外の更新
	virtual AbstractScene* Update() = 0;

	//描画の更新
	virtual void Draw() const = 0;
};

