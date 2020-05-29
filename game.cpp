//-----------------------------------------------------------------------------
// �Q�[���̏���.
//-----------------------------------------------------------------------------
#include "Game.h"
#include "define.h"
#include "sceneMgr.h"

//-----------------------------------------------------------------------------
// �R���X�g���N�^
//-----------------------------------------------------------------------------
Game::Game()
{
	// �w�i�N���X
	back = new BACK;

	//�v���C���[�N���X�̐���
	player = new PLAYER;

	//�G�t�F�N�g�N���X�̃C���X�^���X����
	for (int i = 0; i < EFFECT_EDEADNUM; ++i) 
	{
		 effectEData[i] = new EFFECT_EDEAD;
	}

	for (int i = 0; i < EFFECT_PDEADNUM; ++i)
	{
		effectPData[i] = new EFFECT_PDEAD;
	}

	// �X�R�A�N���X
	score = new SCORE;

	//�A�C�e���N���X
	for (int i = 0; i < ITEM_NUM; ++i) 
	{
		item[i] = new ITEM;
	}

	FILE *fp = NULL;
	ENEMYDATA data[ENEMY_NUM];
	char buf[100];
	int c;
	int col = 1;
	int row = 0;

	memset(buf, 0, sizeof(buf));
	fopen_s(&fp,"data/enemyData.csv", "r");

	// �w�b�_�ǂݔ�΂�
	while (fgetc(fp) != '\n');

	while (1)
	{
		while (1)
		{
			c = fgetc(fp);

			// �����Ȃ烋�[�v�𔲂���
			if (c == EOF) 	goto out;

			// �J���}�����s�łȂ���΁A�����Ƃ��ĂȂ���
			if (c != ',' && c != '\n')
			{
				strcat_s(buf, sizeof(buf), (const char*)&c);
			}
			else
			{
				//�@�J���}�����s�Ȃ烋�[�v������
				break;
			}
		}
		// �����ɗ����Ƃ������Ƃ́A1���镪�̕����񂪏o���オ�����Ƃ�������
		switch (col)
		{
		// 1�s�ڂ̓G�l�~�[��ނ�\�� atoi�֐��Ő��l�Ƃ��đ��
		case 1: data[row].type = atoi(buf); break;
		case 2: data[row].shotType = atoi(buf); break;
		case 3: data[row].movePattern = atoi(buf); break;
		case 4: data[row].shotPattern = atoi(buf); break;
		case 5: data[row].inTime = atoi(buf); break;
		case 6: data[row].stopTime = atoi(buf); break;
		case 7: data[row].shotTime = atoi(buf); break;
		case 8: data[row].outTime = atoi(buf); break;
		case 9: data[row].x = atoi(buf); break;
		case 10: data[row].y = atoi(buf); break;
		case 11: data[row].speed = atoi(buf); break;
		case 12: data[row].hp = atoi(buf); break;
		case 13: data[row].item = atoi(buf); break;
		}
		// �o�b�t�@��������
		memset(buf, 0, sizeof(buf));
		// �񐔂𑫂�
		++col;

		// �����ǂݍ��񂾕��������s��������񐔂����������čs���𑝂₷
		if (c == '\n')
		{
			col = 1;
			++row;
		}
	}
out:

	// �G�l�~�[�N���X�̐���
	for (int i = 0; i < ENEMY_NUM; ++i)
	{
		enemy[i] = new ENEMY(data[i].type, data[i].shotType, data[i].movePattern, data[i].shotPattern, data[i].inTime, data[i].stopTime, data[i].shotTime,
			                 data[i].outTime, data[i].x, data[i].y, data[i].speed, data[i].hp, data[i].item);
	}

	// �T�E���h�t�@�C���ǂݍ���
	pShotSound = LoadSoundMem("data/se/playerShot.mp3");
	eShotSound = LoadSoundMem("data/se/enemyShot.mp3");
	bShotSound = eShotSound;
	pDeadSound = LoadSoundMem("data/se/playerDead.mp3");
	eDeadSound = LoadSoundMem("data/se/enemyDead.mp3");
	itemSound = LoadSoundMem("data/se/item.mp3");

	pShotFlag = false;
	eShotFlag = false;
	bShotFlag = false;
	pDeadFlag = false;
	eDeadFlag = false;
	itemFlag = false;
}

