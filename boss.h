#pragma once

#include "define.h"

class BOSS
{
private:
	// ���W
	double x, y;
	double prevX, prevY;
	int width, height;
	// �O���t�B�b�N�n���h��
	int graph;
	int blackShot[3];
	int whiteShot[3];
	// ���݂̈ړ��p�^�[��
	int movePattern;
	// ���݂̃V���b�g�p�^�[��
	int shotPattern;
	// �O��̈ړ��p�^�[��
	int prevMovePattern;
	// �O��̃V���b�g�p�^�[��
	int prevShotPattern;

	//�e�\����
	ESHOT shot[BOSS_SHOTNUM];

	//���v�p�x�Ƒ�����
	int angle, raise;

	//���ړ����̑�����
	int raise2;
	int waitCount;
	bool wait;

	//���̈ړ��ꏊ�܂ł̋���
	double moveX, moveY;
	int state;

	// �J�E���g
	int shotCount;
	int tempShotCount;

	//HP
	int hp;
	//�O��HP
	int prevHp;

	//�_���[�W�𕉂������ǂ����̃t���O
	bool damageFlag;
	// �_���[�W�𕉂�Ȃ��t���O
	bool noDamageFlag;
	//�����Ă邩�ǂ����̃t���O
	bool flag;
	bool bossFlag;
	// �e�𔭎˂��邽�߂̃t���O
	bool shotFlag;
	// �V���b�g�����������ǂ����������t���O
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

