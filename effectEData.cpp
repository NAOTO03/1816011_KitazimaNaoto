#include "Game.h"
#include "effectEData.h"

int EFFECT_EDEAD::graph[2];


EFFECT_EDEAD::EFFECT_EDEAD()
{
	x = y = 0;

	//画像読み込み。初回だけ
	if (graph[0] == 0)
	{
		graph[0] = LoadGraph("data/png/EEffect/effect1.png");
		graph[1] = LoadGraph("data/png/EEffect/effect2.png");
	}

	srand((unsigned int)time(NULL));	// 乱数を初期化 
	rad = 0;
	rate = 1;
	alpha = 255;
	count = 0;
	flag = false;
	index = 0;

}

void EFFECT_EDEAD::Updata()
{
	if (flag)
	{
		//初回だけ角度と添字セット
		if (count == 0)
		{
			rad = rand() % 624 / 100;
		}

		rate = 0.5 + count * 0.05;
		alpha = 255 - 255 / 30 * count;
		++count;

		if (count == 25)
		{
			count = 0;
			flag = false;
		}
	}
}

void EFFECT_EDEAD::SetFlag(double x, double y , int index)
{
	this->x = x;
	this->y = y;
	this->index = index;

	flag = true;
}

bool EFFECT_EDEAD::GetFlag()
{
	return flag;

}

void EFFECT_EDEAD::Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	DrawRotaGraph(x + 16, y + 16, rate, rad, graph[index], TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}


void EFFECT_EDEAD::All()
{
	Updata();
	Draw();
}

