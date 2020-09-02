#include "DxLib.h"
#include "define.h"
#include "score.h"
#include "sceneMgr.h"
#include "GameOver.h"


void GameOver::Initialize()
{
	graph = LoadGraph("data/png/Transition/GameOver.png");
	scoreGraph = LoadGraph("data/png/Score/ResultScore.png");
	LoadDivGraph("data/png/Score/ResultNumber.png", 10, 10, 1, 57, 100, graphNumber);

	score = new SCORE;
	LoadData();
}

void GameOver::Finalize()
{
	// �摜�̊J��
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
	DrawGraph(150, 300, scoreGraph, TRUE);  // ���݂̃X�R�A

	// �X�R�A�`��
	num = snprintf(buf, sizeof(buf), "%d", fileData.score);
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


// ----------- �f�[�^�̃��[�h ----------
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
