#pragma once

#include "define.h"

class BOSS
{
private:
	// 座標
	double x, y;
	double prevX, prevY;
	int width, height;
	// グラフィックハンドル
	int graph;
	int blackShot[3];
	int whiteShot[3];
	// 現在の移動パターン
	int movePattern;
	// 現在のショットパターン
	int shotPattern;
	// 前回の移動パターン
	int prevMovePattern;
	// 前回のショットパターン
	int prevShotPattern;

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
	int tempShotCount;

	//HP
	int hp;
	//前回HP
	int prevHp;

	//ダメージを負ったかどうかのフラグ
	bool damageFlag;
	// ダメージを負わないフラグ
	bool noDamageFlag;
	//生きてるかどうかのフラグ
	bool flag;
	bool bossFlag;
	// 弾を発射するためのフラグ
	bool shotFlag;
	// ショット音が鳴ったかどうかを示すフラグ
	bool shotSound;
private:
	void Updata();
	void Appear();
	void MovePattern1();
	void MovePattern2();
	void MovePattern3();
	void MoveInit(double bx, double by, int state);
	void Shot();
	int ShotSearch();
	bool ShotOutCheck(int i);
	void MoveToDefault();
	void SetMovePattern(int pattern);
	void SetShotPattern(int pattern);
	void Draw();
public:
	BOSS();
	void SetDamageSetting();
	void SetFlag(bool bFlag);
	void SetBossFlag(bool flag);
	bool GetFlag();
	bool GetBossFlag();
	bool GetShotSound();
	void GetPosition(double *x, double *y);
	bool GetShotPosition(int index, double *x, double *y, int *type);
	void SetShotFlag(int index, bool flag);
	int SetHp(int damage);
	int GetPrevHp();
	bool GetNoDamageFlag();
	int GetShotColor(int index);
	void All();
};

