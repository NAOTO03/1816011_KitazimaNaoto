#include "DxLib.h"
#include "back.h"



BACK::BACK()
{
	graph = LoadGraph("data/png/Back/back.png");

	x = 0;
	y = 0;
}

void BACK::Draw()
{
	DrawGraph(x, y, graph, FALSE);
}

void BACK::All()
{
	Draw();
}
