#pragma once

//extern宣言してkey配列にどこからでもアクセスできるようにする
extern char key[256];

//グローバルカウント
extern int gameCount;

// ---------- 当たり判定用半径定義 ----------

constexpr auto PLAYER_COLLISION = 4;  // プレイヤーの当たり判定用
constexpr auto ENEMY_COLLISION = 12;  // エネミーの当たり判定用

constexpr auto PSHOT_COLLISION = 4;	  // プレイヤーの弾
constexpr auto ESHOT0_COLLISION = 6;  // エネミーの弾(丸い弾)
constexpr auto ESHOT1_COLLISION = 4;  // 縦長の弾
constexpr auto ESHOT2_COLLISION = 4;  // ひし形の小さな弾

constexpr auto BOSS_COLLISION = 60;   // ボスの当たり判定用

constexpr auto ITEM_COLLISION = 10;   // アイテムの当たり判定用半径


// ---------- プレイヤー関連 ----------

//プレイヤーの初期位置
constexpr auto PLAYER_INITX = 310;
constexpr auto PLAYER_INITY = 550;
//プレイヤーの移動スピード
constexpr auto PLAYER_SPEED = 3;
//プレイヤーの弾の数
constexpr auto PSHOT_NUM = 200;
//弾スピード
constexpr auto PSHOT_SPEED = 8;
// プレイヤーのエフェクトの数
constexpr auto EFFECT_PDEADNUM = 80;

// ---------- エネミー関連 ----------

// エネミーの数
constexpr auto ENEMY_NUM = 54;
// エネミーの弾の数
constexpr auto ESHOT_NUM = 300;
// エネミーのエフェクトの数
constexpr auto EFFECT_EDEADNUM = 50;

// ---------- ボス関連 ----------

// ボスの弾の数
constexpr auto BOSS_SHOTNUM = 300;
// ボスの揺れ幅
constexpr auto BOSS_SHAKE = 20;
// ボスのHP
constexpr auto BOSS_HP = 1500;

// ---------- 背景関連 ----------

// スコアの文字描画の基準となるX座標
constexpr auto SCORE_X = 660;

//アイテムの総数
constexpr auto ITEM_NUM = 30;



// ---------- プレイヤー関連 ----------

struct PSHOT
{
	bool flag;         //弾が発射中かどうか
	double x;
	double y;
	int graph[2];
	int width, height; //画像の幅と高さ
	double rad;		   // 角度
};

enum PLAYER_COLOR
{
	BLACK,
	WHITE
};

// ---------- エネミー関連 ----------

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
	int color;
};

// ---------- 背景関連 ----------

//struct FILE_DATA
//{
//	int score;
//	int highScore;
//};
