// �Q�[���̏���

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
	// �w�i�N���X
	BACK *back;
	// �v���C���[�N���X
	PLAYER *player;
	// �G�l�~�[�N���X
	ENEMY *enemy[ENEMY_NUM];
	//�G���ŃG�t�F�N�g�N���X
	EFFECT_EDEAD *effectEData[EFFECT_EDEADNUM];
	// �X�R�A�N���X
	SCORE *score;
	//�A�C�e���N���X
	ITEM *item[ITEM_NUM];
	// �{�X�N���X
	BOSS boss;

	// �T�E���h�n���h��
	int pShotSound;
	int eShotSound;
	int bShotSound;
	int pDeadSound;
	int eDeadSound;

	// �T�E���h��炷���ǂ����̃t���O
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

