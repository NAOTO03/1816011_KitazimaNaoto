// ------ エネミー ------

#pragma once

// エネミー構造体
class ENEMY
{
public:
	ENEMY(int type, int shotType, int movePattern, int shotPattern, int inTime, int stopTime, int shotTime, int outTime,
		  int x, int y, int speed, int hp, int item);	
	// エネミー自身と弾の座標を返す
	void GetPosition(double *x, double *y);
	bool GetShotPosition(int index, double *x, double *y);
	// 当たった弾を元に戻す
	void SetShotFlag(int index, bool flag);
	// エネミー自身と弾の色を返す
	int GetEnemyType();
	int  GetShotType();
	// ショットサウンドを鳴らすタイミングを返す
	bool GetShotSound();
	bool GetContinuationShotSound();
	// どの種類のアイテムかを示す
	int GetItem();
	// 死んだかどうかの判定
	void SetDeadFlag();
	bool GetDeadFlag();
	// 現在のHPを返す・HPを変更する
	int GetHp();
	void SetHp(int eHp);
	bool All();	
private:
	void Update();
	void Shot();
	void Draw();
	// 画面外に出たかどうかの判定
	bool OutCheck();
	bool ShotOutCheck(int i);
	// エネミーの動きの種類
	void EnemyPattern0();
	void EnemyPattern1();
	void EnemyPattern2();
	void EnemyPattern3();
	void EnemyPattern4();
	void EnemyPattern5();
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
	bool continuationShotSound;	// 弾を連続で発射するショットパターン用のフラグ
};


