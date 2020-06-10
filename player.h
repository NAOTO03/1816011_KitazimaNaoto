// ------ プレイヤー ------

#pragma once

#include "define.h"
#include "effectPData.h"


// プレイヤー構造体
class PLAYER
{
public:
	PLAYER();
	// プレイヤーの座標を返す
	void GetPosition(double *x, double *y);
	bool GetShotPosition(int index, double *x, double *y);
	// 当たった弾を元に戻す
	void SetShotFlag(int index, bool flag);
	// ショットサウンドを鳴らすタイミングを返す
	bool GetShotSound();
	// 色の変更音を鳴らすタイミングを返す
	bool GetChangeColor();
	// ダメージを受けたときにライフを減らす
	void SetDamageFlag();
	// ダメージを受けた際の無敵時間用
	bool GetDamageFlag();
	// プレイヤーの色を返す
	int GetPlayerColor();
	// ----- スコア関連 -----
	int GetLife();
	void SetPower(int p);
	int GetPower();
	void All();
private:
	void Update();
	void Shot();
	void Draw();
private:
	double playerX, playerY; //x座標,y座標
	int width, height;	     //画像幅
	int graph[2];	         //グラフィックハンドル格納用配列
	int rGraph[2];
	PSHOT shot[PSHOT_NUM];
	double rad;		         //回転角度
	int count;
	float move;		         // 移動係数	
	int life;		         // プレイヤーのライフ
	int power;			     // プレイヤーのパワー
	bool damageFlag;
	bool moveFlag;
	bool endFlag;
	int damageCount;         // ダメージ中のカウント
	int shotCount;
	// ショット音が鳴ったかどうかを示すフラグ
	bool shotSound;
	//// 色の変更音をなったかどうかを示すフラグ
	bool changeColor;
	// プレイヤーの色
	PLAYER_COLOR color;
	//プレイヤー消滅エフェクトクラス
	EFFECT_PDEAD effectPDead;
};
