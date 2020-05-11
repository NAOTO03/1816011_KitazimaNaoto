// ------ �v���C���[ ------

#pragma once

#include "define.h"
#include "effectPData.h"

struct PSHOT {
	bool flag;//�e�����˒����ǂ���
	double x;
	double y; 
	int graph[3];
	int width, height; //�摜�̕��ƍ���
};

enum COLOR {
	RED,
	BLUE,
	GREEN,
	COLOR_MAX
};

// �v���C���[�\����
class PLAYER
{
public:
	PLAYER();
	void GetPosition(double *x, double *y);
	bool GetShotPosition(int index, double *x, double *y);
	bool GetShotSound();
	void SetShotFlag(int index, bool flag);
	void SetDamageFlag();
	bool GetDamageFlag();
	int GetPlayerColor();
	void All();
private:
	void Update();
	void Shot();
	void Draw();
private:
	double playerX, playerY;	//x���W,y���W
	int width, height;	//�摜��
	int graph[3];	//�O���t�B�b�N�n���h���i�[�p�z��
	float move;		// �ړ��W��	
	int life;		// �v���C���[�̃��C�t
	bool damageFlag;
	bool endFlag;
	int damageCount;// �_���[�W���̃J�E���g
	PSHOT shot[PSHOT_NUM];
	int shotCount;
	bool soundShot; // �V���b�g�����������ǂ����������t���O
	COLOR color;
	//�v���C���[���ŃG�t�F�N�g�N���X
	EFFECT_PDEAD effectPDead;
};
