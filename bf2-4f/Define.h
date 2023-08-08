#pragma once

//他の所でも使いそうな情報はここに格納

#define SCREEN_WIDTH 640			//画面の横幅
#define SCREEN_HEIGHT 480			//画面の高さ

#define MAX_STAGE 5					//最大ステージ数

#define PLAYER_ENEMY_HEIGHT 50		//プレイヤーと敵の高さ
#define PLAYER_ENEMY_WIDTH  32		//プレイヤーと敵の横幅

#define BALLOON_HEIGHT  25			//プレイヤーと敵の風船の高さ

#define PLAYER_RESPAWN_POS_X 100	//プレイヤーのリスポーン位置(X)
#define PLAYER_RESPAWN_POS_Y 370	//プレイヤーのリスポーン位置(Y)

#define MAX_SPEED 250				//最高速度と最低速度の差を調整する用
#define MAX_SPEED_LAND 100			//最高速度と最低速度の差を調整する用（地面）
#define MAX_JUMP 10					//最大連打数
#define JUMP_INTERVAL 10			//ジャンプボタン連打間隔
#define FALL_SPPED 0.014f			//最高落下速度
#define MOVE_SPPED 0.009f			//最高移動速度
#define RISE_SPPED 0.027f			//最高上昇速度
#define LAND_SPEED 0.025f			//最高移動速度（地面）
	
#define SEA_SURFACE 445				//海面
#define UNDER_WATER 470				//海のなか

#define SOAPBUBBLE_GETPOINT 500		//シャボン玉の点数