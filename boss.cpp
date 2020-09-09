#include <DxLib.h>
#include <math.h>
#include <time.h>
#include "define.h"
#include "Game.h"
#include "boss.h"

void BOSS::Initialize()
{
	x = 320;
	y = -100;
	prevX = 320;
	prevY = -100;

	graph = LoadGraph("data/png/Boss/boss.png");
	blackShot[0] = LoadGraph("data/png/EShot/BlackShot1.png");
	blackShot[1] = LoadGraph("data/png/EShot/BlackShot2.png");
	blackShot[2] = LoadGraph("data/png/EShot/BlackShot3.png");
	whiteShot[0] = LoadGraph("data/png/EShot/WhiteShot1.png");
	whiteShot[1] = LoadGraph("data/png/EShot/WhiteShot2.png");
	whiteShot[2] = LoadGraph("data/png/EShot/WhiteShot3.png");

	GetGraphSize(graph, &width, &height);

	for (int i = 0; i < BOSS_SHOTNUM; ++i)
	{
		shot[i].flag = false;
		shot[i].graph = 0;
		shot[i].pattern = 0;
		shot[i].rad = 0;
		shot[i].speed = 0;
		shot[i].x = 0;
		shot[i].y = 0;
		shot[i].color = 0;
	}

	raise = 2;
	raise2 = 2;
	angle = 0;
	movePattern = 0;
	shotPattern = 0;
	moveX = 0;
	moveY = 220;
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
	bossFlag = true;
	shotFlag = false;
	shotSound = false;
}

void BOSS::Finalize()
{
	DeleteGraph(graph);
	DeleteGraph(blackShot[0]);
	DeleteGraph(blackShot[1]);
	DeleteGraph(blackShot[2]);
	DeleteGraph(whiteShot[0]);
	DeleteGraph(whiteShot[1]);
	DeleteGraph(whiteShot[2]);
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

	// 定位置まで移動したら移動パターンを変更
	if (angle == 90)
	{
		movePattern = 1;
		angle = 0;
		shotFlag = true;
	}
}