//-----------------------------------------------------------------------------
//  �f�X�g���N�^
//-----------------------------------------------------------------------------
Game::~Game()
{
	delete(back);

	// �v���C���[���폜.
	delete(player);

	for (int i = 0; i < ENEMY_NUM; ++i)
	{
		if (enemy[i] != NULL)
		{
			delete(enemy[i]);
		}
	}

	//�G�t�F�N�g�N���X�̃C���X�^���X���
	for (int i = 0; i < EFFECT_EDEADNUM; ++i) 
	{
		delete(effectEData[i]);
	}

	for (int i = 0; i < EFFECT_PDEADNUM; ++i)
	{
		delete(effectPData[i]);
	}

	delete(score);

	for (int i = 0; i < ITEM_NUM; ++i)
	{
		delete(item[i]);
	}

	boss.Finalize();
}

void Game::Initialize()
{
	gameCount = 0;

	PlayMusic("data/bgm/NormalBgm.mp3", DX_PLAYTYPE_BACK);
	SetVolumeMusic(255 * 50 / 100);		// BGM�̉��ʒ���

	// �w�i�N���X
	back = new BACK;

	//�v���C���[�N���X�̐���
	player = new PLAYER;

	//�G�t�F�N�g�N���X�̃C���X�^���X����
	for (int i = 0; i < EFFECT_EDEADNUM; ++i)
	{
		effectEData[i] = new EFFECT_EDEAD;
	}

	for (int i = 0; i < EFFECT_PDEADNUM; ++i)
	{
		effectPData[i] = new EFFECT_PDEAD;
	}

	// �X�R�A�N���X
	score = new SCORE;

	//�A�C�e���N���X
	for (int i = 0; i < ITEM_NUM; ++i)
	{
		item[i] = new ITEM;
	}

	FILE *fp = NULL;
	ENEMYDATA data[ENEMY_NUM];
	char buf[100];
	int c;
	int col = 1;
	int row = 0;

	memset(buf, 0, sizeof(buf));
	fopen_s(&fp, "data/enemyData.csv", "r");

	// �w�b�_�ǂݔ�΂�
	while (fgetc(fp) != '\n');

	while (1)
	{
		while (1)
		{
			c = fgetc(fp);

			// �����Ȃ烋�[�v�𔲂���
			if (c == EOF) 	goto out;

			// �J���}�����s�łȂ���΁A�����Ƃ��ĂȂ���
			if (c != ',' && c != '\n')
			{
				strcat_s(buf, sizeof(buf), (const char*)&c);
			}
			else
			{
				//�@�J���}�����s�Ȃ烋�[�v������
				break;
			}
		}
		// �����ɗ����Ƃ������Ƃ́A1���镪�̕����񂪏o���オ�����Ƃ�������
		switch (col)
		{
			// 1�s�ڂ̓G�l�~�[��ނ�\�� atoi�֐��Ő��l�Ƃ��đ��
		case 1: data[row].type = atoi(buf); break;
		case 2: data[row].shotType = atoi(buf); break;
		case 3: data[row].movePattern = atoi(buf); break;
		case 4: data[row].shotPattern = atoi(buf); break;
		case 5: data[row].inTime = atoi(buf); break;
		case 6: data[row].stopTime = atoi(buf); break;
		case 7: data[row].shotTime = atoi(buf); break;
		case 8: data[row].outTime = atoi(buf); break;
		case 9: data[row].x = atoi(buf); break;
		case 10: data[row].y = atoi(buf); break;
		case 11: data[row].speed = atoi(buf); break;
		case 12: data[row].hp = atoi(buf); break;
		case 13: data[row].item = atoi(buf); break;
		}
		// �o�b�t�@��������
		memset(buf, 0, sizeof(buf));
		// �񐔂𑫂�
		++col;

		// �����ǂݍ��񂾕��������s��������񐔂����������čs���𑝂₷
		if (c == '\n')
		{
			col = 1;
			++row;
		}
	}
out:

	// �G�l�~�[�N���X�̐���
	for (int i = 0; i < ENEMY_NUM; ++i)
	{
		enemy[i] = new ENEMY(data[i].type, data[i].shotType, data[i].movePattern, data[i].shotPattern, data[i].inTime, data[i].stopTime, data[i].shotTime,
			data[i].outTime, data[i].x, data[i].y, data[i].speed, data[i].hp, data[i].item);
	}

	boss.Initialize();

	// �T�E���h�t�@�C���ǂݍ���
	pShotSound = LoadSoundMem("data/se/playerShot.mp3");
	eShotSound = LoadSoundMem("data/se/enemyShot.mp3");
	bShotSound = eShotSound;
	pDeadSound = LoadSoundMem("data/se/playerDead.mp3");
	eDeadSound = LoadSoundMem("data/se/enemyDead.mp3");
	itemSound = LoadSoundMem("data/se/item.mp3");

	pShotFlag = false;
	eShotFlag = false;
	bShotFlag = false;
	pDeadFlag = false;
	eDeadFlag = false;
	itemFlag = false;
}

