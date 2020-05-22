#include "GameOver.h"
#include "DxLib.h"


void GameOver::Initialize()
{
	graph = LoadGraph("data/png/Transition/GameOver.png");
}

void GameOver::Finalize()
{
	DeleteGraph(graph);	// �摜�̊J��
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

