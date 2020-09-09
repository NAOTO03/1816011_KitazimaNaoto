#include <DxLib.h>
#include "Description.h"
#include "SceneMgr.h"


void DESCRIPTION::Initialize()
{
	graph[0] = LoadGraph("data/png/Transition/Operation(0).png");
	graph[1] = LoadGraph("data/png/Transition/Operation(1).png");
	graph[2] = LoadGraph("data/png/Transition/Operation(2).png");

	keySound = LoadSoundMem("data/se/button.mp3");
	keyFlag = false;
}


void DESCRIPTION::Finalize()
{
	DeleteGraph(graph[0]);	// ‰æ‘œ‚ÌŠJ•ú
	DeleteGraph(graph[1]);
	DeleteGraph(graph[2]);
}

void DESCRIPTION::Update()
{
	SceneMgr& sceneMgr = SceneMgr::GetInstance();

	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		sceneMgr.ChangeScene(SCENE_GAME);
		StopMusic();
		if (!keyFlag) KeySound(true);
		keyFlag = true;
	}
}

void DESCRIPTION::Draw()
{
	DrawGraph(-50, 50, graph[0], TRUE);
	DrawGraph(50, 180, graph[1], TRUE);
	DrawGraph(60, 320, graph[2], TRUE);
}

void DESCRIPTION::KeySound(bool flag)
{
	if (flag)
	{
		PlaySoundMem(keySound, DX_PLAYTYPE_BACK);
	}
}

void DESCRIPTION::All()
{
	Update();
	Draw();
}
