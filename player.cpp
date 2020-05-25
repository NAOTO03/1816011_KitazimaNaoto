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
	width = 8;
	height = 8;
	rad = 0;
	count = 0;
	color = BLACK;
	move = 1.0f;
	life = 1;
	power = 5;
	shotCount = 0;
	damageCount = 0;

	//�e������
	memset(shot, 0, sizeof(shot));

	//�e�摜�ǂݍ���
	int temp = LoadGraph("data/png/PShot/BlackShot.png");
	int w, h;
	GetGraphSize(temp, &w, &h);

	damageFlag = false;
	moveFlag = false;
	endFlag = false;
	shotSound = false; // �V���b�g�����������ǂ����������t���O 

	//�t���O��S��false�ɂ��Ƃ�
	//�O���t�B�b�N�n���h���Ɖ摜�̃T�C�Y�������Ƃ�
	for (int i = 0; i < PSHOT_NUM; ++i)
	{
		shot[i].flag = false;
		shot[i].graph[0] = LoadGraph("data/png/PShot/BlackShot.png");
		shot[i].graph[1] = LoadGraph("data/png/PShot/WhiteShot.png");
		shot[i].width = w;
		shot[i].height = h;
	}

	// �v���C���[
	graph[0] = LoadGraph("data/png/Player/BlackPlayer.png");
	graph[1] = LoadGraph("data/png/Player/WhitePlayer.png");
	// ��]����g
	rGraph[0] = LoadGraph("data/png/Player/RotateBlack.png");
	rGraph[1] = LoadGraph("data/png/Player/RotateWhite.png");
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
	if (playerX < 24)
	{
		playerX = 24;
	}
	if (playerX > 640 - 24)
	{
		playerX = 640 - 24;
	}
	if (playerY < 24)
	{
		playerY = 24;
	}
	if (playerY > 600 - 24)
	{
		playerY = 600 - 24;
	}

	//0.04���W�A��(��2�x)����]������B
	rad = 0.04 * count;

	++count;

	if (CheckHitKey(KEY_INPUT_X))
	{
		color = BLACK;
	}
	if (CheckHitKey(KEY_INPUT_C))
	{
		color = WHITE;
	}

}

