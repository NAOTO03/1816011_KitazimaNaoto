#pragma once

//extern�錾����key�z��ɂǂ�����ł��A�N�Z�X�ł���悤�ɂ���
extern char key[256];

//�O���[�o���J�E���g
extern int gameCount;

// ---------- �����蔻��p���a��` ----------

#define PLAYER_COLLISION 4	// �v���C���[�̓����蔻��p
#define ENEMY_COLLISION 12  // �G�l�~�[�̓����蔻��p

#define PSHOT_COLLISION 4	// �v���C���[�̒e
#define ESHOT0_COLLISION 6  // �G�l�~�[�̒e(�ۂ��e)
#define ESHOT1_COLLISION 4	// �c���̒e
#define ESHOT2_COLLISION 4  // �Ђ��`�̏����Ȓe

#define BOSS_COLLISION 60   // �{�X�̓����蔻��p

#define ITEM_COLLISION 10   // �A�C�e���̓����蔻��p���a


// ---------- �v���C���[�֘A ----------

//�v���C���[�̏����ʒu
#define PLAYER_INITX 310
#define PLAYER_INITY 550
//�v���C���[�̈ړ��X�s�[�h
#define PLAYER_SPEED 3
//�v���C���[�̒e�̐�
#define PSHOT_NUM 200
//�e�X�s�[�h
#define PSHOT_SPEED 8
// �v���C���[�̃G�t�F�N�g�̐�
#define EFFECT_PDEADNUM 80

// ---------- �G�l�~�[�֘A ----------

// �G�l�~�[�̐�
#define ENEMY_NUM 54
// �G�l�~�[�̒e�̐�
#define ESHOT_NUM 300
// �G�l�~�[�̃G�t�F�N�g�̐�
#define EFFECT_EDEADNUM 50

// ---------- �{�X�֘A ----------

// �{�X�̒e�̐�
#define BOSS_SHOTNUM 300
// �{�X�̗h�ꕝ
#define BOSS_SHAKE 20
// �{�X��HP
#define BOSS_HP 1500

// ---------- �w�i�֘A ----------

// �X�R�A�̕����`��̊�ƂȂ�X���W
#define SCORE_X 660

//�A�C�e���̑���
#define ITEM_NUM 30



// ---------- �v���C���[�֘A ----------

struct PSHOT
{
	bool flag;         //�e�����˒����ǂ���
	double x;
	double y;
	int graph[2];
	int width, height; //�摜�̕��ƍ���
	double rad;		   // �p�x
};

enum PLAYER_COLOR
{
	BLACK,
	WHITE
};

// ---------- �G�l�~�[�֘A ----------

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
	int color;
};

// ---------- �w�i�֘A ----------

struct FILE_DATA
{
	int score;
	int highScore;
};
