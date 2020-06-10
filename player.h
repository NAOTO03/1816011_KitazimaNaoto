// ------ �v���C���[ ------

#pragma once

#include "define.h"
#include "effectPData.h"


// �v���C���[�\����
class PLAYER
{
public:
	PLAYER();
	// �v���C���[�̍��W��Ԃ�
	void GetPosition(double *x, double *y);
	bool GetShotPosition(int index, double *x, double *y);
	// ���������e�����ɖ߂�
	void SetShotFlag(int index, bool flag);
	// �V���b�g�T�E���h��炷�^�C�~���O��Ԃ�
	bool GetShotSound();
	// �F�̕ύX����炷�^�C�~���O��Ԃ�
	bool GetChangeColor();
	// �_���[�W���󂯂��Ƃ��Ƀ��C�t�����炷
	void SetDamageFlag();
	// �_���[�W���󂯂��ۂ̖��G���ԗp
	bool GetDamageFlag();
	// �v���C���[�̐F��Ԃ�
	int GetPlayerColor();
	// ----- �X�R�A�֘A -----
	int GetLife();
	void SetPower(int p);
	int GetPower();
	void All();
private:
	void Update();
	void Shot();
	void Draw();
private:
	double playerX, playerY; //x���W,y���W
	int width, height;	     //�摜��
	int graph[2];	         //�O���t�B�b�N�n���h���i�[�p�z��
	int rGraph[2];
	PSHOT shot[PSHOT_NUM];
	double rad;		         //��]�p�x
	int count;
	float move;		         // �ړ��W��	
	int life;		         // �v���C���[�̃��C�t
	int power;			     // �v���C���[�̃p���[
	bool damageFlag;
	bool moveFlag;
	bool endFlag;
	int damageCount;         // �_���[�W���̃J�E���g
	int shotCount;
	// �V���b�g�����������ǂ����������t���O
	bool shotSound;
	//// �F�̕ύX�����Ȃ������ǂ����������t���O
	bool changeColor;
	// �v���C���[�̐F
	PLAYER_COLOR color;
	//�v���C���[���ŃG�t�F�N�g�N���X
	EFFECT_PDEAD effectPDead;
};
