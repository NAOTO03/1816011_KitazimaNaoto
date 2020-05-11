// ------ プレイヤー ------

#pragma once

#include "define.h"
#include "effectPData.h"

struct PSHOT {
	bool flag;//弾が発射中かどうか
	double x;
	double y; 
	int graph[3];
	int width, height; //画像の幅と高さ
};

enum COLOR {
	RED,
	BLUE,
	GREEN,
	COLOR_MAX
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
	void All();
private:
	void Update();
	void Shot();
	void Draw();
private:
	double playerX, playerY;	//x座標,y座標
	int width, height;	//画像幅
	int graph[3];	//グラフィックハンドル格納用配列
	float move;		// 移動係数	
	int life;		// プレイヤーのライフ
	bool damageFlag;
	bool endFlag;
	int damageCount;// ダメージ中のカウント
	PSHOT shot[PSHOT_NUM];
	int shotCount;
	bool soundShot; // ショット音が鳴ったかどうかを示すフラグ
	COLOR color;
	//プレイヤー消滅エフェクトクラス
	EFFECT_PDEAD effectPDead;
};
