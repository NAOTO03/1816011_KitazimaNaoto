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

	//弾初期化
	memset(shot, 0, sizeof(shot));

	//弾画像読み込み
	int temp = LoadGraph("data/png/PShot/BlackShot.png");
	int w, h;
	GetGraphSize(temp, &w, &h);

	damageFlag = false;
	moveFlag = false;
	endFlag = false;
	shotSound = false; // ショット音が鳴ったかどうかを示すフラグ 

	//フラグを全部falseにしとく
	//グラフィックハンドルと画像のサイズを代入しとく
	for (int i = 0; i < PSHOT_NUM; ++i)
	{
		shot[i].flag = false;
		shot[i].graph[0] = LoadGraph("data/png/PShot/BlackShot.png");
		shot[i].graph[1] = LoadGraph("data/png/PShot/WhiteShot.png");
		shot[i].width = w;
		shot[i].height = h;
	}

	// プレイヤー
	graph[0] = LoadGraph("data/png/Player/BlackPlayer.png");
	graph[1] = LoadGraph("data/png/Player/WhitePlayer.png");
	// 回転する枠
	rGraph[0] = LoadGraph("data/png/Player/RotateBlack.png");
	rGraph[1] = LoadGraph("data/png/Player/RotateWhite.png");
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

	//0.04ラジアン(約2度)ずつ回転させる。
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
		// キーが押されててかつ、6ループに一回発射
		if (CheckHitKey(KEY_INPUT_Z) == 1 && shotCount % 6 == 0) 
		{
			for (int i = 0; i < PSHOT_NUM; ++i)
			{
				if (shot[i].flag == false)
				{
					// パワーが5より小さいとき前方に二つショットを撃つ
					if (power < 5)
					{
						if (num == 0)
						{
							shot[i].flag = true;
							// 弾の位置をセット、位置はプレイヤーの左
							shot[i].x = playerX - width / 6;
							shot[i].y = playerY - height / 4;
							shot[i].rad = -1.57;
						}
						else if(num == 1)
						{
							shot[i].flag = true;
							// 弾の位置をセット、位置はプレイヤーの右
							shot[i].x = playerX + width;
							shot[i].y = playerY - height / 4;
							shot[i].rad = -1.57;
						}

						++num;

						// 二つ撃ったらループから抜ける
						if (num == 2)
						{
							break;
						}
					}
					else if (power >= 5 && power < 10)	// 前方に４つショットを撃つ
					{
						if (num == 0)		
						{
							shot[i].flag = true;
							// 弾の位置をセット、位置はプレイヤーの左
							shot[i].x = playerX - width * 2;
							shot[i].y = playerY - height / 4;
							shot[i].rad = -1.57;
						}
						else if (num == 1)	
						{
							shot[i].flag = true;
							// 弾の位置をセット、位置はプレイヤーの左から２番目
							shot[i].x = playerX - width / 6;
							shot[i].y = playerY - height / 4;
							shot[i].rad = -1.57;
						}
						else if (num == 2)	
						{
							shot[i].flag = true;
							// 弾の位置をセット、位置はプレイヤーの右から２番目
							shot[i].x = playerX + width;
							shot[i].y = playerY - height / 4;
							shot[i].rad = -1.57;
						}
						else if (num == 3) 
						{
							shot[i].flag = true;
							// 弾の位置をセット、位置はプレイヤーの右
							shot[i].x = playerX + width * 3;
							shot[i].y = playerY - height / 4;
							shot[i].rad = -1.57;
						}

						++num;

						//四つ撃ったらループから抜ける
						if (num == 4)
						{
							break;
						}
					}
					else if (power >= 10)	// 3方向にショットを打つ
					{
						if (num == 0)
						{
							shot[i].flag = true;
							// 弾の位置をセット、位置はプレイヤーの左
							shot[i].x = playerX - width * 2;
							shot[i].y = playerY - height / 4;
							shot[i].rad = -1.57;
						}
						else if (num == 1)
						{
							shot[i].flag = true;
							// 弾の位置をセット、位置はプレイヤーの左から２番目
							shot[i].x = playerX - width / 6;
							shot[i].y = playerY - height / 4;
							shot[i].rad = -1.57;
						}
						else if (num == 2)
						{
							shot[i].flag = true;
							// 弾の位置をセット、位置はプレイヤーの右から2番目z
							shot[i].x = playerX + width;
							shot[i].y = playerY - height / 4;
							shot[i].rad = -1.57;
						}
						else if (num == 3)
						{
							shot[i].flag = true;
							// 弾の位置をセット、位置はプレイヤーの右
							shot[i].x = playerX + width * 3;
							shot[i].y = playerY - height / 4;
							shot[i].rad = -1.57;
						}
						else if (num == 4)	// 4の時が左斜め上
						{
							shot[i].flag = true;
							shot[i].x = playerX - width * 3;
							shot[i].y = playerY - height / 4;
							shot[i].rad = -1.69;
						}
						else if (num == 5) // 5の時が右斜め上
						{
							shot[i].flag = true;
							shot[i].x = playerX + width * 4;
							shot[i].y = playerY - height / 4;
							shot[i].rad = -1.45;
						}

						++num;

						// 3方向に撃ったらループから抜ける
						if (num == 6)
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
			case BLACK:
				DrawRotaGraph(shot[i].x, shot[i].y, 1.0, shot[i].rad + (90 * DX_PI / 180), shot[i].graph[0], TRUE);
				break;
			case WHITE:
				DrawRotaGraph(shot[i].x, shot[i].y, 1.0, shot[i].rad + (90 * DX_PI / 180), shot[i].graph[1], TRUE);
				break;
			}
		}
	}

	// 生きていれば描画
	if (damageFlag)
	{
		if (damageCount % 2 == 0)	// 2で割って余りが0になったときに少し透過させて描画
		{
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);	// 透過モード
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
			// 座標を初期地に戻す
			playerX = playerX;
			playerY = playerY;
		}
	}
	else
	{
		// 通常描画
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
	if (power > 15)
	{
		// パワーの最大値を10にしておく
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
	// 消滅していないときだけ実行
	if (!damageFlag || moveFlag)
	{
		Update();
	}
	Shot();
	Draw();
	effectPDead.All();
	++shotCount;
}

