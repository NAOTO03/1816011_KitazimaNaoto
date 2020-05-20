#pragma once

//�O���[�o���J�E���g
extern int gameCount;

//�����蔻��p���a��`
#define PLAYER_COLLISION 4
#define ENEMY_COLLISION 14

#define PSHOT_COLLISION 4
#define ESHOT0_COLLISION 6
#define ESHOT1_COLLISION 4
#define ESHOT2_COLLISION 3

#define BOSS_COLLISION 60


//�v���C���[�̏����ʒu
#define PLAYER_INITX 310
#define PLAYER_INITY 550

//�v���C���[�̈ړ��X�s�[�h
#define PLAYER_SPEED 4

//�v���C���[�̒e�̐�
#define PSHOT_NUM 200
//�e�X�s�[�h

#define PSHOT_SPEED 8

// �G�l�~�[�̐�
#define ENEMY_NUM 15

// �G�l�~�[�̒e�̐�
#define ESHOT_NUM 100

// �G�l�~�[�̃G�t�F�N�g�̐�
#define EFFECT_EDEADNUM 20

// �v���C���[�̃G�t�F�N�g�̐�
#define EFFECT_PDEADNUM 80

// �X�R�A�̕����`��̊�ƂȂ�X���W
#define SCORE_X 660

//�A�C�e���̓����蔻��p���a
#define ITEM_COLLISION 10
//�A�C�e���̑���
#define ITEM_NUM 30

// �{�X�̒e�̐�
#define BOSS_SHOTNUM 200
// �{�X�̗h�ꕝ
#define BOSS_SHAKE 20
// �{�X��HP
#define BOSS_HP 500

struct ENEMYDATA
{
	int type;		// �G�l�~�[�̎��
	int shotType;	// �e�̎��
	int movePattern;// �ړ��p�^�[��
	int shotPattern;// ���˃p�^�[��
	int inTime;		//�o������
	int stopTime;	// ��~����
	int shotTime;	// �e���ˎ���
	int outTime;	// �A�Ҏ���	
	int x;			// x���W
	int y;			// y���W
	int speed;		// �X�s�[�h
	int hp;			// HP
	int item;		// �A�C�e��
};

struct ESHOT
{
	bool flag;	 // �e�����˒����ǂ���
	double x;
	double y;
	double rad;	 // �p�x(���W�A��)
	int graph;
	int width, height;
	int pattern; // �V���b�g�p�^�[��
	int speed;
	int type;
};
