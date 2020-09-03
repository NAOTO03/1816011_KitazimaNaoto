#include <DxLib.h>
#include "Title.h"
#include "SceneMgr.h"


void Title::Initialize()
{
	graph[0] = LoadGraph("data/png/Transition/Title.png");
	graph[1] = LoadGraph("data/png/Transition/Press.png");

	keySound = LoadSoundMem("data/se/button.mp3");
	PlayMusic("data/bgm/TitleBgm.mp3", DX_PLAYTYPE_LOOP);	// タイトルBGMの再生

	keyFlag = false;
}


void Title::Finalize()
{
	DeleteGraph(graph[0]);	// 画像の開放
	DeleteGraph(graph[1]);
}

void Title::Update()
{
	SceneMgr &sceneMgr = SceneMgr::GetInstance();

	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		sceneMgr.ChangeScene(SCENE_GAME);
		StopMusic();
		if(!keyFlag) KeySound(true);
		keyFlag = true;
	}
}

void Title::Draw()
{
	DrawGraph(100, 200, graph[0], TRUE);
	DrawGraph(180, 400, graph[1], TRUE);
}

void Title::KeySound(bool flag)
{
	if (flag)
	{
		PlaySoundMem(keySound, DX_PLAYTYPE_BACK);
	}
}

void Title::All()
{
	Update();
	Draw();
}
