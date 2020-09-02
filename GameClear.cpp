#include "DxLib.h"
#include "define.h"
#include "score.h"
#include "sceneMgr.h"
#include "GameClear.h"


void GameClear::Initialize()
{
	graph = LoadGraph("data/png/Transition/GameClear.png");
	scoreGraph = LoadGraph("data/png/Score/ResultScore.png");
	LoadDivGraph("data/png/Score/ResultNumber.png", 10, 10, 1, 57, 100, graphNumber);

	score = new SCORE;
	LoadData();
}

void GameClear::Finalize()
{
	DeleteGraph(graph);	// 画像の開放
	DeleteGraph(scoreGraph);
	for (int i = 0; i < 10; i++)
	{
		DeleteGraph(graphNumber[i]);
	}
	delete(score);
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
	char buf[100];
	int num;

	DrawGraph(50, 150, graph, TRUE);
	DrawGraph(150, 300, scoreGraph, TRUE);  // 現在のスコア

	// スコア描画
	num = snprintf(buf, sizeof(buf), "%d", fileData.score);
	for (int i = 0; i < num; ++i)
	{
		DrawGraph(250 + i * 48, 400, graphNumber[buf[i] - '0'], TRUE);
	}
}

void GameClear::All()
{
	Update();
	Draw();
}

// ----------- データのロード ----------
bool GameClear::LoadData()
{
	FILE *fp;

	fopen_s(&fp, "SaveData/saveData.dat", "rb");
	if (fp == NULL)
	{
		return false;
	}
	else
	{
		fread(&fileData, sizeof(fileData), 1, fp);
		fclose(fp);

		return true;
	}
}
