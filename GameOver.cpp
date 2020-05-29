#include "GameOver.h"
#include "DxLib.h"
#include "sceneMgr.h"


void GameOver::Initialize()
{
	graph = LoadGraph("data/png/Transition/GameOver.png");
	scoreGraph = LoadGraph("data/png/Score/score.png");
	LoadDivGraph("data/png/Score/number.png", 10, 10, 1, 19, 27, graphNumber);

	score = new SCORE;
	LoadData();
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

	DrawGraph(100, 160, graph, TRUE);
	DrawGraph(300, 400, scoreGraph, TRUE);  // 現在のスコア

	// スコア描画
	num = snprintf(buf, sizeof(buf), "%d", fileData.score);
	for (int i = 0; i < num; ++i)
	{
		DrawGraph(400 + 20 + i * 19, 402, graphNumber[buf[i] - '0'], TRUE);
	}
}

void GameOver::All()
{
	Update();
	Draw();
}


// ----------- データのロード ----------
bool GameOver::LoadData()
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
