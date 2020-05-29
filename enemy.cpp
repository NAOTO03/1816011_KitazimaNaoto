// ------ エネミー ------

#include "DxLib.h"
#include "math.h"
#include "Game.h"
#include "define.h"
#include "enemy.h"

// エネミーを初期化する
ENEMY::ENEMY(int type, int shotType, int movePattern, int shotPattern, int inTime, int stopTime, int shotTime, int outTime,
	         int x, int y, int speed, int hp, int item)
{
	//-------------------------------
	// ---------- エネミー ----------
	//-------------------------------

	// 読み込み
	switch (type)
	{
	case 0:
		graph = LoadGraph("data/png/Enemy/BlackEnemy.png");
		break;
	case 1:
		graph = LoadGraph("data/png/Enemy/WhiteEnemy.png");
		break;
	}

	// サイズ
	width = 24;
	height = 24;

	this->type = type;	       // エネミーの種類
	this->shotType = shotType; // 弾の種類
	
	// 移動パターンとショットパターン
	this->movePattern = movePattern;
	this->shotPattern = shotPattern;

	// 座標セット
	this->enemyX = x;
	this->enemyY = y;

	// 出現　停止　発射　帰還時間セット
	this->inTime = inTime;
	this->stopTime = stopTime;
	this->shotTime = shotTime;
	this->outTime = outTime;

	this->item = item;

	rad = 0;
	shotNum = 0;
	count = 0;		// エネミーが出現してからのカウント
	shotCount = 0;	// ショットが撃てるようになってからのカウント

	deadFlag = false;  // エネミー消滅フラグ
	endFlag = false;   // エネミークラス消滅フラグ
	shotFlag = false;  // ショットが撃てるようになったかのフラグ
	shotSound = false; // ショット音が鳴ったかどうかを示すフラグ 

	// 弾の画像とサイズを取得
	// int shotGraph = NULL;
	switch (shotType)
	{
	case 0:
		if (type == 0)
		{
			shotGraph = LoadGraph("data/png/EShot/BlackShot1.png");
		}
		else if(type == 1)
		{
			shotGraph = LoadGraph("data/png/EShot/WhiteShot1.png");
		}
		break;
	case 1:
		if (type == 0)
		{
			shotGraph = LoadGraph("data/png/EShot/BlackShot2.png");
		}
		else if (type == 1)
		{
			shotGraph = LoadGraph("data/png/EShot/WhiteShot2.png");
		}
		break;
	case 2:
		if (type == 0)
		{
			shotGraph = LoadGraph("data/png/EShot/BlackShot3.png");
		}
		else if (type == 1)
		{
			shotGraph = LoadGraph("data/png/EShot/WhiteShot3.png");
		}
		break;
	}

	int w, h;
	GetGraphSize(shotGraph, &w, &h);

	// 弾の初期化
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

// エネミーの更新
void ENEMY::Update()
{
	// まだ生きてるか画面内にいるときだけ処理
	if (!deadFlag)
	{
		switch (movePattern)
		{
			// 途中で止まって、そのまま後ろに帰るパターン
		case 0:
			// 出てきてから止まる時間までの間なら下に移動
			if (inTime < gameCount && gameCount < stopTime)
			{
				enemyY += 2;
			}
			else if (gameCount > outTime)	//帰還時間を過ぎたら戻る。
			{
				enemyY -= 2;
			}
			break;
		
		// 途中で止まって、下に行くパターン
		case 1:
			if (inTime < gameCount && gameCount < stopTime)
			{
				enemyY += 2;
			}
			else if (gameCount > outTime)
			{
				enemyY += 2;
			}
			break;
		// ちょっとずつ左に移動しながら消えていく
		case 2:
			if (inTime <= gameCount)
			{
				enemyY += 1;
				if (count % 10 == 0)
				{ 
					enemyX -= 2;
				}
			}
			break;
		// ちょっとずつ右に移動しながら消えていく
		case 3:
			if (inTime <= gameCount)
			{
				enemyY += 1;
				if (count % 10 == 0)
				{
					enemyX += 2;
				}
			}
			break;
		}
		// 画面からはみ出したら、deadFlag(はみ出すか死ぬかのフラグ)をtrueにする
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
	// Gameクラスの参照
	Game &game = Game::GetInstance();
	double px, py;

	// 発射タイミングになったら、フラグを立てる
	if (shotTime == gameCount)
	{
		shotFlag = true;
	}

	// フラグが立っているときだけ
	if (shotFlag)
	{
		// ショット音フラグを戻す
		shotSound = false;

		// エネミーが生きているときだけ
		if (!deadFlag)
		{
			// プレイヤーの位置取得
			game.GetPlayerPosition(&px, &py);

			// エネミーとプレイヤー都の座標から逆位置を求める
			// 初回だけ実行
			if (shotCount == 0)
			{
				rad = atan2(py - (enemyY + height / 2), px - (enemyX + width / 2));
			}


			switch (shotPattern)
			{
				// 前方にショット
			case 0:
				// 5ループに1回発射 20までなので5発発射
				if (shotCount % 5 == 0 && shotCount <= 20)
				{
					for (int i = 0; i < ESHOT_NUM; ++i)
					{
						// フラグが立っていない弾を探して、座標等をセット
						if (shot[i].flag == false)
						{
							shot[i].flag = true;
							shot[i].x = enemyX + shot[i].width / 2;
							shot[i].y = enemyY + shot[i].height / 2;
							shot[i].rad = rad;
							break;
						}
					}
					// ショットサウンドフラグを立てる
					shotSound = true;
				}
				break;
				// プレイヤーに向かって直線ショット
			case 1:
				// 6ループに1回発射 54までなので10発発射
				if (shotCount % 6 == 0 && shotCount <= 54)
				{
					for (int i = 0; i < ESHOT_NUM; ++i)
					{
						// フラグが立っていない弾を探して、座標等をセット
						if (shot[i].flag == false)
						{
							shot[i].flag = true;
							shot[i].x = enemyX + shot[i].width + shot[i].width * 2 / 3;
							shot[i].y = enemyY + shot[i].height / 2;
							shot[i].rad = rad;
							break;
						}
					}
					// ショットサウンドフラグを立てる
					shotSound = true;
				}
				break;
				// 3方向直線ショット
			case 2:
				// 10ループに1回発射　1ループに3発なので5ループさせると15発発射
				if (shotCount % 10 == 0 && shotCount <= 40)
				{
					for (int i = 0; i < ESHOT_NUM; ++i)
					{
						// フラグが立っていない弾を探して、座標等をセット
						if (shot[i].flag == false)
						{
							shot[i].flag = true;
							shot[i].x = enemyX + shot[i].width + shot[i].width * 2 / 3;
							shot[i].y = enemyY + shot[i].height / 2;
							// 0の時は左より
							if (shotNum == 0)
							{
								// エネミーとプレイヤーとの逆正接から10度引いたラジアンを代入
								shot[i].rad = rad - (10 * DX_PI / 180);	// DX_PI 3.14
							}
							else if (shotNum == 1)	// 1の時はプレイヤーに一直線
							{
								// エネミーとプレイヤーとの逆正接を代入
								shot[i].rad = rad;
							}
							else if (shotNum == 2)	// 2の時は右より
							{
								// エネミープレイヤーとの逆正接から10度足したラジアンを代入
								shot[i].rad = rad + (10 * DX_PI / 180);
							}
							++shotNum;

							// 3発発射したら shotNumを0にループして抜ける
							if (shotNum == 3)
							{
								shotNum = 0;
								break;
							}
						}
					}
					// ショットサウンドフラグを立てる
					shotSound = true;
				}
				break;
				// 乱射ショット
			case 3:
				//2ループに一回発射。98までなので50発発射。
				if (shotCount % 2 == 0 && shotCount <= 98)
				{
					for (int i = 0; i < ESHOT_NUM; ++i)
					{
						// フラグが立っていない弾を探して、座標等をセット
						if (shot[i].flag == false)
						{
							shot[i].flag = true;
							shot[i].x = enemyX + shot[i].width;
							shot[i].y = enemyY + shot[i].height * 2;
							// 初回だけ乱数初期化
							if (shotNum == 0)
							{
								srand((unsigned int)time(NULL));
							}
							shot[i].rad = atan2(py - enemyY, px - enemyX) - (60 * DX_PI / 180) + ((rand() % 120) * DX_PI / 180);
							++shotNum;
							break;
						}
					}
					// ショットサウンドフラグを立てる
					shotSound = true;
				}
				break;
				// 全方位弾
			case 4:
				if (shotCount % 60 == 0)
				{
					for (int i = 0; i < ESHOT_NUM; ++i)
					{
						// フラグが立っていない弾を探して、座標等をセット
						if (shot[i].flag == false)
						{
							shot[i].flag = true;
							shot[i].x = enemyX + shot[i].width / 2;
							shot[i].y = enemyY + shot[i].height / 2;
							shot[i].rad = ((360 / 30) * DX_PI / 180) * shotNum + ((shotCount / 15) * 0.08);

							++shotNum;

							if (shotNum == 30)
							{
								break;
							}
							// ショットサウンドフラグを立てる
							shotSound = true;
						}
					}
				}
				break;
				// うずまき弾
			case 5:
				// shotCountが60以下までなので60発発射
				if (shotCount <= 60)
				{
					for (int i = 0; i < ESHOT_NUM; ++i)
					{
						// フラグが立っていない弾を探して、座標等をセット
						if (shot[i].flag == false)
						{
							shot[i].flag = true;
							shot[i].x = enemyX + shot[i].width / 2;
							shot[i].y = enemyY + shot[i].height / 2;
							shot[i].rad = ((360 / 60) * DX_PI / 180) * shotNum + ((shotCount / 15) * 0.08);

							++shotNum;
							// ショットサウンドフラグを立てる
							shotSound = true;
							break;
						}
					}
				}
				break;
				// ワインダー(3方向の弾幕の檻)
			case 6:
				if (shotCount % 3 == 0)
				{
					for (int i = 0; i < ESHOT_NUM; ++i)
					{
						// フラグが立っていない弾を探して、座標等をセット
						if (shot[i].flag == false)
						{
							shot[i].flag = true;
							shot[i].x = enemyX + shot[i].width + shot[i].width * 2 / 3;
							shot[i].y = enemyY + shot[i].height / 2;
							rad = atan2(py - (enemyY + height / 2), px - (enemyX + width / 2));	// プレイヤーの両側30度までの範囲内でランダム

							// 0の時は左より
							if (shotNum == 0)
							{
								// エネミーとプレイヤーとの逆正接から10度引いたラジアンを代入
								shot[i].rad = rad - (30 * DX_PI / 180);	// DX_PI 3.14
							}
							else if (shotNum == 1)	// 1の時はプレイヤーに一直線
							{
								// エネミーとプレイヤーとの逆正接を代入
								shot[i].rad = rad;
							}
							else if (shotNum == 2)	// 2の時は右より
							{
								// エネミープレイヤーとの逆正接から10度足したラジアンを代入
								shot[i].rad = rad + (30 * DX_PI / 180);
							}
							++shotNum;

							// 3発発射したら shotNumを0にループして抜ける
							if (shotNum == 3)
							{
								shotNum = 0;
								break;
							}
						}
					}
					// ショットサウンドフラグを立てる
					shotSound = true;
				}
				break;
			}
		}	

		// フラグが立っている弾の数
		int flagNum = 0;

		//フラグの立っている弾だけ、弾の移動を行う
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
				case 2:
				case 3:
				case 4:
				case 5:
				case 6:
					shot[i].x += shot[i].speed * cos(shot[i].rad);
					shot[i].y += shot[i].speed * sin(shot[i].rad);
					break;
				}

				// 弾が画面にはみ出たらフラグを戻す
				if (ShotOutCheck(i))
				{
					shot[i].flag = false;
					continue;
				}
				++flagNum;
			}
		}

		// flagNumが0ということは発射中の弾がない
		// かつdeadFlagがtrueということはこのエネミーのクラスは消滅させてもいい
		if (flagNum == 0 && deadFlag)
		{
			// エネミークラス消滅フラグをtrueにする
			endFlag = true;
		}

		++shotCount;
	}

}

