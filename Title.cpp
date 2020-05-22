#include "Title.h"
#include "DxLib.h"


void Title::Initialize()
{
	graph[0] = LoadGraph("data/png/Transition/Title.png");
	graph[1] = LoadGraph("data/png/Transition/Press.png");
}


void Title::Finalize()
{
	DeleteGraph(graph[0]);	// ‰æ‘œ‚ÌŠJ•ú
	DeleteGraph(graph[1]);
}

void Title::Update()
{
	if (CheckHitKey(KEY_INPUT_SPACE))
	{

	}
}

void Title::Draw()
{
	DrawGraph(0, 0, graph[0], TRUE);
	DrawGraph(0, 300, graph[1], TRUE);
}

void Title::All()
{
	Initialize();
	Finalize();
	Update();
	Draw();
}
