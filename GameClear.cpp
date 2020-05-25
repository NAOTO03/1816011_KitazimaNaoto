#include "GameClear.h"
#include "DxLib.h"
#include "sceneMgr.h"


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
	SceneMgr &sceneMgr = SceneMgr::GetInstance();

	if (CheckHitKey(KEY_INPUT_RETURN) || CheckHitKey(KEY_INPUT_SPACE))
	{
		sceneMgr.ChangeScene(SCENE_TITLE);
	}
}

void GameClear::Draw()
{
	DrawGraph(100, 200, graph, TRUE);
}

void GameClear::All()
{
	Initialize();
	Update();
	Draw();
}
