#include "Title.h"
#include "DxLib.h"
#include "SceneMgr.h"


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
	SceneMgr &sceneMgr = SceneMgr::GetInstance();

	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		sceneMgr.ChangeScene(SCENE_GAME);
	}
}

void Title::Draw()
{
	DrawGraph(100, 200, graph[0], TRUE);
	DrawGraph(180, 400, graph[1], TRUE);
}

void Title::All()
{
	Initialize();
	Update();
	Draw();
}
