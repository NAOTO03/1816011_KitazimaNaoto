#include "GameClear.h"
#include "DxLib.h"


void GameClear::Initialize()
{
	graph = LoadGraph("data/png/Transition/GameClear.png");
}

void GameClear::Finalize()
{
	DeleteGraph(graph);	// ‰æ‘œ‚ÌŠJ•ú
}

void GameClear::Update()
{
	if (CheckHitKey(KEY_INPUT_SPACE))
	{

	}
}

void GameClear::Draw()
{
	DrawGraph(0, 0, graph, TRUE);
}

void GameClear::All()
{
	Initialize();
	Finalize();
	Update();
	Draw();
}