void Game::All()
{
	// �T�E���h�t���O��������
	pShotFlag = false;
	eShotFlag = false;
	bShotFlag = false;
	pDeadFlag = false;
	eDeadFlag = false;
	itemFlag = false;

	back->All();

	//�v���C���[�N���X��All�֐����s
	player->All();
	// �v���C���[�V���b�g�T�E���h�t���O�`�F�b�N
	if (player->GetShotSound())
	{
		pShotFlag = true;
	}

	if (!boss.GetFlag())
	{
		for (int i = 0; i < ENEMY_NUM; ++i)
		{
			// �C���X�^���X���܂���������Ă���Ƃ�����
			if (enemy[i] != NULL)
			{
				// �G�l�~�[�V���b�g�T�E���h�t���O���`�F�b�N
				if (enemy[i]->GetShotSound())
				{
					eShotFlag = true;
				}

				if (enemy[i]->All())
				{
					delete(enemy[i]);
					enemy[i] = NULL;
				}
			}
			else if (i >= ENEMY_NUM - 1)
			{
				if (gameCount >= 5100)
				{
					StopMusic();	// �ʏ펞��BGM���~�߂�
					BossBgm(true);	// BOSS���BGM�̃t���O�𗧂Ă�
					boss.SetFlag(true);
				}
			}
		}
		// �G�Ƃ̓����蔻��
		EnemyCollisionAll();
		// boss.SetFlag(true);
	}
	else
	{
		if (boss.GetBossFlag())
		{
			boss.All();
			// �{�X�V���b�g�T�E���h�t���O�`�F�b�N
			if (boss.GetShotSound())
			{
				eShotFlag = true;
			}
			// �{�X�Ƃ̓����蔻��
			BossCollisionAll();
		}
	}
	
	// �����蔻��
	CollisionAll();

	//�G���ŃG�t�F�N�g
	for (int i = 0; i < EFFECT_EDEADNUM; ++i)
	{
		if (effectEData[i]->GetFlag()) 
		{
			effectEData[i]->All();
		}
	}

	for (int i = 0; i < ITEM_NUM; ++i)
	{
		if (item[i]->GetFlag())
		{
			item[i]->All();
		}
	}

	SoundAll();

	score->All();

	if (player->GetLife() == 0)
	{
		StopMusic();	// �ʏ펞��BGM���~�߂�
		SceneMgr &sceneMgr = SceneMgr::GetInstance();
		sceneMgr.ChangeScene(SCENE_GAMEOVER);
	}

	++gameCount;
}

