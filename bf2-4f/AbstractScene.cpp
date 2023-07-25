#include "AbstractScene.h"
#include "math.h"

AbstractScene::~AbstractScene()
{

}

void AbstractScene::DrawNumber(int x, int y, int score)const
{
	int a;
	int value = score;
	for (int i = 5; i >= 0; i--)
	{
		a = value % 10;
		value /= 10;
		//DrawFormatString(x, y + (i * 20), 0x00ff00, "%d", j);
		DrawGraph(x + (i * 20), y, numbers_image[a], TRUE);
	}
}