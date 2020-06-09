// ゲームの処理

#pragma once

#include "define.h"
#include "boss.h"

// プロトタイプ宣言
class BACK;
class PLAYER;
class ENEMY;
class EFFECT_EDEAD;
class EFFECT_PDEAD;
class SCORE;
class ITEM;


class Game
{
public:
	void Initialize();
	void Finalize();
	void GetPlayerPosition(double *x, double *y);
	void GetEnemyPosiition(int index, double *x, double *y);
	void GetBossPosition(double *x, double *y);
	static Game& GetInstance()
	{
		static Game game;
		return game;
	}
	void All();
private:
	bool CircleCollision(double c1, double c2, double cx1, double cx2, double cy1, double cy2);
	void CollisionAll();
	void EnemyCollisionAll();
	void BossCollisionAll();
	void SoundAll();
	void BossBgm(bool flag);
	void EnemyDeadEffect(double x, double y, int index);
	bool SaveData();
	bool LoadData();
private:
	// 背景クラス
	BACK *back;
	// プレイヤークラス
	PLAYER *player;
	// エネミークラス
	ENEMY *enemy[ENEMY_NUM];
	//敵消滅エフェクトクラス
	EFFECT_EDEAD *effectEData[EFFECT_EDEADNUM];
	// プレイヤー消滅エフェクトクラス
	EFFECT_PDEAD *effectPData[EFFECT_PDEADNUM];
	// スコアクラス
	SCORE *score;
	//アイテムクラス
	ITEM *item[ITEM_NUM];
	// ボスクラス
	BOSS boss;

	// サウンドハンドル
	int pShotSound;
	int eShotSound;
	int continuationShotSound;
	int bShotSound;
	int pDeadSound;
	int eDeadSound;
	int itemSound;

	// サウンドを鳴らすかどうかのフラグ
	bool pShotFlag;
	bool eShotFlag;
	bool continuationShotFlag;
	bool bShotFlag;
	bool pDeadFlag;
	bool eDeadFlag;
	bool itemFlag;

	// スコア用のフラグ
	bool scoreFlag;
	// ボスを倒したかどうかのフラグ
	bool defeatFlag;
	// ボスを倒してからのカウント
	int defeatCount;
	// スコア保存用
	FILE_DATA fileData;
};

