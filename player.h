// ------ プレイヤー ------

#pragma once

#include "define.h"
#include "effectPData.h"

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

// プレイヤー構造体
class PLAYER
{
public:
	PLAYER();
	void GetPosition(double *x, double *y);
	bool GetShotPosition(int index, double *x, double *y);
	bool GetShotSound();
	void SetShotFlag(int index, bool flag);
	void SetDamageFlag();
	bool GetDamageFlag();
	int GetPlayerColor();
	int GetLife();
	void SetPower(int p);
	int GetPower();
	void All();
private:
	void Update();
	void Shot();
	void Draw();
private:
	double playerX, playerY;	//x座標,y座標
	int width, height;	//画像幅
	int graph[2];	//グラフィックハンドル格納用配列
	int rGraph[2];
	double rad;		//回転角度
	int count;
	float move;		// 移動係数	
	int life;		// プレイヤーのライフ
	int power;		// プレイヤーのパワー
	bool damageFlag;
	bool moveFlag;
	bool endFlag;
	int damageCount;// ダメージ中のカウント
	PSHOT shot[PSHOT_NUM];
	int shotCount;
	bool shotSound; // ショット音が鳴ったかどうかを示すフラグ
	PLAYER_COLOR color;
	//プレイヤー消滅エフェクトクラス
	EFFECT_PDEAD effectPDead;
};
