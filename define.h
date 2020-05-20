#pragma once

//グローバルカウント
extern int gameCount;

//当たり判定用半径定義
#define PLAYER_COLLISION 4
#define ENEMY_COLLISION 14

#define PSHOT_COLLISION 4
#define ESHOT0_COLLISION 6
#define ESHOT1_COLLISION 4
#define ESHOT2_COLLISION 3

#define BOSS_COLLISION 60


//プレイヤーの初期位置
#define PLAYER_INITX 310
#define PLAYER_INITY 550

//プレイヤーの移動スピード
#define PLAYER_SPEED 4

//プレイヤーの弾の数
#define PSHOT_NUM 200
//弾スピード

#define PSHOT_SPEED 8

// エネミーの数
#define ENEMY_NUM 15

// エネミーの弾の数
#define ESHOT_NUM 100

// エネミーのエフェクトの数
#define EFFECT_EDEADNUM 20

// プレイヤーのエフェクトの数
#define EFFECT_PDEADNUM 80

// スコアの文字描画の基準となるX座標
#define SCORE_X 660

//アイテムの当たり判定用半径
#define ITEM_COLLISION 10
//アイテムの総数
#define ITEM_NUM 30

// ボスの弾の数
#define BOSS_SHOTNUM 200
// ボスの揺れ幅
#define BOSS_SHAKE 20
// ボスのHP
#define BOSS_HP 500

struct ENEMYDATA
{
	int type;		// エネミーの種類
	int shotType;	// 弾の種類
	int movePattern;// 移動パターン
	int shotPattern;// 発射パターン
	int inTime;		//出現時間
	int stopTime;	// 停止時間
	int shotTime;	// 弾発射時間
	int outTime;	// 帰還時間	
	int x;			// x座標
	int y;			// y座標
	int speed;		// スピード
	int hp;			// HP
	int item;		// アイテム
};

struct ESHOT
{
	bool flag;	 // 弾が発射中かどうか
	double x;
	double y;
	double rad;	 // 角度(ラジアン)
	int graph;
	int width, height;
	int pattern; // ショットパターン
	int speed;
	int type;
};
