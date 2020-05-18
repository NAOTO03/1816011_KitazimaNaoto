#pragma once

#include "define.h"

class BOSS
{
private:
	// 座標
	double x, y;
	double prevX, prevY;
	// グラフィックハンドル
	int bGraph[3];
	int shotGraph[3];
	// 現在の移動パターン
	int movePattern;
	// 現在のショットパターン
	int shotPattern;

	//弾構造体
	ESHOT shot[BOSS_SHOTNUM];

	//合計角度と増加量
	int angle, raise;

	//横移動時の増加量
	int raise2;
	int waitCount;
	bool wait;

	//次の移動場所までの距離
	double moveX, moveY;
	int state;

	// カウント
	int shotCount;

	//ダメージを負ったかどうかのフラグ
	bool damageFlag;

	//生きてるかどうかのフラグ
	bool flag;

	// 弾を発射するためのフラグ
	bool shotFlag;
	// ショット音が鳴ったかどうかを示すフラグ
	bool soundShot;
private:
	void Updata();
	void Appear();
	void MovePattern1();
	void MovePattern2();
	void MovePattern3();
	void MoveInit(double bx, double by, int state);
	void Shot();
	int ShotSearch();
	void Draw();
public:
	BOSS();
	void SetDamageFlag();
	void SetFlag(bool f);
	bool GetFlag();
	void All();
};