void Game::GetPlayerPosition(double *x, double *y)
{
	double tempX, tempY;
	// �w�肵���Y���̃v���C���[�̍��W���擾
	player->GetPosition(&tempX, &tempY);
	// ���
	*x = tempX;
	*y = tempY;
}
void Game::GetEnemyPosiition(int index, double *x, double *y)
{
	double tempX, tempY;
	// �w�肵���Y���̃G�l�~�[�̍��W���擾
	enemy[index]->GetPosition(&tempX, &tempY);
	// ���
	*x = tempX;
	*y = tempY;
}

void Game::GetBossPosition(double *x, double *y)
{
	double tempX, tempY;
	// �w�肵���Y���̃v���C���[�̍��W���擾
	boss.GetPosition(&tempX, &tempY);
	// ���
	*x = tempX;
	*y = tempY;
}

void Game::SoundAll()
{
	if (pShotFlag)
	{
		PlaySoundMem(pShotSound, DX_PLAYTYPE_BACK);
	}

	if (eShotFlag)
	{
		PlaySoundMem(eShotSound, DX_PLAYTYPE_BACK);
	}

	if (pDeadFlag)
	{
		PlaySoundMem(pDeadSound, DX_PLAYTYPE_BACK);
	}

	if (eDeadFlag)
	{
		PlaySoundMem(eDeadSound, DX_PLAYTYPE_BACK);
	}

	if (itemFlag)
	{
		PlaySoundMem(itemSound, DX_PLAYTYPE_BACK);
	}

}

void Game::BossBgm(bool flag)
{
	if (flag)
	{
		PlayMusic("data/bgm/BossBgm.mp3", DX_PLAYTYPE_LOOP);
		SetVolumeMusic(255 * 60 / 100);		// BGM�̉��ʒ���
	}
	else
	{
		StopMusic();	// �{�X���BGM���~�߂�
	}
}

bool Game::CircleCollision(double c1, double c2, double cx1, double cx2, double cy1, double cy2)
{
	double hLength = c1 + c2;
	double xLength = cx1 - cx2;
	double yLength = cy1 - cy2;

	if (hLength*hLength >= xLength * xLength + yLength * yLength)
	{
		return true;
	}
	else 
	{
		return false;
	}
}

void Game::CollisionAll()
{
	double px, py, ix, iy;

	//�A�C�e���ƃv���C���[�̓����蔻��
	if (!player->GetDamageFlag())
	{
		player->GetPosition(&px, &py);
		for (int i = 0; i < ITEM_NUM; ++i)
		{
			if (item[i]->GetFlag())
			{
				item[i]->GetPosition(&ix, &iy);
				if (CircleCollision(PLAYER_COLLISION, ITEM_COLLISION, px, ix, py, iy))
				{
					switch (item[i]->GetType())
					{
					case 0:
						score->SetScore(CURRENT_SCORE, 5000);
						break;
					case 1:
						player->SetPower(1);
						break;
					}
					item[i]->Delete();
					itemFlag = true;	// �A�C�e���擾���t���O�𗧂Ă�
				}
			}
		}
	}

	// ���C�t�͖���擾
	score->SetScore(LIFE_SCORE, player->GetLife());
	// �p���[�͖���擾
	score->SetScore(POWER_SCORE, player->GetPower());
}

