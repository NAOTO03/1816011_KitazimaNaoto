// ------ �v���C���[�@------

#include "DxLib.h"
#include "player.h"
#include "math.h"

// �v���C���[������������
PLAYER::PLAYER()
{
	//---------------------------------
	// ---------- �v���C���[ ----------
	//---------------------------------
	playerX = PLAYER_INITX;
	playerY = PLAYER_INITY;
	width = 24;
	height = 24;
	color = RED;
	move = 1.0f;
	life = 5;
	power = 5;
	shotCount = 0;
	damageCount = 0;

	//�e������
	memset(shot, 0, sizeof(shot));

	//�e�摜�ǂݍ���
	int temp = LoadGraph("data/png/PShot/RedShot.png");
	int w, h;
	GetGraphSize(temp, &w, &h);

	damageFlag = false;
	endFlag = false;
	shotSound = false; // �V���b�g�����������ǂ����������t���O 

	//�t���O��S��false�ɂ��Ƃ�
	//�O���t�B�b�N�n���h���Ɖ摜�̃T�C�Y�������Ƃ�
	for (int i = 0; i<PSHOT_NUM; ++i)
	{
		shot[i].flag = false;
		shot[i].graph[0] = LoadGraph("data/png/PShot/RedShot.png");
		shot[i].graph[1] = LoadGraph("data/png/PShot/BlueShot.png");
		shot[i].graph[2] = LoadGraph("data/png/PShot/GreenShot.png");
		shot[i].width = w;
		shot[i].height = h;
	}

	// �v���C���[�̃O���t�B�b�N���������Ƀ��[�h���\�����W��������
	graph[0] = LoadGraph("data/png/Player/RedPlayer.png");
	graph[1] = LoadGraph("data/png/Player/BluePlayer.png");
	graph[2] = LoadGraph("data/png/Player/GreenPlayer.png");
}

// �v���C���[�̍X�V
void PLAYER::Update()
{
	if (CheckHitKey(KEY_INPUT_LEFT) == 1 || CheckHitKey(KEY_INPUT_RIGHT) == 1) 
	{
		if (CheckHitKey(KEY_INPUT_UP) == 1 || CheckHitKey(KEY_INPUT_DOWN) == 1) 
		{
				//�ړ��W�����O�D�V�P�ɐݒ�
				move = 0.71f;
		}
		else {
				//�΂߂���Ȃ���΂P�D�O�ɐݒ�
				move = 1.0f;
		}
	}
	else if (CheckHitKey(KEY_INPUT_UP) == 1 || CheckHitKey(KEY_INPUT_DOWN) == 1)
	{
			move = 1.0f;
	}

	// ���L�[�������Ă�����v���C���[���ړ�������
	if (CheckHitKey(KEY_INPUT_UP) == 1)
	{
		 playerY -= PLAYER_SPEED*move;
	}
	if (CheckHitKey(KEY_INPUT_DOWN) == 1)
	{
		playerY += PLAYER_SPEED*move;
	}
	if (CheckHitKey(KEY_INPUT_LEFT) == 1)
	{
		playerX -= PLAYER_SPEED*move;
	}
	if (CheckHitKey(KEY_INPUT_RIGHT) == 1)
	{
		playerX += PLAYER_SPEED*move;
	}

	// �v���C���[����ʍ��[����͂ݏo�����ɂȂ��Ă������ʓ��̍��W�ɖ߂��Ă�����
	if (playerX < 0)
	{
		playerX = 0;
	}
	if (playerX > 640 - 24)
	{
		playerX = 640 - 24;
	}
	if (playerY < 0)
	{
		playerY = 0;
	}
	if (playerY > 480 - 24)
	{
		playerY = 480 - 24;
	}

	if (CheckHitKey(KEY_INPUT_A))
	{
		color = RED;
	}
	if (CheckHitKey(KEY_INPUT_S))
	{
		color = BLUE;
	}
	if (CheckHitKey(KEY_INPUT_D))
	{
		color = GREEN;
	}

}

void PLAYER::Shot()
{
	shotSound = false;
	int num = 0;

	if (!damageFlag)
	{
		// �L�[��������ĂĂ��A6���[�v�Ɉ�񔭎�
		if (CheckHitKey(KEY_INPUT_SPACE) == 1 && shotCount % 6 == 0) 
		{
			for (int i = 0; i < PSHOT_NUM; ++i)
			{
				if (shot[i].flag == false)
				{
					// �p���[��5��菬�����Ƃ��O���ɃV���b�g������
					if (power < 5)
					{
					    shot[i].flag = true;
						// �e�̈ʒu���Z�b�g�A�ʒu�̓v���C���[�̒��S�ɂ���
						shot[i].x = playerX + width / 2;
						shot[i].y = playerY - height / 2;
						shot[i].rad = -1.57;
						break;
					}
					else if (power >= 5)	// 3�����ɃV���b�g��ł�
					{
						// 0�̎����O���ɃV���b�g
						if (num == 0)
						{
							shot[i].flag = true;
							shot[i].x = playerX + width / 2;
							shot[i].y = playerY - height / 2;
							shot[i].rad = -1.57;
						}
						else if (num == 1)	// 1�̎������΂ߏ�
						{
							shot[i].flag = true;
							shot[i].x = playerX + width / 2;
							shot[i].y = playerY - height / 2;
							shot[i].rad = -1.69;
						}
						else if (num == 2)	// 2�̎����E�΂ߏ�
						{
							shot[i].flag = true;
							shot[i].x = playerX + width / 2;
							shot[i].y = playerY - height / 2;
							shot[i].rad = -1.45;
						}

						++num;

						// 3�����ɑł����烋�[�v���甲����
						if (num == 3)
						{
							break;
						}
					}
				}
			}
			// �V���b�g�T�E���h�t���O�𗧂Ă�
			shotSound = true;
		}
	}

	//�e���ړ������鏈��
	for (int i = 0; i < PSHOT_NUM; ++i) 
	{
		//���˂��Ă�e����
		if (shot[i].flag) 
		{
			shot[i].x += cos(shot[i].rad) * PSHOT_SPEED;
			shot[i].y += sin(shot[i].rad) * PSHOT_SPEED;
			//��ʂ̊O�ɂ͂ݏo������t���O��߂�
			if (shot[i].y < -10 || shot[i].x < -20 || shot[i].x > 640)
			{
				shot[i].flag = false;
			}
		}
	}
}