void PLAYER::Shot()
{
	shotSound = false;
	int num = 0;

	if (!damageFlag)
	{
		// �L�[��������ĂĂ��A6���[�v�Ɉ�񔭎�
		if (CheckHitKey(KEY_INPUT_Z) == 1 && shotCount % 6 == 0) 
		{
			for (int i = 0; i < PSHOT_NUM; ++i)
			{
				if (shot[i].flag == false)
				{
					// �p���[��5��菬�����Ƃ��O���ɓ�V���b�g������
					if (power < 5)
					{
						if (num == 0)
						{
							shot[i].flag = true;
							// �e�̈ʒu���Z�b�g�A�ʒu�̓v���C���[�̍�
							shot[i].x = playerX - width / 6;
							shot[i].y = playerY - height / 4;
							shot[i].rad = -1.57;
						}
						else if(num == 1)
						{
							shot[i].flag = true;
							// �e�̈ʒu���Z�b�g�A�ʒu�̓v���C���[�̉E
							shot[i].x = playerX + width;
							shot[i].y = playerY - height / 4;
							shot[i].rad = -1.57;
						}

						++num;

						// ��������烋�[�v���甲����
						if (num == 2)
						{
							break;
						}
					}
					else if (power >= 5 && power < 10)	// �O���ɂS�V���b�g������
					{
						if (num == 0)		
						{
							shot[i].flag = true;
							// �e�̈ʒu���Z�b�g�A�ʒu�̓v���C���[�̍�
							shot[i].x = playerX - width * 2;
							shot[i].y = playerY - height / 4;
							shot[i].rad = -1.57;
						}
						else if (num == 1)	
						{
							shot[i].flag = true;
							// �e�̈ʒu���Z�b�g�A�ʒu�̓v���C���[�̍�����Q�Ԗ�
							shot[i].x = playerX - width / 6;
							shot[i].y = playerY - height / 4;
							shot[i].rad = -1.57;
						}
						else if (num == 2)	
						{
							shot[i].flag = true;
							// �e�̈ʒu���Z�b�g�A�ʒu�̓v���C���[�̉E����Q�Ԗ�
							shot[i].x = playerX + width;
							shot[i].y = playerY - height / 4;
							shot[i].rad = -1.57;
						}
						else if (num == 3) 
						{
							shot[i].flag = true;
							// �e�̈ʒu���Z�b�g�A�ʒu�̓v���C���[�̉E
							shot[i].x = playerX + width * 3;
							shot[i].y = playerY - height / 4;
							shot[i].rad = -1.57;
						}

						++num;

						//�l�������烋�[�v���甲����
						if (num == 4)
						{
							break;
						}
					}
					else if (power >= 10)	// 3�����ɃV���b�g��ł�
					{
						if (num == 0)
						{
							shot[i].flag = true;
							// �e�̈ʒu���Z�b�g�A�ʒu�̓v���C���[�̍�
							shot[i].x = playerX - width * 2;
							shot[i].y = playerY - height / 4;
							shot[i].rad = -1.57;
						}
						else if (num == 1)
						{
							shot[i].flag = true;
							// �e�̈ʒu���Z�b�g�A�ʒu�̓v���C���[�̍�����Q�Ԗ�
							shot[i].x = playerX - width / 6;
							shot[i].y = playerY - height / 4;
							shot[i].rad = -1.57;
						}
						else if (num == 2)
						{
							shot[i].flag = true;
							// �e�̈ʒu���Z�b�g�A�ʒu�̓v���C���[�̉E����2�Ԗ�z
							shot[i].x = playerX + width;
							shot[i].y = playerY - height / 4;
							shot[i].rad = -1.57;
						}
						else if (num == 3)
						{
							shot[i].flag = true;
							// �e�̈ʒu���Z�b�g�A�ʒu�̓v���C���[�̉E
							shot[i].x = playerX + width * 3;
							shot[i].y = playerY - height / 4;
							shot[i].rad = -1.57;
						}
						else if (num == 4)	// 4�̎������΂ߏ�
						{
							shot[i].flag = true;
							shot[i].x = playerX - width * 3;
							shot[i].y = playerY - height / 4;
							shot[i].rad = -1.69;
						}
						else if (num == 5) // 5�̎����E�΂ߏ�
						{
							shot[i].flag = true;
							shot[i].x = playerX + width * 4;
							shot[i].y = playerY - height / 4;
							shot[i].rad = -1.45;
						}

						++num;

						// 3�����Ɍ������烋�[�v���甲����
						if (num == 6)
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
			case BLACK:
				DrawRotaGraph(shot[i].x, shot[i].y, 1.0, shot[i].rad + (90 * DX_PI / 180), shot[i].graph[0], TRUE);
				break;
			case WHITE:
				DrawRotaGraph(shot[i].x, shot[i].y, 1.0, shot[i].rad + (90 * DX_PI / 180), shot[i].graph[1], TRUE);
				break;
			}
		}
	}

	// �����Ă���Ε`��
	if (damageFlag)
	{
		if (damageCount % 2 == 0)	// 2�Ŋ����ė]�肪0�ɂȂ����Ƃ��ɏ������߂����ĕ`��
		{
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);	// ���߃��[�h
			switch (color)
			{
			case BLACK:
				DrawGraph(playerX, playerY, graph[0], TRUE);
				break;
			case WHITE:
				DrawGraph(playerX, playerY, graph[1], TRUE);
				break;
			}
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}
		else
		{
			switch (color)
			{
			case BLACK:
				DrawGraph(playerX, playerY, graph[0], TRUE);
				break;
			case WHITE:
				DrawGraph(playerX, playerY, graph[1], TRUE);
				break;
			}
		}
		++damageCount;
		moveFlag = true;
		if (damageCount == 140)
		{
			damageFlag = false;
			damageCount = 0;
			// ���W�������n�ɖ߂�
			playerX = playerX;
			playerY = playerY;
		}
	}
	else
	{
		// �ʏ�`��
		switch (color)
		{
		case BLACK:
			DrawGraph(playerX, playerY, graph[0], TRUE);
			DrawRotaGraph(playerX + width / 2, playerY + height / 2, 1.0, rad, rGraph[0], TRUE);
			DrawRotaGraph(playerX + width / 2, playerY + height / 2, 1.0, -rad, rGraph[0], TRUE);
			break;
		case WHITE:
			DrawGraph(playerX, playerY, graph[1], TRUE);
			DrawRotaGraph(playerX + width / 2, playerY + height / 2, 1.0, rad, rGraph[1], TRUE);
			DrawRotaGraph(playerX + width / 2, playerY + height / 2, 1.0, -rad, rGraph[1], TRUE);
			break;
		}
	}
	// DrawCircle(playerX + width / 2, playerY + height / 2, 4, 0xff0000, true);
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
	if (power > 15)
	{
		// �p���[�̍ő�l��10�ɂ��Ă���
		power = 15;
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
	if (!damageFlag || moveFlag)
	{
		Update();
	}
	Shot();
	Draw();
	effectPDead.All();
	++shotCount;
}

