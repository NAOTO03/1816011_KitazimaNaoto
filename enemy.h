// ------ �G�l�~�[ ------

#pragma once

#include "define.h"

// �G�l�~�[�\����
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

	// �o���@��~�@�A�ҁ@���˃^�C�~���O
	int inTime, stopTime, outTime, shotTime;

	int type;	     // �G�l�~�[�̎��
	int shotType;	 // �e�̎��
	int movePattern; // �ړ��p�^�[��
	int shotPattern; // �V���b�g�p�^�[��
	int count;		 // �G�l�~�[���o�����Ă���̃J�E���g
	int item;		 // �A�C�e��
	int hp;		     // HP
	int shotNum;	 // ���˂�������
	double rad;		 // ���˒���̃��W�A��
	bool deadFlag;	 // �G�l�~�[���Ńt���O
	bool endFlag;	 // �G�l�~�[�N���X���Ńt���O

	// �e�\����
	ESHOT shot[ESHOT_NUM];
	// �V���b�g�����Ă�悤�ɂȂ������̃t���O
	bool shotFlag;
	// �V���b�g�����Ă�悤�ɂȂ��Ă���̃J�E���g
	int shotCount;
	// �V���b�g�����������ǂ����������t���O
	bool shotSound; 
};


