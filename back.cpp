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
	DrawGraph(x, y, graph, TRUE);
	// DrawCircle(250, 300, 10, 0xffffff, true);
	// DrawCircle(500, 300, 10, 0x000000, true);
}

void BACK::All()
{
	Draw();
}
