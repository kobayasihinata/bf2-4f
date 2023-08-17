#pragma once
#include "AbstractScene.h"
#include "Player.h"
#include "Enemy.h"
#include "Enemy_AI.h"
#include"StageObject.h"
#include"Fish.h"
#include"SoapBubble.h"
#include"Thunder.h"
#include"UI.h"
#include"SoundManager.h"
#include"BackGroundStar.h"

#define ENEMY_NAMBER 6
#define SECOND_TO_FRAME(sec) ((sec)*FRAMERATE)
#define MAX_FLOOR 7+3
#define MAX_STAR 40     //�w�i�̐��̍ő吔

enum State {
    Normal,
    Clear,
    Over,
};

class GameMain :
    public AbstractScene
{
private:

    Player* player;
    Enemy* enemy[ENEMY_NAMBER];
    ENEMY_AI* enemy_ai[ENEMY_NAMBER];
    StageObject* stageobject[MAX_FLOOR];
    Fish* fish;
    Thunder* thunder[2];
    SoapBubble* soapbubble[6];
    UI* ui;
    SoundManager* soundmanager;
    BackGroundStar* backgroundstar[MAX_STAR];

    int seaImage;

    bool para;
    bool E_jump;

    bool Pouse;
    int max_enemy;      //�G�̐�
    int P_x, P_y;       //�v���C���[���W
    int AI_Pattern[ENEMY_NAMBER];     //Ai�p�^�[��
    bool Avoidance[ENEMY_NAMBER]; // ����t���O
    bool damage_once;   //�d�Ȃ��Ă��鎞��񂾂��_���[�W��^����
    int main_state;
    bool clear_flg;     //���̃X�e�[�W�֑J�ڂ�������𒲂ׂ�p
    int clear_wait;     //���̃X�e�[�W�֑J�ڂ���O�̑҂�����
    int now_floor_max;  //���݂̏��̐�
    int GameOver_Img;   //�Q�[���I�[�o�[�摜  
    int phase_image;    //�X�e�[�W���\���摜
    int GameOver_BGM;   //�Q�[���I�[�o�[BGM
    int WaitTimer;
    int phase_disptime; //�X�e�[�W���摜�\�����ԑ���p
    int phase_disp;     //�X�e�[�W���摜�\���_�ŗp

    //BGM
    int Continue_BGM;			//�R���e�j���[BGM
    int StageClear_BGM;			//�X�e�[�W�N���ABGM

    //SE
    int EnemuyMove_SE;          //�g������SE
    int BaloonBurst_SE;			//�o���[���j��SE
    int Eatable_SE;
    int StageClear_SE;
    int para_SE;
    int EnemyMove_SE;
    

    

public:

    //�R���X�g���N�^
    GameMain(int beforescene);

    //�f�X�g���N�^
    ~GameMain() final;

    //�`��ȊO�̍X�V�����s
    AbstractScene* Update() override;

    //�`��Ɋւ��邱�Ƃ�����
    void Draw() const override;

    //�G�ƃv���C���[���ڐG�������̃_���[�W����
    void Damage(int i);

    //���̃X�e�[�W��
    void NextStage();

    //�G�ƒn�ʂ𐶐�����
    void CreateStage(int stage);

    //�_���擾
    static int GetScore();

    //�G�̃X�|�[���ʒu���w�肵�����̏�ɐݒ�
    Location SpawnPosSet(StageObject* floor);

    //�f�[�^���Z�b�g
    static void DataReset();

    //�X�R�A���Z
    static void AddScore(int point);

};

