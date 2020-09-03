#include "DxLib.h"
#include "define.h"
#include "score.h"
#include "sceneMgr.h"
#include "GameOver.h"
#include "FileData.h"

void GameOver::Initialize()
{
	graph = LoadGraph("data/png/Transition/GameOver.png");
	scoreGraph = LoadGraph("data/png/Score/ResultScore.png");
	LoadDivGraph("data/png/Score/ResultNumber.png", 10, 10, 1, 57, 100, graphNumber);

	score = new SCORE;
	fileData = new FILE_DATA();
	fileData->LoadData();
}

void GameOver::Finalize()
{
	// 画像の開放
	DeleteGraph(graph);	
	DeleteGraph(scoreGraph);
	for (int i = 0; i < 10; i++)
	{
		DeleteGraph(graphNumber[i]);
	}
	delete(score);
}

void GameOver::Update()
{
	SceneMgr &sceneMgr = SceneMgr::GetInstance();

	if (CheckHitKey(KEY_INPUT_RETURN) || CheckHitKey(KEY_INPUT_SPACE))
	{
		sceneMgr.ChangeScene(SCENE_TITLE);
	}
}

void GameOver::Draw()
{
	char buf[100];
	int num;

	DrawGraph(100, 100, graph, TRUE);
	DrawGraph(150, 300, scoreGraph, TRUE);  // 現在のスコア

	// スコア描画
	num = snprintf(buf, sizeof(buf), "%d", fileData->GetScore());
	for (int i = 0; i < num; ++i)
	{
		DrawGraph(250 + i * 48, 400, graphNumber[buf[i] - '0'], TRUE);
	}
}

void GameOver::All()
{
	Update();
	Draw();
}
