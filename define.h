#pragma once

//グローバルカウント
extern int gameCount;

//当たり判定用半径定義
#define PLAYER_COLLISION 10
#define ENEMY_COLLISION 16

#define PSHOT_COLLISION 3
#define ESHOT0_COLLISION 6
#define ESHOT1_COLLISION 4
#define ESHOT2_COLLISION 3


//プレイヤーの初期位置
#define PLAYER_INITX 305
#define PLAYER_INITY 430

//プレイヤーの歩くスピード
#define PLAYER_SPEED 4

//プレイヤーの弾の数
#define PSHOT_NUM 50
//弾スピード

#define PSHOT_SPEED 8

// エネミーの数
#define ENEMY_NUM 11

// エネミーの弾の数
#define ESHOT_NUM 100

// エネミーのエフェクトの数
#define EFFECT_EDEADNUM 20

// プレイヤーのエフェクトの数
#define EFFECT_PDEADNUM 60

// スコアの文字描画の基準となるX座標
#define SCORE_X 660

//アイテムの当たり判定用半径
#define ITEM_COLLISION 10
//アイテムの総数
#define ITEM_NUM 30
