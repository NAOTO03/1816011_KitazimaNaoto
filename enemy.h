// ------ �G�l�~�[ ------

#pragma once

// �G�l�~�[�\����
class ENEMY
{
public:
	ENEMY(int type, int shotType, int movePattern, int shotPattern, int inTime, int stopTime, int shotTime, int outTime,
		  int x, int y, int speed, int hp, int item);	
	// �G�l�~�[���g�ƒe�̍��W��Ԃ�
	void GetPosition(double *x, double *y);
	bool GetShotPosition(int index, double *x, double *y);
	// ���������e�����ɖ߂�
	void SetShotFlag(int index, bool flag);
	// �G�l�~�[���g�ƒe�̐F��Ԃ�
	int GetEnemyType();
	int  GetShotType();
	// �V���b�g�T�E���h��炷�^�C�~���O��Ԃ�
	bool GetShotSound();
	bool GetContinuationShotSound();
	// �ǂ̎�ނ̃A�C�e����������
	int GetItem();
	// ���񂾂��ǂ����̔���
	void SetDeadFlag();
	bool GetDeadFlag();
	// ���݂�HP��Ԃ��EHP��ύX����
	int GetHp();
	void SetHp(int eHp);
	bool All();	
private:
	void Update();
	void Shot();
	void Draw();
	// ��ʊO�ɏo�����ǂ����̔���
	bool OutCheck();
	bool ShotOutCheck(int i);
	// �G�l�~�[�̓����̎��
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
	bool continuationShotSound;	// �e��A���Ŕ��˂���V���b�g�p�^�[���p�̃t���O
};


