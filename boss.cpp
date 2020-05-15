#include "DxLib.h"
#include "math.h"
#include "define.h"
#include "boss.h"
#include "Game.h"


BOSS::BOSS()
{
	x = 320;
	y = -100;
	prevX = 320;
	prevY = -100;

	bGraph[0] = LoadGraph("data/png/Boss/RedBoss.png");
	shotGraph[0] = LoadGraph("data/png/EShot/RedSho1.png");
	shotGraph[1] = LoadGraph("data/png/Eshot/RedShot2.png");
	shotGraph[2] = LoadGraph("data/png/Eshot/RedShot3.png");

	for (int i = 0; i < BOSS_SHOTNUM; ++i)
	{
		shot[i].flag = false;
		shot[i].gFlag = false;
		shot[i].graph = 0;
		shot[i].pattern = 0;
		shot[i].rad = 0;
		shot[i].speed = 0;
		shot[i].x = 0;
		shot[i].y = 0;
	}

	raise = 2;
	raise2 = 2;
	angle = 0;
	movePattern = 0;
	shotPattern = 0;
	moveX = 0;
	moveY = 270;
	waitCount = 0;
	wait = false;
	state = 0;
	damageFlag = false;
	flag = false;
	shotFlag = false;
}

void BOSS::Updata()
{
	switch (movePattern)
	{
	case 0:
		Appear();
		break;
	case 1:
		MovePattern1();
		break;
	case 2:
		MovePattern2();
		break;
	case 3:
		MovePattern3();
		break;
	}
}

void BOSS::Appear()
{
	double temp;

	angle += 2;
	temp = sin(angle * DX_PI / 180);
	x = 320;
	y = prevY + temp * moveY;

	// ��ʒu�܂ňړ�������ړ��p�^�[����ύX
	if (angle == 90)
	{
		movePattern = 1;
		angle = 0;
		shotFlag = true;
	}
}

void BOSS::MovePattern1()
{
	angle += raise;

	y = 170 + sin(angle * DX_PI / 180) * BOSS_SHAKE;

	if (angle == 90)
	{
		raise = -2;
	}
	else if (angle == -90)
	{
		raise = 2;
	}

	x = 320;
}

void BOSS::MovePattern2()
{
	if (!wait)
	{
		x += raise2;

		if (x == 160)
		{
			raise2 = 2;
			wait = true;
		}
		else if (x == 480)
		{
			raise2 = -2;
			wait = true;
		}
	}

	if (wait)
	{
		++waitCount;
		if (waitCount == 30)
		{
			wait = false;
			waitCount = 0;
		}
	}
}

void BOSS::MovePattern3()
{
	double temp;

	angle += 2;

	temp = sin(angle * DX_PI / 180);

	x = prevX + temp * moveX;
	y = prevY + temp * moveY;

	if (angle == 90)
	{
		if (state == 0)
		{
			MoveInit(160, 170, 1);
		}
		else if (state == 1)
		{
			MoveInit(320, 270, 2);
		}
		else if (state == 2)
		{
			MoveInit(480, 170, 0);
		}
	}
}

void BOSS::MoveInit(double bx, double by, int bState)
{
	prevX = x;
	prevY = y;

	moveX = bx - x;
	moveY = by - y;

	angle = 0;

	state = bState;
}

void  BOSS::Shot()
{
	// �������˂�����
	int num = 0;
	// �󂢂Ă�e�̓Y����
	int index;
	// shotCount��߂����ǂ����̃t���O
	bool shotCountFlag = false;

	Game &game = Game::GetInstance();

	double px, py;
	static double trad;

	if (!damageFlag)
	{
		game.GetPlayerPosition(&px, &py);

		if (shotCount == 0)
		{
			trad = atan2(py - y, px - x);
		}

		// �T�E���h�t���O��߂�
		// shotSound = false;

		switch (shotPattern)
		{
		case 0:
			if (shotCount % 5 == 0 && shotCount <= 15)
			{
				while ((index = ShotSearch()) != -1)
				{
					shot[index].graph = shotGraph[1];
					shot[index].pattern = 0;
					shot[index].speed = 6;
				}
			}
		}
	}
}

void BOSS::SetDamageFlag()
{

}

void BOSS::SetFlag(bool f)
{

}

bool BOSS::GetFlag()
{
	return flag;
}

int BOSS::ShotSearch()
{
	bool check = false;
	int i;

	for (i = 0; i < BOSS_SHOTNUM; ++i)
	{
		if (shot[i].flag == false) 
		{
			check = true;
			break;
		}
	}

	if (check)
	{
		shot[i].flag = true;
		shot[i].x = x;
		shot[i].y = y;
	}
	else 
	{
		i = -1;
	}

	return i;
}

void BOSS::Draw()
{
	// �e�������������ɂ̓_���[�W�p�̉摜��`��
	if (damageFlag)
	{
		DrawRotaGraph(x, y, 1.0, 0, bGraph[0], TRUE);
	}	
	else
	{
		// �����Ȃ��Ƃ��͒ʏ�`��
		DrawRotaGraph(x, y, 1.0, 0, bGraph[0], TRUE);
	}

	damageFlag = false;
}

void BOSS::All()
{
	Updata();
	Draw();
}

