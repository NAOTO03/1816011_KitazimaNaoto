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
	shotGraph[0] = LoadGraph("data/png/EShot/RedShot.png");
	shotGraph[1] = LoadGraph("data/png/Eshot/RedShot2.png");
	shotGraph[2] = LoadGraph("data/png/Eshot/RedShot3.png");

	for (int i = 0; i < BOSS_SHOTNUM; ++i)
	{
		shot[i].flag = false;
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
	shotCount = 0;
	tempShotCount = 0;
	hp = BOSS_HP;
	prevHp = 0;
	damageFlag = false;
	noDamageFlag = false;
	flag = false;
	shotFlag = false;
	shotSound = false;
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
	case 4:
		MoveToDefault();
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

// �ӂ�ӂ�㉺�ړ�
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

// �P���ȉ��ړ�
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

// �O�p�`��`���悤�Ɉړ�
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

void BOSS::MoveToDefault()
{

	double temp;

	angle += 2;

	temp = sin(angle * DX_PI / 180);

	x = prevX + temp * moveX;
	y = prevY + temp * moveY;

	// �w�肵���ʒu�܂ňړ�������
	if (angle == 90) 
	{
		// ���̈ړ����V���b�g�p�^�[���ɕύX
		SetMovePattern(prevMovePattern + 1);
		SetShotPattern(prevShotPattern + 1);
		//���G�t���O��߂�
		noDamageFlag = false;

		// �ړ��p�^�[�����R�Ȃ�
		if (movePattern == 3)
		{
			MoveInit(320, 270, 2);
		}
	}

}

void BOSS::SetMovePattern(int pattern)
{
	// �O��̈ړ��p�^�[���Ɍ��݂̈ړ��p�^�[��������
	prevMovePattern = movePattern;
	// ���̈ړ��p�^�[���ɕύX
	movePattern = pattern;
}

void BOSS::SetShotPattern(int pattern)
{
	// �O��̃V���b�g�p�^�[���Ɍ��݂̃V���b�g�p�^��������
	prevShotPattern = shotPattern;
	// ���̃V���b�g�p�^�[���ɕύX
	shotPattern = pattern;
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

		//�T�E���h�t���O��߂�
		shotSound = false;

		// �e�̃Z�b�g
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

					// 5�����ɃV���b�g��ł�
					if (num == 0)
					{
						shot[index].rad = trad - (10 * DX_PI / 180); // ��ԍ�
					}
					else if (num == 1)
					{
						shot[index].rad = trad - (5 * DX_PI / 180);  // ������2�Ԗ�
					}
					else if (num == 2)
					{
						shot[index].rad = trad;	// �^��
					}
					else if (num == 3)
					{
						shot[index].rad = trad + (5 * DX_PI / 180);  // �E����2�Ԗ�
					}
					else if (num == 4)
					{
						shot[index].rad = trad + (10 * DX_PI / 180); // ��ԉE
					}

					++num;
					shotSound = true;

					if (num == 5)
					{
						break;
					}

				}
			}
			break;
		case 1:
			if (shotCount % 5 == 0)
			{
				if ((index = ShotSearch()) != -1)
				{
					shot[index].graph = shotGraph[2];
					shot[index].speed = 4;
					shot[index].rad = atan2(py - y, px - x) + (rand() % 41 - 20) * DX_PI / 180;	// �v���C���[�̗���20�x�܂ł͈͓̔��Ń����_��
					shot[index].pattern = 1;

					shotSound = true;
				}
			}
			break;
		case 2:
			if (shotCount % 10 == 0)
			{
				trad = atan2(py - y, px - x);
				while ((index = ShotSearch()) != -1)
				{
					shot[index].graph = shotGraph[0];
					shot[index].speed = 5;
					shot[index].rad = trad + num * ((360 - 20) * DX_PI / 180);
					shot[index].pattern = 2;
					
					++num;

					if (num == 20)
					{
						break;
					}
					shotSound = true;
				}
			}
			break;
		case 3:
			if (shotCount % 15 == 0)
			{
				while ((index = ShotSearch()) != -1)
				{
					shot[index].graph = shotGraph[0];
					shot[index].speed = 3;
					shot[index].pattern = 3;
					shot[index].rad = ((360 / 20) * DX_PI / 180) * num + ((shotCount / 15) * 0.08);

					++num;

					if (num == 20)
					{
						break;
					}
					shotSound = true;
				}
			}
			
			num = 0;

			if (shotCount % 5 == 0 && tempShotCount <= shotCount)
			{
				while ((index = ShotSearch()) != -1)
				{
					shot[index].graph = shotGraph[1];
					shot[index].speed = 6;
					shot[index].pattern = 3;

					if (num == 0)
					{
						shot[index].x = x - 50;
						shot[index].rad = atan2(py - y, px - (x - 50));
					}
					else if (num == 1)
					{
						shot[index].x = x + 50;
						shot[index].rad = atan2(py - y, px - (x + 50));
					}

					++num;

					if (num == 2)
					{
						// 5���������I������� 60���[�v(��b��)��~
						if (tempShotCount + 20 == shotCount)
						{
							tempShotCount += 80;
						}
						break;
					}
					shotSound = true;
				}
			}
			break;
		default:
			//�@�������Ȃ�
			break;
		}

		// �e�̈ړ�����
		for (int i = 0; i < BOSS_SHOTNUM; ++i)
		{
			if (shot[i].flag)
			{
				switch (shot[i].pattern)
				{
				case 0:
					shot[i].x += shot[i].speed * cos(shot[i].rad);
					shot[i].y += shot[i].speed * sin(shot[i].rad);

					if (shotCountFlag == false && shotCount == 40)
					{
						shotCountFlag = true;
					}
					break;
				case 1:
					shot[i].x += shot[i].speed * cos(shot[i].rad);
					shot[i].y += shot[i].speed * sin(shot[i].rad);
					break;
				case 2:
					shot[i].x += shot[i].speed * cos(shot[i].rad);
					shot[i].y += shot[i].speed * sin(shot[i].rad);
					break;
				case 3:
					shot[i].x += shot[i].speed * cos(shot[i].rad);
					shot[i].y += shot[i].speed * sin(shot[i].rad);
					break;
				}

				// �e���͂ݏo�Ă���t���O��߂�
				if (ShotOutCheck(i))
				{
					shot[i].flag = false;
				}
			}
		}

		++shotCount;

		if (shotCountFlag)
		{
			shotCount = 0;
		}
	}
}

