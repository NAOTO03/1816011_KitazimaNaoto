#pragma once

class ITEM
{
public:
	ITEM();
	void SetFlag(double x, double y, int type);
	bool GetFlag();
	void Delete();
	void GetPosition(double *x, double *y);
	int GetType();
	void GetSize(int *width, int *height);
	void All();
private:
	void Updata();
	void Draw();
private:
	// �O���t�B�b�N�n���h��
	static int graph[2];
	// �ǂ����̃A�C�e�����������ϐ�
	int type;
	// ���W
	double x, y;
	double prevY;
	//�摜��
	int width, height;
	// �A�C�e�����������n�߂�t���O
	bool fallFlag;
	// �o�������ǂ����̃t���O
	bool flag;
};

