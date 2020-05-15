#include "DxLib.h"
#include "math.h"
#include "define.h"
#include "boss.h"


BOSS::BOSS()
{
	x = 320;
	y = -100;
	prevX = 200;
	prevY = -100;

	bGraph[0] = LoadGraph("data/png/Boss/RedBoss.png");
	shotGraph[0] = LoadGraph("data/png/EShot/RedSho1.png");
	shotGraph[1] = LoadGraph("data/png/Eshot/RedShot2.png");
	shotGraph[2] = LoadGraph("data/png/Eshot/RedShot3.png");

	for (int i = 0; i < BOSS_SHOTNUM; ++i)
	{
		shot[i].flag = false;
		shot[i].gFlag = false;
		shot[i].graph = 0;
		shot[i].pattern = 0;
		shot[i].rad = 0;
		shot[i].speed = 0;
		shot[i].x = 0;
		shot[i].y = 0;
	}

	raise = 2;
	raise2 = 2;
	angle = 0;
	movePattern = 0;
	shotPattern = 0;
	moveX = 0;
	moveY = 180;
	waitCount = 0;
	wait = false;
	state = 0;
	damageFlag = false;
	flag = false;
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
	}
}

void BOSS::MovePattern1()
{
	angle += raise;

	y = 80 + sin(angle * DX_PI / 180) * BOSS_SHAKE;

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

void BOSS::MovePattern2()
{

}

void BOSS::MovePattern3()
{

}

void BOSS::MoveInit(double bx, double by, int state)
{

}

void BOSS::SetDamageFlag()
{

}

void BOSS::SetFlag(bool f)
{

}

bool BOSS::GetFlag()
{
	return flag;
}



void BOSS::Draw()
{
	// 弾が当たった時にはダメージ用の画像を描画
	if (damageFlag)
	{
		DrawRotaGraph(x, y, 1.0, 0, bGraph[0], TRUE);
	}	
	else
	{
		// 何もないときは通常描画
		DrawRotaGraph(x, y, 1.0, 0, bGraph[0], TRUE);
	}

	damageFlag = false;
}

void BOSS::All()
{
	Updata();
	Draw();
}