void Game::EnemyCollisionAll()
{
	double px, py, ex, ey;

	int itemW, itemH;

	//�@�����������̃t���O
	bool hitFlag = false;

	// �v���C���[�̒e�ƃG�l�~�[�Ƃ̓����蔻��
	for (int i = 0; i < PSHOT_NUM; ++i)
	{
		if (player->GetShotPosition(i, &px, &py))
		{
			for (int j = 0; j < ENEMY_NUM; ++j)
			{
				// �G�l�~�[�N���X�̃|�C���^��NULL����Ȃ��A����deadFlag��false�̎�(����łȂ�&�A�҂��ĂȂ�)
				if (enemy[j] != NULL && !enemy[j]->GetDeadFlag())
				{
					enemy[j]->GetPosition(&ex, &ey);
					// �����蔻��
					if (CircleCollision(PSHOT_COLLISION, ENEMY_COLLISION, px, ex, py, ey))
					{
						// ���������e�̃t���O��߂�
						player->SetShotFlag(i, false);
						enemy[j]->SetHp(1);

						if (enemy[j]->GetHp() == 0)
						{
							// �������Ă���΁AdeadFlag�𗧂Ă�
							enemy[j]->SetDeadFlag();
							// �G�l�~�[���ŉ��t���O�Z�b�g
							eDeadFlag = true;
							//�G���ŃG�t�F�N�g�Z�b�g
							EnemyDeadEffect(ex, ey, enemy[j]->GetEnemyType());
							// ���_��������
							score->SetScore(CURRENT_SCORE, 1000);
							for (int k = 0; k < ITEM_NUM; ++k)
							{
								item[k]->GetSize(&itemW, &itemH);
								if (!item[k]->GetFlag())
								{
									item[k]->SetFlag(ex - itemW / 4, ey + itemH / 6, enemy[j]->GetItem());
									break;
								}
							}
						}
					}
				}
			}
		}
	}

	// �G�l�~�[�̒e�ƃv���C���[�̓����蔻��
	// �v���C���[�������Ă����
	if (!player->GetDamageFlag())
	{
		player->GetPosition(&px, &py);
		for (int i = 0; i < ENEMY_NUM; ++i)
		{
			if (enemy[i] != NULL)
			{
				for (int j = 0; j < ESHOT_NUM; ++j)
				{
					// �e�t���O�������Ă����true��Ԃ�
					if (enemy[i]->GetShotPosition(j, &ex, &ey))
					{
						// �e�ɂ���ē����蔻�肪�Ⴄ�̂�switch���ŕ���
						switch (enemy[i]->GetShotType())
						{
						case 0:
							// �������Ă����
							if (CircleCollision(PLAYER_COLLISION, ESHOT0_COLLISION, px, ex, py, ey))
							{
								hitFlag = true;
							}
							break;
						case 1:
							if (CircleCollision(PLAYER_COLLISION, ESHOT1_COLLISION, px, ex, py, ey))
							{
								hitFlag = true;
							}
							break;
						case 2:
							if (CircleCollision(PLAYER_COLLISION, ESHOT2_COLLISION, px, ex, py, ey))
							{
								hitFlag = true;
							}
							break;
						}
						if (hitFlag)
						{
							if (player->GetPlayerColor() == enemy[i]->GetEnemyType())
							{
								// �e������
								enemy[i]->SetShotFlag(j, false);
								// �ꎞ�t���O��߂�
								hitFlag = false;
							}
							else
							{
								// �v���C���[��damageFlag�𗧂Ă�
								player->SetDamageFlag();
								// �e������
								enemy[i]->SetShotFlag(j, false);
								// �v���C���[�̏��ŉ��t���O
								pDeadFlag = true;
								// �v���C���[�̃p���[�����炷
								player->SetPower(-2);
								// �ꎞ�t���O��߂�
								hitFlag = false;
							}
						}
					}
				}
			}
		}
	}

	// �v���C���[�ƃG�l�~�[�̓����蔻��
	if (!player->GetDamageFlag())
	{
		player->GetPosition(&px, &py);
		for (int i = 0; i < ENEMY_NUM; ++i)
		{
			// �G�l�~�[�N���X�̃|�C���^��NULL����Ȃ��A����deadFlag��false�̎�(����łȂ�&�A�҂��ĂȂ�)
			if (enemy[i] != NULL && !enemy[i]->GetDeadFlag())
			{
				enemy[i]->GetPosition(&ex, &ey);
				// �����蔻��
				if (CircleCollision(PSHOT_COLLISION, ENEMY_COLLISION, px, ex, py, ey))
				{
					if (player->GetPlayerColor() == enemy[i]->GetEnemyType())
					{
						// �������Ă���΁AdeadFlag�𗧂Ă�
						enemy[i]->SetDeadFlag();
						// �G�l�~�[���ŉ��t���O�Z�b�g
						eDeadFlag = true;
						//�G���ŃG�t�F�N�g�Z�b�g
						EnemyDeadEffect(ex, ey, enemy[i]->GetEnemyType());
						// ���_��������
						score->SetScore(CURRENT_SCORE, 500);
						// �v���C���[�̃p���[�𑝂₷
						player->SetPower(1);
					}
					else
					{
						// �������Ă���΁AdeadFlag�𗧂Ă�
						player->SetDamageFlag();
						// �v���C���[�̃p���[�����炷
						player->SetPower(-2);
						// �v���C���[�̏��ŉ��t���O
						pDeadFlag = true;
					}

				}
			}
		}
	}
}

