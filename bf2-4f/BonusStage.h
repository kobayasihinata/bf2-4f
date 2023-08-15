#pragma once
#include "AbstractScene.h"
#include "GameMain.h"
#include "Player.h"
#include "UI.h"
#include "BackGroundStar.h"
#include "StageObject.h"
#include"Balloon.h"

#define ENEMY_NAMBER 6
#define SECOND_TO_FRAME(sec) ((sec)*FRAMERATE)
#define MAX_FLOOR 7+3
#define MAX_STAR 40     //�w�i�̐��̍ő吔


class BonusStage :
    public AbstractScene
{
private:

    Player* player;
    StageObject* stageobject;
    UI* ui;
    Balloon* balloon[20];

    int spawn_int;              //�t���[����
    int get_balloon_count;      //���D���擾�������i�[
    int spawn_balloon_count;    //���D�𐶐��������i�[

    bool pause;             //�ꎞ��~
    bool result_flg;        //���ʂ�\������
    bool once;              //��񂾂��s���p
    int result_time;    //���o�p

    int score;  //���̃X�e�[�W�Ŋl�������X�R�A
    int wait_time;  //���Z��̑ҋ@����
    int player_image[31];   //�v���C���[�摜
    int balloon_image[4];   //�摜�p�ϐ�
    //BGM
   // int Trip_BGM;	


public:

    //�R���X�g���N�^
    BonusStage();

    //�f�X�g���N�^
    ~BonusStage() final;

    //�`��ȊO�̍X�V�����s
    AbstractScene* Update() override;

    //�`��Ɋւ��邱�Ƃ�����
    void Draw() const override;

    //���D���X�|�[��������
    void SpawnBalloon();

    //���D���S���擾�ς݂������͉�ʊO�܂ŏ㏸�ς݂����ׂ�
    bool EndCheck();
};