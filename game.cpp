//-----------------------------------------------------------------------------
// ゲームの処理.
//-----------------------------------------------------------------------------
#include "Game.h"
#include "define.h"
#include "sceneMgr.h"

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
	for (int i = 0; i < EFFECT_EDEADNUM; ++i) 
	{
		 effectEData[i] = new EFFECT_EDEAD;
	}

	for (int i = 0; i < EFFECT_PDEADNUM; ++i)
	{
		effectPData[i] = new EFFECT_PDEAD;
	}

	// スコアクラス
	score = new SCORE;

	//アイテムクラス
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
	SetVolumeMusic(255 * 50 / 100);		// BGMの音量調整

	// 背景クラス
	back = new BACK;

	//プレイヤークラスの生成
	player = new PLAYER;

	//エフェクトクラスのインスタンス生成
	for (int i = 0; i < EFFECT_EDEADNUM; ++i)
	{
		effectEData[i] = new EFFECT_EDEAD;
	}

	for (int i = 0; i < EFFECT_PDEADNUM; ++i)
	{
		effectPData[i] = new EFFECT_PDEAD;
	}

	// スコアクラス
	score = new SCORE;

	//アイテムクラス
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

	boss.Initialize();

	// サウンドファイル読み込み
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
	// サウンドフラグを初期化
	pShotFlag = false;
	eShotFlag = false;
	bShotFlag = false;
	pDeadFlag = false;
	eDeadFlag = false;
	itemFlag = false;

	back->All();

	//プレイヤークラスのAll関数実行
	player->All();
	// プレイヤーショットサウンドフラグチェック
	if (player->GetShotSound())
	{
		pShotFlag = true;
	}

	if (!boss.GetFlag())
	{
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
			else if (i >= ENEMY_NUM - 1)
			{
				if (gameCount >= 5100)
				{
					StopMusic();	// 通常時のBGMを止める
					BossBgm(true);	// BOSS戦のBGMのフラグを立てる
					boss.SetFlag(true);
				}
			}
		}
		// 敵との当たり判定
		EnemyCollisionAll();
		// boss.SetFlag(true);
	}
	else
	{
		if (boss.GetBossFlag())
		{
			boss.All();
			// ボスショットサウンドフラグチェック
			if (boss.GetShotSound())
			{
				eShotFlag = true;
			}
			// ボスとの当たり判定
			BossCollisionAll();
		}
	}
	
	// 当たり判定
	CollisionAll();

	//敵消滅エフェクト
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
		StopMusic();	// 通常時のBGMを止める
		SceneMgr &sceneMgr = SceneMgr::GetInstance();
		sceneMgr.ChangeScene(SCENE_GAMEOVER);
	}

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

void Game::GetBossPosition(double *x, double *y)
{
	double tempX, tempY;
	// 指定した添字のプレイヤーの座標を取得
	boss.GetPosition(&tempX, &tempY);
	// 代入
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
		SetVolumeMusic(255 * 60 / 100);		// BGMの音量調整
	}
	else
	{
		StopMusic();	// ボス戦のBGMを止める
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

	//アイテムとプレイヤーの当たり判定
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
					itemFlag = true;	// アイテム取得音フラグを立てる
				}
			}
		}
	}

	// ライフは毎回取得
	score->SetScore(LIFE_SCORE, player->GetLife());
	// パワーは毎回取得
	score->SetScore(POWER_SCORE, player->GetPower());
}

