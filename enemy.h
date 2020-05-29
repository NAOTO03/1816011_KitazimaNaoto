// ------ エネミー ------

#pragma once

#include "define.h"

// エネミー構造体
class ENEMY
{
public:
	ENEMY(int type, int shotType, int movePattern, int shotPattern, int inTime, int stopTime, int shotTime, int outTime,
		  int x, int y, int speed, int hp, int item);	
	void GetPosition(double *x, double *y);
	bool GetShotPosition(int index, double *x, double *y);
	void SetShotFlag(int index, bool flag);
	int GetEnemyType();
	int  GetShotType();
	void SetDeadFlag();
	bool GetDeadFlag();
	bool GetShotSound();
	int GetItem();
	int GetHp();
	void SetHp(int eHp);
	bool All();
	
private:
	void Update();
	void Shot();
	void Draw();
	bool OutCheck();
	bool ShotOutCheck(int i);
private:
	double enemyX, enemyY;
	int width, height;
	int graph;
	int shotGraph;

	// 出現　停止　帰還　発射タイミング
	int inTime, stopTime, outTime, shotTime;

	int type;	     // エネミーの種類
	int shotType;	 // 弾の種類
	int movePattern; // 移動パターン
	int shotPattern; // ショットパターン
	int count;		 // エネミーが出現してからのカウント
	int item;		 // アイテム
	int hp;		     // HP
	int shotNum;	 // 発射した球数
	double rad;		 // 発射直後のラジアン
	bool deadFlag;	 // エネミー消滅フラグ
	bool endFlag;	 // エネミークラス消滅フラグ

	// 弾構造体
	ESHOT shot[ESHOT_NUM];
	// ショットが撃てるようになったかのフラグ
	bool shotFlag;
	// ショットが撃てるようになってからのカウント
	int shotCount;
	// ショット音が鳴ったかどうかを示すフラグ
	bool shotSound; 
};