// ふわふわ上下移動
void BOSS::MovePattern1()
{
	angle += raise;

	y = 120 + sin(angle * DX_PI / 180) * BOSS_SHAKE;

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

// 単純な横移動
void BOSS::MovePattern2()
{
	if (!wait)
	{
		x += raise2;

		if (x == 80)
		{
			raise2 = 2;
			wait = true;
		}
		else if (x == 540)
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

// 三角形を描くように移動
void BOSS::MovePattern3()
{
	double temp;

	angle += 1;

	temp = sin(angle * DX_PI / 180);

	x = prevX + temp * moveX;
	y = prevY + temp * moveY;

	if (angle == 90)
	{
		if (state == 0)
		{
			MoveInit(80, 120, 1);
		}
		else if (state == 1)
		{
			MoveInit(320, 240, 2);
		}
		else if (state == 2)
		{
			MoveInit(540, 120, 0);
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

	// 指定した位置まで移動したら
	if (angle == 90) 
	{
		// 次の移動＆ショットパターンに変更
		SetMovePattern(prevMovePattern + 1);
		SetShotPattern(prevShotPattern + 1);
		//無敵フラグを戻す
		noDamageFlag = false;

		// 移動パターンが３なら
		if (movePattern == 3)
		{
			MoveInit(320, 240, 2);
		}
	}

}

void BOSS::SetMovePattern(int pattern)
{
	// 前回の移動パターンに現在の移動パターンを入れる
	prevMovePattern = movePattern;
	// 次の移動パターンに変更
	movePattern = pattern;
}

void BOSS::SetShotPattern(int pattern)
{
	// 前回のショットパターンに現在のショットパタンを入れる
	prevShotPattern = shotPattern;
	// 次のショットパターンに変更
	shotPattern = pattern;
}

void  BOSS::Shot()
{
	// 何発発射したか
	int num = 0;
	// 空いてる弾の添え字
	int index;
	// ランダムで色を決定
	srand((unsigned)time(NULL));
	int rnd;
	rnd = rand() % 2;	// 0か1を返す
	// shotCountを戻すかどうかのフラグ
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

		//サウンドフラグを戻す
		shotSound = false;

		// 弾のセット
		switch (shotPattern)
		{
		case 0:
			if (shotCount % 7 == 0 && shotCount <= 28)
			{
				while ((index = ShotSearch()) != -1)
				{
					shot[index].type = 1;
					shot[index].pattern = 0;
					shot[index].speed = 6;

					// 7方向にショットを打つ
					switch (num)
					{
					case 0:
						shot[index].rad = trad - (24 * DX_PI / 180); // 一番左
						break;
					case 1:
						shot[index].rad = trad - (16 * DX_PI / 180); // 左から二番目
						break;
					case 2:
						shot[index].rad = trad - (8 * DX_PI / 180); // 左から三番目
						break;
					case 3:
						shot[index].rad = trad;	// 真ん中
						break;
					case 4:
						shot[index].rad = trad + (8 * DX_PI / 180);  // 右から3番目
						break;
					case 5:
						shot[index].rad = trad + (16 * DX_PI / 180);  // 右から2番目
						break;
					case 6:
						shot[index].rad = trad + (24 * DX_PI / 180);  // 一番右
						break;
					}

					if (rnd == 0)
					{
						shot[index].graph = blackShot[1];  // 黒
						shot[index].color = 0;
					}
					else if(rnd == 1)
					{
						shot[index].graph = whiteShot[1];  // 白
						shot[index].color = 1;
					}

					++num;
					shotSound = true;

					if (num == 7)
					{
						break;
					}

				}
			}
			break;
		case 1:
			if (shotCount % 3 == 0)
			{
				if ((index = ShotSearch()) != -1)
				{				
					if (rnd == 0)
					{
						shot[index].graph = blackShot[2];  // 黒
						shot[index].color = 0;
					}
					else if (rnd == 1)
					{
						shot[index].graph = whiteShot[2];  // 白
						shot[index].color = 1;
					}
					shot[index].type = 2;
					shot[index].speed = 5;
					shot[index].pattern = 1;
					shot[index].rad = atan2(py - y, px - x) + ((double)(rand() % 41) - 20) * DX_PI / 180;	// プレイヤーの両側20度までの範囲内でランダム
					shotSound = true;
				}
			}

			if (shotCount % 45 == 0)
			{
				while ((index = ShotSearch()) != -1)
				{
					if (rnd == 0)
					{
						shot[index].graph = blackShot[0];  // 黒
						shot[index].color = 0;
					}
					else if (rnd == 1)
					{
						shot[index].graph = whiteShot[0];  // 白
						shot[index].color = 1;
					}
					shot[index].type = 0;
					shot[index].speed = 2;
					shot[index].pattern = 1;
					shot[index].rad = ((360 / 40) * DX_PI / 180) * num + ((shotCount / 15) * 0.08);

					++num;

					if (num == 40)
					{
						break;
					}
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
					if (rnd == 0)
					{
						shot[index].graph = blackShot[0];  // 黒
						shot[index].color = 0;
					}
					else if (rnd == 1)
					{
						shot[index].graph = whiteShot[0];  // 白
						shot[index].color = 1;
					}
					shot[index].type = 0;
					shot[index].speed = 3;
					shot[index].rad = trad + num * ((360 / 20) * DX_PI / 180);
					shot[index].pattern = 1;
					
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
					if (rnd == 0)
					{
						shot[index].graph = blackShot[0];  // 黒
						shot[index].color = 0;
					}
					else if (rnd == 1)
					{
						shot[index].graph = whiteShot[0];  // 白
						shot[index].color = 1;
					}
					shot[index].type = 0;
					shot[index].speed = 3;
					shot[index].pattern = 1;
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
					if (rnd == 0)
					{
						shot[index].graph = blackShot[1];  // 黒
						shot[index].color = 0;
					}
					else if (rnd == 1)
					{
						shot[index].graph = whiteShot[1];  // 白
						shot[index].color = 1;
					}
					shot[index].type = 1;
					shot[index].speed = 6;
					shot[index].pattern = 1;

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
						// 5発分撃ち終わったら 60ループ(一秒間)停止
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
			//　何もしない
			break;
		}

		// 弾の移動処理
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
				}

				// 弾がはみ出てたらフラグを戻す
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

void BOSS::SetBossFlag(bool flag)
{
	bossFlag = flag;
}

bool BOSS::GetFlag()
{
	return flag;
}

bool BOSS::GetBossFlag()
{
	return bossFlag;
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

int BOSS::GetShotColor(int index)
{
	return shot[index].color;
}

void BOSS::Draw()
{
	// 弾から最初に描画
	for (int i = 0; i < BOSS_SHOTNUM; ++i)
	{
		if (shot[i].flag)
		{
			if (shot[i].graph != blackShot[1] || shot[i].graph != whiteShot[1])
			{
				DrawGraph(shot[i].x, shot[i].y, shot[i].graph, TRUE);
			}
			else
			{
				DrawRotaGraph(shot[i].x, shot[i].y, 1.0, shot[i].rad + 90 * DX_PI / 180, shot[i].graph, TRUE);
			}
		}
	}

	// 弾が当たった時にはダメージ用の画像を描画
	if (damageFlag)
	{
		DrawRotaGraph(x, y, 1.0, 0, graph, TRUE);
	}	
	else
	{
		// 何もないときは通常描画
		DrawRotaGraph(x, y, 1.0, 0, graph, TRUE);
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

