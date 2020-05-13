//-----------------------------------------------------------------------------
// ゲームの処理.
//-----------------------------------------------------------------------------
#include "Game.h"
#include "define.h"

//-----------------------------------------------------------------------------
// コンストラクタ
//-----------------------------------------------------------------------------
Game::Game()
{
	// 背景クラス
	back = new BACK;

	//プレイヤークラスの生成
	player = new PLAYER;

	//エフェクトクラスのインスタンス生成
	for (int i = 0; i<EFFECT_EDEADNUM; ++i) 
	{
		 effectEData[i] = new EFFECT_EDEAD;
	}

	// スコアクラス
	score = new SCORE;

	FILE *fp = NULL;
	ENEMYDATA data[ENEMY_NUM];
	char buf[100];
	int c;
	int col = 1;
	int row = 0;

	memset(buf, 0, sizeof(buf));
	fopen_s(&fp,"data/enemyData.csv", "r");

	// ヘッダ読み飛ばし
	while (fgetc(fp) != '\n');

	while (1)
	{
		while (1)
		{
			c = fgetc(fp);

			// 末尾ならループを抜ける
			if (c == EOF) 	goto out;

			// カンマが改行でなければ、文字としてつなげる
			if (c != ',' && c != '\n')
			{
				strcat_s(buf, sizeof(buf), (const char*)&c);
			}
			else
			{
				//　カンマが改行ならループ抜ける
				break;
			}
		}
		// ここに来たということは、1是る分の文字列が出来上がったということ
		switch (col)
		{
		// 1行目はエネミー種類を表す atoi関数で数値として代入
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
		// バッファを初期化
		memset(buf, 0, sizeof(buf));
		// 列数を足す
		++col;

		// もし読み込んだ文字が改行だったら列数を初期化して行数を増やす
		if (c == '\n')
		{
			col = 1;
			++row;
		}
	}
out:

	// エネミークラスの生成
	for (int i = 0; i < ENEMY_NUM; ++i)
	{
		enemy[i] = new ENEMY(data[i].type, data[i].shotType, data[i].movePattern, data[i].shotPattern, data[i].inTime, data[i].stopTime, data[i].shotTime,
			                 data[i].outTime, data[i].x, data[i].y, data[i].speed, data[i].hp, data[i].item);
	}

	// サウンドファイル読み込み
	soundPShot = LoadSoundMem("data/se/playerShot.mp3");
	soundEShot = LoadSoundMem("data/se/enemyShot.mp3");
	soundPDead = LoadSoundMem("data/se/playerDead.mp3");
	soundEDead = LoadSoundMem("data/se/enemyDead.mp3");

	pShotFlag = false;
	eShotFlag = false;
	pDeadFlag = false;
	eDeadFlag = false;
}

//-----------------------------------------------------------------------------
//  デストラクタ
//-----------------------------------------------------------------------------
Game::~Game()
{
	delete(back);

	// プレイヤーを削除.
	delete(player);

	for (int i = 0; i < ENEMY_NUM; ++i)
	{
		if (enemy[i] != NULL)
		{
			delete(enemy[i]);
		}
	}

	//エフェクトクラスのインスタンス解放
	for (int i = 0; i < EFFECT_EDEADNUM; ++i) 
	{
		delete effectEData[i];
	}

	delete(score);
}

void Game::All()
{
	// サウンドフラグを初期化
	pShotFlag = false;
	eShotFlag = false;
	pDeadFlag = false;
	eDeadFlag = false;

	back->All();

	//プレイヤークラスのAll関数実行
	player->All();
	// プレイヤーショットサウンドフラグチェック
	if (player->GetShotSound())
	{
		pShotFlag = true;
	}

	for (int i = 0; i < ENEMY_NUM; ++i) 
	{
		// インスタンスがまだ生成されているときだけ
		if (enemy[i] != NULL)
		{
			// エネミーショットサウンドフラグをチェック
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
	}

	// 当たり判定
	CollisionAll();

	//敵消滅エフェクト
	for (int i = 0; i<EFFECT_EDEADNUM; ++i)
	{
		if (effectEData[i]->GetFlag()) 
		{
			effectEData[i]->All();
		}
	}

	SoundAll();

	score->All();

	++gameCount;
}

void Game::GetPlayerPosition(double *x, double *y)
{
	double tempX, tempY;
	// 指定した添字のプレイヤーの座標を取得
	player->GetPosition(&tempX, &tempY);
	// 代入
	*x = tempX;
	*y = tempY;
}
void Game::GetEnemyPosiition(int index, double *x, double *y)
{
	double tempX, tempY;
	// 指定した添字のエネミーの座標を取得
	enemy[index]->GetPosition(&tempX, &tempY);
	// 代入
	*x = tempX;
	*y = tempY;
}

void Game::SoundAll()
{
	if (pShotFlag)
	{
		PlaySoundMem(soundPShot, DX_PLAYTYPE_BACK);
	}

	if (eShotFlag)
	{
		PlaySoundMem(soundEShot, DX_PLAYTYPE_BACK);
	}

	if (pDeadFlag)
	{
		PlaySoundMem(soundPDead, DX_PLAYTYPE_BACK);
	}

	if (eDeadFlag)
	{
		PlaySoundMem(soundEDead, DX_PLAYTYPE_BACK);
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
	double px, py, ex, ey;

	int playerColor = 0;
	int	enemyType = 0;

	bool tempFlag = false;

	// プレイヤーの弾とエネミーとの当たり判定
	for (int i = 0; i < PSHOT_NUM; ++i)
	{
		if (player->GetShotPosition(i, &px, &py))
		{		
			for (int j = 0; j < ENEMY_NUM; ++j)
			{
				// エネミークラスのポインタがNULLじゃない、かつdeadFlagがfalseの時(死んでない&帰還してない)
				if (enemy[j] != NULL && !enemy[j]->GetDeadFlag())
				{
					enemy[j]->GetPosition(&ex, &ey);
					// 当たり判定
					if (CircleCollision(PSHOT_COLLISION, ENEMY_COLLISION, px, ex, py, ey))
					{
						// プレイヤーの色とエネミーの色が同じときダメージがなし
						if (player->GetPlayerColor() == enemy[j]->GetEnemyType())
						{
							// 当たった弾のフラグを戻す
          					player->SetShotFlag(i, false);
						}
						else
						{
							// 当たっていれば、deadFlagを立てる
							enemy[j]->SetDeadFlag();
							// エネミー消滅音フラグセット
							eDeadFlag = true;
							//敵消滅エフェクトセット
							EnemyDeadEffect(ex, ey, enemy[j]->GetEnemyType());
							// 当たった弾のフラグを戻す
							player->SetShotFlag(i, false);
							// 得点を加える
							score->SetScore(CURRENT_SCORE, 100);
						}
					}
				}
			}
		}
	}

	// エネミーの弾とプレイヤーの当たり判定
	// プレイヤーが生きていれば
	if (!player->GetDamageFlag())
	{
		player->GetPosition(&px, &py);
		for (int i = 0; i < ENEMY_NUM; ++i)
		{
			if (enemy[i] != NULL)
			{
				for (int j = 0; j < ESHOT_NUM; ++j)
				{
					// 弾フラグが立っていればtrueを返す
					if (enemy[i]->GetShotPosition(j, &ex, &ey))
					{
						// 弾によって当たり判定が違うのでswitch文で分岐
						switch (enemy[i]->GetShotType())
						{
						case 0:
							// 当たっていれば
							if (CircleCollision(PLAYER_COLLISION, ESHOT0_COLLISION, px, ex, py, ey))
							{
								tempFlag = true;
							}
							break;
						case 1:
							if (CircleCollision(PLAYER_COLLISION, ESHOT1_COLLISION, px, ex, py, ey))
							{
								tempFlag = true;
							}
							break;
						case 2:
							if (CircleCollision(PLAYER_COLLISION, ESHOT2_COLLISION, px, ex, py, ey))
							{
								tempFlag = true;
							}
							break;
						}
						if (tempFlag)
						{
							if (player->GetPlayerColor() == enemy[i]->GetEnemyType())
							{
								// 弾を消す
								enemy[i]->SetShotFlag(j, false);
								// 一時フラグを戻す
								tempFlag = false;
							}
							else
							{
								// プレイヤーのdamageFlagを立てる
								player->SetDamageFlag();
								// 弾を消す
								enemy[i]->SetShotFlag(j, false);
								// プレイヤーの消滅音フラグ
								pDeadFlag = true;
								// 一時フラグを戻す
								tempFlag = false;
							}
						}
					}
				}
			}
		}
	}

	// プレイヤーとエネミーの当たり判定
	if (!player->GetDamageFlag())
	{
		player->GetPosition(&px, &py);
		for (int i = 0; i < ENEMY_NUM; ++i)
		{
			// エネミークラスのポインタがNULLじゃない、かつdeadFlagがfalseの時(死んでない&帰還してない)
			if (enemy[i] != NULL && !enemy[i]->GetDeadFlag())
			{
				enemy[i]->GetPosition(&ex, &ey);
				// 当たり判定
				if (CircleCollision(PSHOT_COLLISION, ENEMY_COLLISION, px, ex, py, ey))
				{
					if (player->GetPlayerColor() == enemy[i]->GetEnemyType())
					{
						// 当たっていれば、deadFlagを立てる
						enemy[i]->SetDeadFlag();
						// エネミー消滅音フラグセット
						eDeadFlag = true;
						//敵消滅エフェクトセット
						EnemyDeadEffect(ex, ey, enemy[i]->GetEnemyType());
						// 得点を加える
						score->SetScore(CURRENT_SCORE, 500);
					}
					else
					{
						// 当たっていれば、deadFlagを立てる
						player->SetDamageFlag();
						// プレイヤーの消滅音フラグ
						pDeadFlag = true;
					}

				}
			}
		}
	}

	// ライフは毎回取得
	score->SetScore(LIFE_SCORE, player->GetLife());
}

void Game::EnemyDeadEffect(double x, double y, int index)
{
	//エフェクトセット
	for (int i = 0; i < EFFECT_EDEADNUM; ++i)
	{
		if (!effectEData[i]->GetFlag())
		{
			effectEData[i]->SetFlag(x, y, index);
			break;
		}
	}
}
