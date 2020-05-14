// ------ �G�l�~�[ ------

#include "DxLib.h"
#include "math.h"
#include "Game.h"
#include "define.h"
#include "enemy.h"

// �G�l�~�[������������
ENEMY::ENEMY(int type, int shotType, int movePattern, int shotPattern, int inTime, int stopTime, int shotTime, int outTime,
	         int x, int y, int speed, int hp, int item)
{
	//-------------------------------
	// ---------- �G�l�~�[ ----------
	//-------------------------------

	// �ǂݍ���
	switch (type)
	{
	case 0:
		graph = LoadGraph("data/png/Enemy/RedEnemy.png");
		break;
	case 1:
		graph = LoadGraph("data/png/Enemy/BlueEnemy.png");
		break;
	case 2:
		graph = LoadGraph("data/png/Enemy/GreenEnemy.png");
		break;
	}

	// �T�C�Y
	width = 32;
	height = 32;

	this->type = type;	       // �G�l�~�[�̎��
	this->shotType = shotType; // �e�̎��
	
	// �ړ��p�^�[���ƃV���b�g�p�^�[��
	this->movePattern = movePattern;
	this->shotPattern = shotPattern;

	// ���W�Z�b�g
	this->enemyX = x;
	this->enemyY = y;

	// �o���@��~�@���ˁ@�A�Ҏ��ԃZ�b�g
	this->inTime = inTime;
	this->stopTime = stopTime;
	this->shotTime = shotTime;
	this->outTime = outTime;

	this->item = item;

	rad = 0;
	shotNum = 0;
	count = 0;		// �G�l�~�[���o�����Ă���̃J�E���g
	shotCount = 0;	// �V���b�g�����Ă�悤�ɂȂ��Ă���̃J�E���g

	deadFlag = false;  // �G�l�~�[���Ńt���O
	endFlag = false;   // �G�l�~�[�N���X���Ńt���O
	shotFlag = false;  // �V���b�g�����Ă�悤�ɂȂ������̃t���O
	soundShot = false; // �V���b�g�����������ǂ����������t���O 

	// �e�̉摜�ƃT�C�Y���擾
	// int shotGraph = NULL;
	switch (shotType)
	{
	case 0:
		if (type == 0)
		{
			shotGraph = LoadGraph("data/png/EShot/RedShot.png");
		}
		else if(type == 1)
		{
			shotGraph = LoadGraph("data/png/Eshot/BlueShot.png");
		}
		else if (type == 2)
		{
			shotGraph = LoadGraph("data/png/Eshot/GreenShot.png");
		}
		break;
	case 1:
		if (type == 0)
		{
			shotGraph = LoadGraph("data/png/EShot/RedShot2.png");
		}
		else if (type == 1)
		{
			shotGraph = LoadGraph("data/png/Eshot/BlueShot2.png");
		}
		else if (type == 2)
		{
			shotGraph = LoadGraph("data/png/Eshot/GreenShot2.png");
		}
		break;
	case 2:
		if (type == 0)
		{
			shotGraph = LoadGraph("data/png/EShot/RedShot3.png");
		}
		else if (type == 1)
		{
			shotGraph = LoadGraph("data/png/Eshot/BlueShot3.png");
		}
		else if (type == 2)
		{
			shotGraph = LoadGraph("data/png/Eshot/GreenShot3.png");

		}
		break;
	}

	int w, h;
	GetGraphSize(shotGraph, &w, &h);

	// �e�̏�����
	for (int i = 0; i < ESHOT_NUM; ++i)
	{
		shot[i].flag = false;
		shot[i].graph = shotGraph;
		shot[i].width = w;
		shot[i].height = h;
		shot[i].pattern = shotPattern;
		shot[i].speed = speed;
		shot[i].x = x;
		shot[i].y = y;
	}
	
	
}