void BOSS::SetDamageSetting()
{
	prevX = x;
	prevY = y;

	moveX = 320 - x;
	moveY = 170 - y;

	angle = 0;

	noDamageFlag = true;

	SetMovePattern(4);
	SetShotPattern(4);
}

void BOSS::SetFlag(bool bFlag)
{
	flag = bFlag;
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

bool BOSS::ShotOutCheck(int i)
{
	// �e����ʂɂ͂ݏo����t���O��߂�
	if (shot[i].x < -40 || shot[i].x > 640 || shot[i].y < -40 || shot[i].y > 480)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool BOSS::GetShotSound()
{
	return shotSound;
}

void BOSS::GetPosition(double *x, double *y)
{
	*x = this->x;
	*y = this->y;
}

bool BOSS::GetShotPosition(int index, double *x, double *y, int *type)
{
	if (shot[index].flag)
	{
		*x = shot[index].x;
		*y = shot[index].y;
		*type = shot[index].type;
		return true;
	}
	else
	{
		return false;
	}
}

void BOSS::SetShotFlag(int index, bool flag)
{
	shot[index].flag = flag;
}

int BOSS::SetHp(int damage)
{
	prevHp = hp;
	hp -= damage;

	return hp;
}

int BOSS::GetPrevHp()
{
	return prevHp;
}

bool BOSS::GetNoDamageFlag()
{
	return noDamageFlag;
}

void BOSS::Draw()
{
	// �e����ŏ��ɕ`��
	for (int i = 0; i < BOSS_SHOTNUM; ++i)
	{
		if (shot[i].flag)
		{
			if (shot[i].graph == shotGraph[0] || shot[i].graph == shotGraph[2])
			{
				DrawGraph(shot[i].x, shot[i].y, shot[i].graph, TRUE);
			}
			else
			{
				DrawRotaGraph(shot[i].x, shot[i].y, 1.0, shot[i].rad + 90 * DX_PI / 180, shot[i].graph, TRUE);
			}
		}
	}

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

	if (shotFlag)
	{
		Shot();
	}

	Draw();
}

