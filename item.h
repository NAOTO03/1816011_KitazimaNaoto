#pragma once

class ITEM
{
private:
	// �O���t�B�b�N�n���h��
	static int graph[2];
	// �ǂ����̃A�C�e�����������ϐ�
	int type;
	// ���W
	double x, y;
	double prevY;
	// �A�C�e�����������n�߂�t���O
	bool fallFlag;
	// �o�������ǂ����̃t���O
	bool flag;
private:
	void Updata();
	void Draw();
public:
	ITEM();
	void SetFlag(double x, double y, int type);
	bool GetFlag();
	void Delete();
	void GetPosition(double *x, double *y);
	int GetType();
	void All();
};

