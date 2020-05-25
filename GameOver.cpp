#include "GameOver.h"
#include "DxLib.h"
#include "sceneMgr.h"


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
	SceneMgr &sceneMgr = SceneMgr::GetInstance();

	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		sceneMgr.ChangeScene(SCENE_TITLE);
	}
}

void GameOver::Draw()
{
	DrawGraph(100, 200, graph, TRUE);
}

void GameOver::All()
{
	Initialize();
	Update();
	Draw();
}