// �G�l�~�[�̍X�V
void ENEMY::Update()
{
	// �܂������Ă邩��ʓ��ɂ���Ƃ���������
	if (!deadFlag)
	{
		switch (movePattern)
		{
			// �r���Ŏ~�܂��āA���̂܂܌��ɋA��p�^�[��
		case 0:
			// �o�Ă��Ă���~�܂鎞�Ԃ܂ł̊ԂȂ牺�Ɉړ�
			if (inTime < gameCount && gameCount < stopTime)
			{
				enemyY += 2;
			}
			else if (gameCount > outTime)	//�A�Ҏ��Ԃ��߂�����߂�B
			{
				enemyY -= 2;
			}
			break;
		
		// ���̂܂܎~�܂炸�ɉ��ɍs���p�^�[��
		case 1:
			if (inTime <= gameCount)
			{
				enemyY += 2;
			}
			break;
		// ������Ƃ����Ɉړ����Ȃ�������Ă���
		case 2:
			if (inTime <= gameCount)
			{
				enemyY += 1;
				if (count % 10 == 0)
				{ 
					enemyX -= 1;
				}
			}
			break;
		// ������Ƃ��E�Ɉړ����Ȃ�������Ă���
		case 3:
			if (inTime <= gameCount)
			{
				enemyY += 1;
				if (count % 10 == 0)
				{
					enemyX += 1;
				}
			}
			break;
		}
		// ��ʂ���͂ݏo������AdeadFlag(�͂ݏo�������ʂ��̃t���O)��true�ɂ���
		if (gameCount >= stopTime)
		{
			if (OutCheck())
			{
				deadFlag = true;
			}
		}
		++count;
	}
}

