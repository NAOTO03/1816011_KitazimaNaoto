// ゲームの処理

#pragma once

#include "DxLib.h"
#include <time.h>
#include "back.h"
#include "player.h"
#include "enemy.h"
#include "effectEData.h"
#include "score.h"
#include "item.h"
#include "boss.h"


class Game
{
	// 背景クラス
	BACK *back;
	// プレイヤークラス
	PLAYER *player;
	// エネミークラス
	ENEMY *enemy[ENEMY_NUM];
	//敵消滅エフェクトクラス
	EFFECT_EDEAD *effectEData[EFFECT_EDEADNUM];
	// スコアクラス
	SCORE *score;
	//アイテムクラス
	ITEM *item[ITEM_NUM];
	// ボスクラス
	BOSS boss;

	// サウンドハンドル
	int pShotSound;
	int eShotSound;
	int bShotSound;
	int pDeadSound;
	int eDeadSound;

	// サウンドを鳴らすかどうかのフラグ
	bool pShotFlag;
	bool eShotFlag;
	bool bShotFlag;
	bool pDeadFlag;
	bool eDeadFlag;

public:
	void All();
	void GetPlayerPosition(double *x, double *y);
	void GetEnemyPosiition(int index, double *x, double *y);
	static Game& GetInstance()
	{
		static Game game;
		return game;
	}
private:
	Game();
	~Game();
	bool CircleCollision(double c1, double c2, double cx1, double cx2, double cy1, double cy2);
	void CollisionAll();
	void EnemyCollisionAll();
	void BossCollisionAll();
	void SoundAll();
	void EnemyDeadEffect(double x, double y, int index);
};

