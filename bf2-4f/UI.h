#pragma once
class UI
{
public:
	mutable int gScore = 0;

public:
	void Init();
	int Score();				//�X�R�A�v�Z
	void DrawScore();			//�X�R�A�\��

	void AddScore(int point) { gScore += point; }
	int GetScore() { return gScore; }
};