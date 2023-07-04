#include"DxLib.h"
#include"SceneManager.h"
#include"PadInput.h"

#include"Title.h"
#include"Stage.h"


#define FRAMERATE 60.0 //�t���[�����[�g

#define SCREEN_WIDTH 640	//��ʃT�C�Y
#define SCREEN_HEIGHT 480

/***********************************************
 * �v���O�����̊J�n
 ***********************************************/
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	SetMainWindowText("C++BreakOut");

	ChangeWindowMode(TRUE);		// �E�B���h�E���[�h�ŋN��

	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32);	//��ʃT�C�Y�̐ݒ�

	if (DxLib_Init() == -1) return -1;	// DX���C�u�����̏���������

	SetDrawScreen(DX_SCREEN_BACK);	// �`����ʂ𗠂ɂ���

	SceneManager* sceneMng;

	try
	{
		sceneMng = new SceneManager((AbstractScene*)new Title());
	}
	catch (const char* err)
	{
		FILE* fp = NULL;

		DATEDATA data;

		GetDateTime(&data);
		//�t�@�C���I�[�v��
		fopen_s(&fp, "ErrLog.txt", "a");
		//�G���[�f�[�^�̏�������
		fprintf_s(fp, "%02d�N %02d�� %02d�� %02d�� %02d�� %02d�b : %s������܂���B\n", data.Year, data.Mon, data.Day, data.Hour, data.Min, data.Sec, err);

		return 0;
	}

	// �Q�[�����[�v
	while ((ProcessMessage() == 0) && (sceneMng->Update() != nullptr)) {

		ClearDrawScreen();		// ��ʂ̏�����

		sceneMng->Draw();

		//�����I��
		if (CheckHitKey(KEY_INPUT_ESCAPE))
		{
			break;
		}

		ScreenFlip();			// ����ʂ̓��e��\��ʂɔ��f
	}
	return 0;
}