void Game::BossCollisionAll()
{
	double px, py, bx, by, ix, iy;

	// �{�X�̒e�̎��
	int type;
	// �o���A�C�e���̐�
	int itemNum = 0;
	// �{�X��HP
	int bHp = 0;
	//�@�����������̃t���O
	bool hitFlag = false;

	//�܂����G�t���O�������ĂȂ������`�F�b�N�B
	if (!boss.GetNoDamageFlag()) {
		//�v���C���[�̃V���b�g�ƃ{�X�Ƃ̓����蔻��
		for (int i = 0; i < PSHOT_NUM; ++i)
		{
			if (player->GetShotPosition(i, &px, &py))
			{
				boss.GetPosition(&bx, &by);
				//�����蔻��
				if (CircleCollision(PSHOT_COLLISION, BOSS_COLLISION, px, bx, py, by))
				{
					//�������Ă���΁Ahp�����炷
					bHp = boss.SetHp(1);
					//���������e�̃t���O��߂�
					player->SetShotFlag(i, false);
					//���_��������
					score->SetScore(CURRENT_SCORE, 100);

					// �f�o�b�N�p(HP�\��)
					char buf[100];
					snprintf(buf, sizeof(buf), "%d", bHp);
					SetMainWindowText(buf);

					//�{�X�̑O��HP��HP��2/3�ȏ�ŁA��HP��2/3�ȉ��Ȃ�
   					if (BOSS_HP * 2 / 3 >= bHp && boss.GetPrevHp() > BOSS_HP * 2 / 3)
					{
						//���ŃG�t�F�N�g���o��
						EnemyDeadEffect(bx, by, 0);
						//���ŉ���炷
						// eDeadFlag = true;
						//����ɓ��_��������
						score->SetScore(CURRENT_SCORE, 1000);
						//�A�C�e�����o���B
						for (int j = 0; j < ITEM_NUM; ++j)
						{
							if (!item[j]->GetFlag())
							{
								//�A�C�e���̏������W���΂炯������B
								ix = (rand() % 100 - 51) + bx;
								iy = (rand() % 100 - 51) + by;
								item[j]->SetFlag(ix, iy, rand() % 2);
								++itemNum;
								//5�o�����烋�[�v�𔲂���
								if (itemNum == 5)
								{
									break;
								}
							}
						}
						boss.SetDamageSetting();
					}
					else if (BOSS_HP / 3 >= bHp && boss.GetPrevHp() > BOSS_HP / 3)  // �{�X�̑O��HP��HP��1/3�ȏ�ŁA��HP��1/3�ȉ��Ȃ�
					{
						//���ŃG�t�F�N�g���o��
						EnemyDeadEffect(bx, by, 0);
						//���ŉ���炷
						// eDeadFlag = true;
						//����ɓ��_��������
						score->SetScore(CURRENT_SCORE, 10000);
						//�A�C�e�����o���B
						for (int j = 0; j < ITEM_NUM; ++j)
						{
							if (!item[j]->GetFlag())
							{
								//�A�C�e���̏������W���΂炯������B
								ix = (rand() % 100 - 51) + bx;
								iy = (rand() % 100 - 51) + by;
								item[j]->SetFlag(ix, iy, rand() % 2);
								++itemNum;
								//5�o�����烋�[�v�𔲂���
								if (itemNum == 5)
								{
									break;
								}
							}
						}
						boss.SetDamageSetting();
					}
					else if(bHp <= 0)  //�����{�X��HP��0�ȉ��Ȃ�
					{
						//�t���O��߂�
						boss.SetBossFlag(false);
						//���ŃG�t�F�N�g���o��
						EnemyDeadEffect(bx, by, 0);
						//���ŉ���炷
						eDeadFlag = true;
						BossBgm(false);
						//����ɓ��_��������
						score->SetScore(CURRENT_SCORE, 100000);
						SceneMgr &sceneMgr = SceneMgr::GetInstance();
						sceneMgr.ChangeScene(SCENE_CLEAR);
						//�A�C�e�����o���B
						//for (int j = 0; j < ITEM_NUM; ++j)
						//{
						//	if (!item[j]->GetFlag())
						//	{
						//		//�A�C�e���̏������W���΂炯������B
						//		ix = (rand() % 100 - 51) + bx;
						//		iy = (rand() % 100 - 51) + by;
						//		item[j]->SetFlag(ix, iy, rand() % 2);
						//		++itemNum;
						//		//10�o�����烋�[�v�𔲂���
						//		if (itemNum == 10)
						//		{
						//			break;
						//		}
						//	}
						//}
					}
				}
			}
		}
	}

	// �{�X�̃V���b�g�ƃv���C���[�Ƃ̓����蔻��
	if (!player->GetDamageFlag())
	{
		player->GetPosition(&px, &py);
		for (int i = 0; i < BOSS_SHOTNUM; ++i)
		{
			if (boss.GetShotPosition(i, &bx, &by, &type))
			{
				switch (type)
				{
				case 0:
					// �������Ă����
					if (CircleCollision(PLAYER_COLLISION, ESHOT0_COLLISION, px, bx, py, by))
					{
						hitFlag = true;
					}
					break;
				case 1:
					if (CircleCollision(PLAYER_COLLISION, ESHOT1_COLLISION, px, bx, py, by))
					{
						hitFlag = true;
					}
					break;
				case 2:
					if (CircleCollision(PLAYER_COLLISION, ESHOT2_COLLISION, px, bx, py, by))
					{
						hitFlag = true;
					}
					break;
				}
			}

			if (hitFlag)
			{
				if (player->GetPlayerColor() == boss.GetShotColor(i))
				{
					// �e������
					boss.SetShotFlag(i, false);
					// �ꎞ�t���O�����ɖ߂�
					hitFlag = false;
				}
				else
				{
					// ����L������damageFlag�𗧂Ă�
					player->SetDamageFlag();
					// �v���C���[�̃p���[�����炷
					player->SetPower(-2);
					// �e������
					boss.SetShotFlag(i, false);
					// �v���C���[���ŉ��t���O
					pDeadFlag = true;
					// �ꎞ�t���O�����ɖ߂�
					hitFlag = false;
					// ��ł��������Ă�����v���C���[�͏��ł���̂�
					// ���̒e���`�F�b�N����K�v�Ȃ��̂Ń��[�v�𔲂���
					break;
				}
			}
		}
	}
}

void Game::EnemyDeadEffect(double x, double y, int index)
{
	//�G�t�F�N�g�Z�b�g
	for (int i = 0; i < EFFECT_EDEADNUM; ++i)
	{
		if (!effectEData[i]->GetFlag())
		{
			effectEData[i]->SetFlag(x, y, index);
			break;
		}
	}
}