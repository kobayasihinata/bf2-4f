#pragma once
class UI
{
public:
	mutable int gScore = 0;

public:
	void Init();
	int Score();				//スコア計算
	void DrawScore();			//スコア表示

	void AddScore(int point) { gScore += point; }
	int GetScore() { return gScore; }
};