void PLAYER::Draw()
{
	//�e�`��
	for (int i = 0; i < PSHOT_NUM; ++i)
	{
		if (shot[i].flag)
		{
			switch (color)
			{
			case RED:
				DrawRotaGraph(shot[i].x, shot[i].y, 1.0, shot[i].rad + (90 * DX_PI / 180), shot[i].graph[0], TRUE);
				break;
			case BLUE:
				DrawRotaGraph(shot[i].x, shot[i].y, 1.0, shot[i].rad + (90 * DX_PI / 180), shot[i].graph[1], TRUE);
				break;
			case GREEN:
				DrawRotaGraph(shot[i].x, shot[i].y, 1.0, shot[i].rad + (90 * DX_PI / 180), shot[i].graph[2], TRUE);
				break;
			}
		}
	}

	// �����Ă���Ε`��
	if (damageFlag)
	{
		if (damageCount > 40)	// �G�l�~�[�̒e������������40�܂ŕ`������Ȃ�
		{
			if (damageCount % 2 == 0)	// 2�Ŋ����ė]�肪0�ɂȂ����Ƃ��ɏ������߂����ĕ`��
			{
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);	// ���߃��[�h
				switch (color)
				{
				case RED:
					DrawGraph(PLAYER_INITX, PLAYER_INITY + 60 - (damageCount - 40), graph[0], FALSE);
					break;
				case BLUE:
					DrawGraph(PLAYER_INITX, PLAYER_INITY + 60 - (damageCount - 40), graph[1], FALSE);
					break;
				case GREEN:
					DrawGraph(PLAYER_INITX, PLAYER_INITY + 60 - (damageCount - 40), graph[2], FALSE);
					break;
				}
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			}
			else
			{
				switch (color)
				{
				case RED:
					DrawGraph(PLAYER_INITX, PLAYER_INITY + 60 - (damageCount - 40), graph[0], FALSE);
					break;
				case BLUE:
					DrawGraph(PLAYER_INITX, PLAYER_INITY + 60 - (damageCount - 40), graph[1], FALSE);
					break;
				case GREEN:
					DrawGraph(PLAYER_INITX, PLAYER_INITY + 60 - (damageCount - 40), graph[2], FALSE);
					break;
				}
			}
		}
		++damageCount;
		if (damageCount == 100)
		{
			damageFlag = false;
			damageCount = 0;
			// ���W�������n�ɖ߂�
			playerX = PLAYER_INITX;
			playerY = PLAYER_INITY;
		}
	}
	else
	{
		// �ʏ�`��
		switch (color)
		{
		case RED:
			DrawGraph(playerX, playerY, graph[0], FALSE);
			break;
		case BLUE:
			DrawGraph(playerX, playerY, graph[1], FALSE);
			break;
		case GREEN:
			DrawGraph(playerX , playerY, graph[2], FALSE);
			break;
		}
	}
	//  DrawCircle(playerX + width / 2, playerY + height / 2, 10, 0x000000, true);
}

void PLAYER::GetPosition(double *x, double *y)
{
	*x = this->playerX + width / 2;
	*y = this->playerY + height / 2;
}

bool PLAYER::GetShotPosition(int index, double *x, double *y)
{
	if (shot[index].flag)
	{
		*x = shot[index].x;
		*y = shot[index].y;
		return true;
	}
	else
	{
		return false;
	}
}

bool PLAYER::GetShotSound()
{
	return shotSound;
}

void PLAYER::SetShotFlag(int index, bool flag)
{
	shot[index].flag = flag;
}

void PLAYER::SetDamageFlag()
{
	damageFlag = true;
	// ���C�t�����炷
	if (life > 0)
	{
		--life;
	}
	else
	{
		life = 0;
	}
	// ���ŃG�t�F�N�g�̃t���O�𗧂Ă�
	effectPDead.SetFlag(playerX, playerY, color);
}

bool PLAYER::GetDamageFlag()
{
	return damageFlag;
}

int  PLAYER::GetPlayerColor()
{
	return color;
}

int PLAYER::GetLife()
{
	return life;
}

void PLAYER::SetPower(int p)
{
	power += p;
	if (power > 10)
	{
		// �p���[�̍ő�l��10�ɂ��Ă���
		power = 10;
	}

	if (power < 0)
	{
		power = 0;
	}
}

int PLAYER::GetPower()
{
	return power;
}

void PLAYER::All()
{
	// ���ł��Ă��Ȃ��Ƃ��������s
	if (!damageFlag)
	{
		Update();
	}
	Shot();
	Draw();
	effectPDead.All();
	++shotCount;
}

