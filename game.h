// �Q�[���̏���

#pragma once

#include "define.h"
#include "boss.h"

// �v���g�^�C�v�錾
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
	// �w�i�N���X
	BACK *back;
	// �v���C���[�N���X
	PLAYER *player;
	// �G�l�~�[�N���X
	ENEMY *enemy[ENEMY_NUM];
	//�G���ŃG�t�F�N�g�N���X
	EFFECT_EDEAD *effectEData[EFFECT_EDEADNUM];
	// �v���C���[���ŃG�t�F�N�g�N���X
	EFFECT_PDEAD *effectPData[EFFECT_PDEADNUM];
	// �X�R�A�N���X
	SCORE *score;
	//�A�C�e���N���X
	ITEM *item[ITEM_NUM];
	// �{�X�N���X
	BOSS boss;

	// �T�E���h�n���h��
	int pShotSound;
	int eShotSound;
	int continuationShotSound;
	int bShotSound;
	int pDeadSound;
	int eDeadSound;
	int itemSound;

	// �T�E���h��炷���ǂ����̃t���O
	bool pShotFlag;
	bool eShotFlag;
	bool continuationShotFlag;
	bool bShotFlag;
	bool pDeadFlag;
	bool eDeadFlag;
	bool itemFlag;

	// �X�R�A�p�̃t���O
	bool scoreFlag;
	// �{�X��|�������ǂ����̃t���O
	bool defeatFlag;
	// �{�X��|���Ă���̃J�E���g
	int defeatCount;
	// �X�R�A�ۑ��p
	FILE_DATA fileData;
};