void ENEMY::Draw()
{
	// 弾から最初描画
	for (int i = 0; i < ESHOT_NUM; ++i)
	{
		if (shot[i].flag)
		{
			if (shotType == 0 || shotType == 2)
			{
				DrawGraph(shot[i].x, shot[i].y, shot[i].graph, TRUE);
				// DrawCircle(shot[i].x + shot[i].width / 2, shot[i].y + shot[i].height / 2, 3, 0xff0000, true);
			}
			else
			{
				DrawRotaGraph(shot[i].x, shot[i].y, 1.0, shot[i].rad + (90 * DX_PI / 180), shot[i].graph, TRUE);
				// DrawCircle(shot[i].x, shot[i].y, 4, 0xff0000, true);
			}
		}
	}

	if (!deadFlag)
	{
		DrawGraph(enemyX, enemyY, graph, TRUE);
		// DrawCircle(enemyX + width / 2, enemyY + height / 2, 12, 0xff0000, true);
	}
}

bool ENEMY::OutCheck()
{
	// エネミーが画面から出たらフラグをtrueにする
	if (enemyX < -50 || enemyX > 680 || enemyY < -50 || enemyY > 640)
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
	// 弾が画面にはみ出たらフラグを戻す
	if (shot[i].x < -40 || shot[i].x > 640 || shot[i].y < -40 || shot[i].y > 600)
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
	return shotSound;
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