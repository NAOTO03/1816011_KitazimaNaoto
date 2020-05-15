#pragma once

#include "define.h"

class BOSS
{
private:
	// ���W
	double x, y;
	double prevX, prevY;
	// �O���t�B�b�N�n���h��
	int bGraph[3];
	int shotGraph[3];
	// ���݂̈ړ��p�^�[��
	int movePattern;
	// ���݂̃V���b�g�p�^�[��
	int shotPattern;

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

	//�_���[�W�𕉂������ǂ����̃t���O
	bool damageFlag;

	//�����Ă邩�ǂ����̃t���O
	bool flag;
private:
	void Updata();
	void Appear();
	void MovePattern1();
	void MovePattern2();
	void MovePattern3();
	void MoveInit(double bx, double by, int state);
	void Draw();
public:
	BOSS();
	void SetDamageFlag();
	void SetFlag(bool f);
	bool GetFlag();
	void All();
};