void ENEMY::Shot()
{
	// Game�N���X�̎Q��
	Game &game = Game::GetInstance();
	double px, py;

	// ���˃^�C�~���O�ɂȂ�����A�t���O�𗧂Ă�
	if (shotTime == gameCount)
	{
		shotFlag = true;
	}

	// �t���O�������Ă���Ƃ�����
	if (shotFlag)
	{
		// �V���b�g���t���O��߂�
		soundShot = false;

		// �G�l�~�[�������Ă���Ƃ�����
		if (!deadFlag)
		{
			// �v���C���[�̈ʒu�擾
			game.GetPlayerPosition(&px, &py);

			// �G�l�~�[�ƃv���C���[�s�̍��W����t�ʒu�����߂�
			// ���񂾂����s
			if (shotCount == 0)
			{
				rad = atan2(py - enemyY, px - enemyX);
			}


			switch (shotPattern)
			{
				// �O���ɃV���b�g
			case 0:
				// 5���[�v��1�񔭎� 20�܂łȂ̂�5������
				if (shotCount % 5 == 0 && shotCount <= 20)
				{
					for (int i = 0; i < ESHOT_NUM; ++i)
					{
						// �t���O�������Ă��Ȃ��e��T���āA���W�����Z�b�g
						if (shot[i].flag == false)
						{
							shot[i].flag = true;
							shot[i].x = enemyX + shot[i].width / 2;
							shot[i].y = enemyY + shot[i].height * 2;
							shot[i].rad = rad;
							break;
						}
					}
					// �V���b�g�T�E���h�t���O�𗧂Ă�
					soundShot = true;
				}
				break;
				// �v���C���[�Ɍ������Ē����V���b�g
			case 1:
				// 6���[�v��1�񔭎� 54�܂łȂ̂�10������
				if (shotCount % 6 == 0 && shotCount <= 54)
				{
					for (int i = 0; i < ESHOT_NUM; ++i)
					{
						// �t���O�������Ă��Ȃ��e��T���āA���W�����Z�b�g
						if (shot[i].flag == false)
						{
							shot[i].flag = true;
							shot[i].x = enemyX + shot[i].width * 2;
							shot[i].y = enemyY + shot[i].height * 2;
							shot[i].rad = rad;
							break;
						}
					}
					// �V���b�g�T�E���h�t���O�𗧂Ă�
					soundShot = true;
				}
				break;
				// 3���������V���b�g
			case 2:
				// 10���[�v��1�񔭎ˁ@1���[�v��3���Ȃ̂�5���[�v�������15������
				if (shotCount % 10 == 0 && shotCount <= 40)
				{
					for (int i = 0; i < ESHOT_NUM; ++i)
					{
						// �t���O�������Ă��Ȃ��e��T���āA���W�����Z�b�g
						if (shot[i].flag == false)
						{
							shot[i].flag = true;
							shot[i].x = enemyX + shot[i].width * 2;
							shot[i].y = enemyY + shot[i].height * 2;
							// 0�̎��͍����
							if (shotNum == 0)
							{
								// �G�l�~�[�ƃv���C���[�Ƃ̋t���ڂ���10�x���������W�A������
								shot[i].rad = rad - (10 * DX_PI / 180);	// DX_PI 3.14
							}
							else if (shotNum == 1)	// 1�̎��̓v���C���[�Ɉ꒼��
							{
								// �G�l�~�[�ƃv���C���[�Ƃ̋t���ڂ���
								shot[i].rad = rad;
							}
							else if (shotNum == 2)	// 2�̎��͉E���
							{
								// �G�l�~�[�v���C���[�Ƃ̋t���ڂ���10�x���������W�A������
								shot[i].rad = rad + (10 * DX_PI / 180);
							}
							++shotNum;

							// 3�����˂����� shotNum��0�Ƀ��[�v���Ĕ�����
							if (shotNum == 3)
							{
								shotNum = 0;
								break;
							}
						}
					}
					// �V���b�g�T�E���h�t���O�𗧂Ă�
					soundShot = true;
				}
				break;
				// ���˃V���b�g
			case 3:
				//3���[�v�Ɉ�񔭎ˁB42�܂łȂ̂�20�����ˁB
				if (shotCount % 3 == 0 && shotCount <= 57)
				{
					for (int i = 0; i < ESHOT_NUM; ++i)
					{
						// �t���O�������Ă��Ȃ��e��T���āA���W�����Z�b�g
						if (shot[i].flag == false)
						{
							shot[i].flag = true;
							shot[i].x = enemyX + shot[i].width;
							shot[i].y = enemyY + shot[i].height * 2;
							// ���񂾂�����������
							if (shotNum == 0)
							{
								srand((unsigned int)time(NULL));
							}
							shot[i].rad = atan2(py - enemyY, px - enemyX) - (60 * DX_PI / 180) + ((rand() % 120) * DX_PI / 180);
							++shotNum;
							break;
						}
					}
					// �V���b�g�T�E���h�t���O�𗧂Ă�
					soundShot = true;
				}
				break;
			}
		}

		

		// �t���O�������Ă���e�̐�
		int flagNum = 0;

		//�t���O�̗����Ă���e�����A�e�̈ړ����s��
		for (int i = 0; i < ESHOT_NUM; ++i)
		{
			if (shot[i].flag)
			{
				switch(shot[i].pattern)
				{
				case 0:
					shot[i].y += shot[i].speed;
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

				// �e����ʂɂ͂ݏo����t���O��߂�
				if (ShotOutCheck(i))
				{
					shot[i].flag = false;
					continue;
				}
				++flagNum;
			}
		}

		// flagNum��0�Ƃ������Ƃ͔��˒��̒e���Ȃ�
		// ����deadFlag��true�Ƃ������Ƃ͂��̃G�l�~�[�̃N���X�͏��ł����Ă�����
		if (flagNum == 0 && deadFlag)
		{
			// �G�l�~�[�N���X���Ńt���O��true�ɂ���
			endFlag = true;
		}

		++shotCount;
	}

}

void ENEMY::Draw()
{
	// �e����ŏ��`��
	for (int i = 0; i < ESHOT_NUM; ++i)
	{
		if (shot[i].flag)
		{
			if (shotType == 0 || shotType == 2)
			{
				DrawGraph(shot[i].x, shot[i].y, shot[i].graph, TRUE);
				// DrawCircle(shot[i].x + shot[i].width / 2, shot[i].y + shot[i].height / 2, 6, 0x000000, true);
			}
			else
			{
				DrawRotaGraph(shot[i].x, shot[i].y, 1.0, shot[i].rad + (90 * DX_PI / 180), shot[i].graph, TRUE);
				// DrawCircle(shot[i].x, shot[i].y, 4, 0x000000, true);
			}
		}
	}

	if (!deadFlag)
	{
		DrawGraph(enemyX, enemyY, graph, TRUE);
	}
}

bool ENEMY::OutCheck()
{
	// �G�l�~�[����ʂ���o����t���O��true�ɂ���
	if (enemyX < -50 || enemyX > 680 || enemyY < -50 || enemyY > 520)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool ENEMY::ShotOutCheck(int i)
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

void ENEMY::GetPosition(double *x, double *y)
{
	*x = this->enemyX + width / 2;
	*y = this->enemyY + height / 2;
}

bool ENEMY::GetShotPosition(int index, double *x, double *y)
{
	if (shot[index].flag)
	{
		if (shotType == 0 || shotType == 2)
		{
			*x = shot[index].x + shot[index].width / 2;
			*y = shot[index].y + shot[index].height / 2;
			return true;
		}
		else
		{
			*x = shot[index].x;
			*y = shot[index].y;
			return true;
		}
	}
	else
	{
		return false;
	}
}

void ENEMY::SetShotFlag(int index, bool flag)
{
	shot[index].flag = flag;
}

int ENEMY::GetEnemyType()
{
	return type;
}

int ENEMY::GetShotType()
{
	return shotType;
}

void ENEMY::SetDeadFlag()
{
	deadFlag = true;
}

bool ENEMY::GetDeadFlag()
{
	return deadFlag;
}

bool ENEMY::GetShotSound()
{
	return soundShot;
}

int ENEMY::GetItem()
{
	return item;
}

bool ENEMY::All()
{
	Update();
	Shot();
	Draw();

	return endFlag;
}