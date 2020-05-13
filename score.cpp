#include "DxLib.h"
#include "score.h"
#include "define.h"



SCORE::SCORE()
{
	graph[0] = LoadGraph("data/png/Score/HighScore.png");
	graph[1] = LoadGraph("data/png/Score/score.png");
	graph[2] = LoadGraph("data/png/Score/life.png");
	LoadDivGraph("data/png/Score/number.png", 10, 10, 1, 19, 27, graphNumber);

	highScore = 0;
	score = 0;
	life = 0;
}


void SCORE::SetScore(SCOREDATA data, int val)
{
	switch (data)
	{
	case HIGH_SCORE:
		highScore += val;
		break;
	case CURRENT_SCORE:
		score += val;
		break;
	case LIFE_SCORE:
		life = val;
		break;
	}
}

int SCORE::GetScore(SCOREDATA data)
{
	switch (data)
	{
	case HIGH_SCORE:
		return highScore;
		break;
	case CURRENT_SCORE:
		return score;
		break;
	case LIFE_SCORE:
		return life;
		break;
	}
}

void SCORE::Draw()
{
	char buf[100];
	int num;

	// スコアの文字描画
	DrawGraph(SCORE_X, 10, graph[0], TRUE);	// ハイスコア
	DrawGraph(SCORE_X, 70, graph[1], TRUE); // 現在のスコア
	DrawGraph(SCORE_X, 160, graph[2], TRUE);// ライフ

	// ハイスコア描画
	num = snprintf(buf, sizeof(buf), "%d", highScore);
	for (int i = 0; i < num; ++i)
	{
		DrawGraph(SCORE_X + 20 + i * 19, 35, graphNumber[buf[i] - '0'], TRUE);
	}

	// スコア描画
	num = snprintf(buf, sizeof(buf), "%d", score);
	for (int i = 0; i < num; ++i)
	{
		DrawGraph(SCORE_X + 20 + i * 19, 95, graphNumber[buf[i] - '0'], TRUE);
	}

	// ライフ描画
	num = snprintf(buf, sizeof(buf), "%d", life);
	for (int i = 0; i < num; ++i)
	{
		DrawGraph(SCORE_X + 100 + i * 19, 160, graphNumber[buf[i] - '0'], TRUE);
	}
}

void SCORE::All()
{
	Draw();
}