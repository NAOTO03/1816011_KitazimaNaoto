#ifndef _EFFECT_PDEAD
#define _EFFECT_PDEAD

struct PLAYER_EFFECT 
{
	double x;
	double y;
	double rad;
	int speed;
};

class EFFECT_PDEAD 
{
private:
	//���W
	double x, y;
	//�摜�̃T�C�Y
	int width;
	int height;
	//�O���t�B�b�N�n���h��
	int graph[3];
	//�J�E���g
	int count;
	//���s�����ǂ����̃t���O
	bool flag;
	//�ǂ̉摜���g�����̓Y��
	int index;
	PLAYER_EFFECT pEffect[EFFECT_PDEADNUM];

private:
	void Updata();
	void Draw();
public:
	EFFECT_PDEAD();
	void SetFlag(double x, double y, int index);
	bool GetFlag();
	void All();
};

#endif
