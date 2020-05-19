// ------ プレイヤー　------

#include "DxLib.h"
#include "player.h"
#include "math.h"

// プレイヤーを初期化する
PLAYER::PLAYER()
{
	//---------------------------------
	// ---------- プレイヤー ----------
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

	//弾初期化
	memset(shot, 0, sizeof(shot));

	//弾画像読み込み
	int temp = LoadGraph("data/png/PShot/RedShot.png");
	int w, h;
	GetGraphSize(temp, &w, &h);

	damageFlag = false;
	endFlag = false;
	shotSound = false; // ショット音が鳴ったかどうかを示すフラグ 

	//フラグを全部falseにしとく
	//グラフィックハンドルと画像のサイズを代入しとく
	for (int i = 0; i<PSHOT_NUM; ++i)
	{
		shot[i].flag = false;
		shot[i].graph[0] = LoadGraph("data/png/PShot/RedShot.png");
		shot[i].graph[1] = LoadGraph("data/png/PShot/BlueShot.png");
		shot[i].graph[2] = LoadGraph("data/png/PShot/GreenShot.png");
		shot[i].width = w;
		shot[i].height = h;
	}

	// プレイヤーのグラフィックをメモリにロード＆表示座標を初期化
	graph[0] = LoadGraph("data/png/Player/RedPlayer.png");
	graph[1] = LoadGraph("data/png/Player/BluePlayer.png");
	graph[2] = LoadGraph("data/png/Player/GreenPlayer.png");
}

// プレイヤーの更新
void PLAYER::Update()
{
	if (CheckHitKey(KEY_INPUT_LEFT) == 1 || CheckHitKey(KEY_INPUT_RIGHT) == 1) 
	{
		if (CheckHitKey(KEY_INPUT_UP) == 1 || CheckHitKey(KEY_INPUT_DOWN) == 1) 
		{
				//移動係数を０．７１に設定
				move = 0.71f;
		}
		else {
				//斜めじゃなければ１．０に設定
				move = 1.0f;
		}
	}
	else if (CheckHitKey(KEY_INPUT_UP) == 1 || CheckHitKey(KEY_INPUT_DOWN) == 1)
	{
			move = 1.0f;
	}

	// 矢印キーを押していたらプレイヤーを移動させる
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

	// プレイヤーが画面左端からはみ出そうになっていたら画面内の座標に戻してあげる
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
		// キーが押されててかつ、6ループに一回発射
		if (CheckHitKey(KEY_INPUT_SPACE) == 1 && shotCount % 6 == 0) 
		{
			for (int i = 0; i < PSHOT_NUM; ++i)
			{
				if (shot[i].flag == false)
				{
					// パワーが5より小さいとき前方にショットを撃つ
					if (power < 5)
					{
					    shot[i].flag = true;
						// 弾の位置をセット、位置はプレイヤーの中心にする
						shot[i].x = playerX + width / 2;
						shot[i].y = playerY - height / 2;
						shot[i].rad = -1.57;
						break;
					}
					else if (power >= 5)	// 3方向にショットを打つ
					{
						// 0の時が前方にショット
						if (num == 0)
						{
							shot[i].flag = true;
							shot[i].x = playerX + width / 2;
							shot[i].y = playerY - height / 2;
							shot[i].rad = -1.57;
						}
						else if (num == 1)	// 1の時が左斜め上
						{
							shot[i].flag = true;
							shot[i].x = playerX + width / 2;
							shot[i].y = playerY - height / 2;
							shot[i].rad = -1.69;
						}
						else if (num == 2)	// 2の時が右斜め上
						{
							shot[i].flag = true;
							shot[i].x = playerX + width / 2;
							shot[i].y = playerY - height / 2;
							shot[i].rad = -1.45;
						}

						++num;

						// 3方向に打ったらループから抜ける
						if (num == 3)
						{
							break;
						}
					}
				}
			}
			// ショットサウンドフラグを立てる
			shotSound = true;
		}
	}

	//弾を移動させる処理
	for (int i = 0; i < PSHOT_NUM; ++i) 
	{
		//発射してる弾だけ
		if (shot[i].flag) 
		{
			shot[i].x += cos(shot[i].rad) * PSHOT_SPEED;
			shot[i].y += sin(shot[i].rad) * PSHOT_SPEED;
			//画面の外にはみ出したらフラグを戻す
			if (shot[i].y < -10 || shot[i].x < -20 || shot[i].x > 640)
			{
				shot[i].flag = false;
			}
		}
	}
}

void PLAYER::Draw()
{
	//弾描画
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

	// 生きていれば描画
	if (damageFlag)
	{
		if (damageCount > 40)	// エネミーの弾が当たったら40まで描画をしない
		{
			if (damageCount % 2 == 0)	// 2で割って余りが0になったときに少し透過させて描画
			{
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);	// 透過モード
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
			// 座標を初期地に戻す
			playerX = PLAYER_INITX;
			playerY = PLAYER_INITY;
		}
	}
	else
	{
		// 通常描画
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
	// ライフを減らす
	if (life > 0)
	{
		--life;
	}
	else
	{
		life = 0;
	}
	// 消滅エフェクトのフラグを立てる
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
		// パワーの最大値を10にしておく
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
	// 消滅していないときだけ実行
	if (!damageFlag)
	{
		Update();
	}
	Shot();
	Draw();
	effectPDead.All();
	++shotCount;
}