void Game::EnemyCollisionAll()
{
	double px, py, ex, ey;

	int itemW, itemH;

	//　当たった時のフラグ
	bool hitFlag = false;

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
						// 当たった弾のフラグを戻す
						player->SetShotFlag(i, false);
						enemy[j]->SetHp(1);

						if (enemy[j]->GetHp() == 0)
						{
							// 当たっていれば、deadFlagを立てる
							enemy[j]->SetDeadFlag();
							// エネミー消滅音フラグセット
							eDeadFlag = true;
							//敵消滅エフェクトセット
							EnemyDeadEffect(ex, ey, enemy[j]->GetEnemyType());
							// 得点を加える
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
								// 弾を消す
								enemy[i]->SetShotFlag(j, false);
								// 一時フラグを戻す
								hitFlag = false;
							}
							else
							{
								// プレイヤーのdamageFlagを立てる
								player->SetDamageFlag();
								// 弾を消す
								enemy[i]->SetShotFlag(j, false);
								// プレイヤーの消滅音フラグ
								pDeadFlag = true;
								// プレイヤーのパワーを減らす
								player->SetPower(-2);
								// 一時フラグを戻す
								hitFlag = false;
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
						// プレイヤーのパワーを増やす
						player->SetPower(1);
					}
					else
					{
						// 当たっていれば、deadFlagを立てる
						player->SetDamageFlag();
						// プレイヤーのパワーを減らす
						player->SetPower(-2);
						// プレイヤーの消滅音フラグ
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

	// ボスの弾の種類
	int type;
	// 出すアイテムの数
	int itemNum = 0;
	// ボスのHP
	int bHp = 0;
	//　当たった時のフラグ
	bool hitFlag = false;

	//まず無敵フラグがたってないかをチェック。
	if (!boss.GetNoDamageFlag()) {
		//プレイヤーのショットとボスとの当たり判定
		for (int i = 0; i < PSHOT_NUM; ++i)
		{
			if (player->GetShotPosition(i, &px, &py))
			{
				boss.GetPosition(&bx, &by);
				//当たり判定
				if (CircleCollision(PSHOT_COLLISION, BOSS_COLLISION, px, bx, py, by))
				{
					//当たっていれば、hpを減らす
					bHp = boss.SetHp(1);
					//当たった弾のフラグを戻す
					player->SetShotFlag(i, false);
					//得点を加える
					score->SetScore(CURRENT_SCORE, 100);

					// デバック用(HP表示)
					char buf[100];
					snprintf(buf, sizeof(buf), "%d", bHp);
					SetMainWindowText(buf);

					//ボスの前回HPがHPの2/3以上で、現HPが2/3以下なら
   					if (BOSS_HP * 2 / 3 >= bHp && boss.GetPrevHp() > BOSS_HP * 2 / 3)
					{
						//消滅エフェクトを出す
						EnemyDeadEffect(bx, by, 0);
						//消滅音を鳴らす
						// eDeadFlag = true;
						//さらに得点を加える
						score->SetScore(CURRENT_SCORE, 1000);
						//アイテムを出す。
						for (int j = 0; j < ITEM_NUM; ++j)
						{
							if (!item[j]->GetFlag())
							{
								//アイテムの初期座標をばらけさせる。
								ix = (rand() % 100 - 51) + bx;
								iy = (rand() % 100 - 51) + by;
								item[j]->SetFlag(ix, iy, rand() % 2);
								++itemNum;
								//5個出したらループを抜ける
								if (itemNum == 5)
								{
									break;
								}
							}
						}
						boss.SetDamageSetting();
					}
					else if (BOSS_HP / 3 >= bHp && boss.GetPrevHp() > BOSS_HP / 3)  // ボスの前回HPがHPの1/3以上で、現HPが1/3以下なら
					{
						//消滅エフェクトを出す
						EnemyDeadEffect(bx, by, 0);
						//消滅音を鳴らす
						// eDeadFlag = true;
						//さらに得点を加える
						score->SetScore(CURRENT_SCORE, 10000);
						//アイテムを出す。
						for (int j = 0; j < ITEM_NUM; ++j)
						{
							if (!item[j]->GetFlag())
							{
								//アイテムの初期座標をばらけさせる。
								ix = (rand() % 100 - 51) + bx;
								iy = (rand() % 100 - 51) + by;
								item[j]->SetFlag(ix, iy, rand() % 2);
								++itemNum;
								//5個出したらループを抜ける
								if (itemNum == 5)
								{
									break;
								}
							}
						}
						boss.SetDamageSetting();
					}
					else if(bHp <= 0)  //もしボスのHPが0以下なら
					{
						//フラグを戻す
						boss.SetBossFlag(false);
						//消滅エフェクトを出す
						EnemyDeadEffect(bx, by, 0);
						//消滅音を鳴らす
						eDeadFlag = true;
						BossBgm(false);
						//さらに得点を加える
						score->SetScore(CURRENT_SCORE, 100000);
						SceneMgr &sceneMgr = SceneMgr::GetInstance();
						sceneMgr.ChangeScene(SCENE_CLEAR);
						//アイテムを出す。
						//for (int j = 0; j < ITEM_NUM; ++j)
						//{
						//	if (!item[j]->GetFlag())
						//	{
						//		//アイテムの初期座標をばらけさせる。
						//		ix = (rand() % 100 - 51) + bx;
						//		iy = (rand() % 100 - 51) + by;
						//		item[j]->SetFlag(ix, iy, rand() % 2);
						//		++itemNum;
						//		//10個出したらループを抜ける
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

	// ボスのショットとプレイヤーとの当たり判定
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
					// 当たっていれば
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
					// 弾を消す
					boss.SetShotFlag(i, false);
					// 一時フラグを元に戻す
					hitFlag = false;
				}
				else
				{
					// 操作キャラのdamageFlagを立てる
					player->SetDamageFlag();
					// プレイヤーのパワーを減らす
					player->SetPower(-2);
					// 弾を消す
					boss.SetShotFlag(i, false);
					// プレイヤー消滅音フラグ
					pDeadFlag = true;
					// 一時フラグを元に戻す
					hitFlag = false;
					// 一つでも当たっていたらプレイヤーは消滅するので
					// 他の弾をチェックする必要ないのでループを抜ける
					break;
				}
			}
		}
	}
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