#include "GameOver.h"
#include "DxLib.h"


void GameOver::Initialize()
{
	graph = LoadGraph("data/png/Transition/GameOver.png");
}

void GameOver::Finalize()
{
	DeleteGraph(graph);	// ‰æ‘œ‚ÌŠJ•ú
}

void GameOver::Update()
{
	if (CheckHitKey(KEY_INPUT_SPACE))
	{

	}
}

void GameOver::Draw()
{
	DrawGraph(0, 0, graph, TRUE);
}

void GameOver::All()
{
	Initialize();
	Finalize();
	Update();
	Draw();
}

