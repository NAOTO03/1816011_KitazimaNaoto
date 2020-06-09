#include "DxLib.h"
#include <time.h>
#include "math.h"
#include "effectPData.h"

EFFECT_PDEAD::EFFECT_PDEAD()
{
	graph[0] = LoadGraph("data/png/PEffect/effect1.png");
	graph[1] = LoadGraph("data/png/PEffect/effect2.png");

	width = 5;
	height = 5;
	index = 0;
	count = 0;
	flag = false;
	srand((unsigned)time(NULL));
}

void EFFECT_PDEAD::Updata()
{

	if (count == 0)
	{
		for (int i = 0; i < EFFECT_PDEADNUM; i++)
		{
			pEffect[i].x = x;
			pEffect[i].y = y;
			pEffect[i].rad = rand() % 3600 / 100;
			pEffect[i].speed = rand() % 10;
		}
	}

	//座標の移動
	for (int i = 0; i < EFFECT_PDEADNUM; ++i) 
	{
		pEffect[i].x += cos(pEffect[i].rad) * pEffect[i].speed;
		pEffect[i].y += sin(pEffect[i].rad) * pEffect[i].speed;
	}

	++count;

	if (count == 30)
	{
		flag = false;
		count = 0;
	}
}

void EFFECT_PDEAD::Draw()
{
	//飛び散るエフェクト描画
	for (int i = 0; i < EFFECT_PDEADNUM; ++i)
	{
		DrawGraph(pEffect[i].x - width / 2, pEffect[i].y - height / 2, graph[index], TRUE);
	}
}


void EFFECT_PDEAD::SetFlag(double x, double y, int index)
{
	count = 0;
	flag = true;
	this->x = x;
	this->y = y;
	this->index = index;
}

bool EFFECT_PDEAD::GetFlag()
{
	return flag;
}


void EFFECT_PDEAD::All()
{
	//フラグ立ってるときだけ実行
	if (flag)
	{
		Updata();
		Draw();
	}
}
