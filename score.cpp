#include "DxLib.h"
#include "score.h"
#include "define.h"


SCORE::SCORE()
{
	graph[0] = LoadGraph("data/png/Score/HighScore.png");
	graph[1] = LoadGraph("data/png/Score/score.png");
	graph[2] = LoadGraph("data/png/Score/life.png");
	graph[3] = LoadGraph("data/png/Score/power.png");
	LoadDivGraph("data/png/Score/number02.png", 10, 10, 1, 19, 28, graphNumber);

	highScore = 0;
	score = 0;
	life = 0;
	power = 0;
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
	case POWER_SCORE:
		power = val;
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
	case POWER_SCORE:
		return power;
		break;
	}
}

void SCORE::Draw()
{
	char buf[100];
	int num;

	// スコアの文字描画
	DrawGraph(SCORE_X, 10, graph[0], TRUE);	 // ハイスコア
	DrawGraph(SCORE_X, 70, graph[1], TRUE);  // 現在のスコア
	DrawGraph(SCORE_X, 160, graph[2], TRUE); // ライフ
	DrawGraph(SCORE_X, 200, graph[3], TRUE); // パワー

	// ハイスコア描画
	num = snprintf(buf, sizeof(buf), "%d", highScore);
	for (int i = 0; i < num; ++i)
	{
		DrawGraph(SCORE_X + 20 + i * 19, 40, graphNumber[buf[i] - '0'], TRUE);
	}

	// スコア描画
	num = snprintf(buf, sizeof(buf), "%d", score);
	for (int i = 0; i < num; ++i)
	{
		DrawGraph(SCORE_X + 20 + i * 19, 100, graphNumber[buf[i] - '0'], TRUE);
	}

	// ライフ描画
	num = snprintf(buf, sizeof(buf), "%d", life);
	for (int i = 0; i < num; ++i)
	{
		DrawGraph(SCORE_X + 80 + i * 19, 162, graphNumber[buf[i] - '0'], TRUE);
	}

	// パワー描画
	num = snprintf(buf, sizeof(buf), "%d", power);
	for (int i = 0; i < num; ++i)
	{
		DrawGraph(SCORE_X + 120 + i * 19, 203, graphNumber[buf[i] - '0'], TRUE);
	}
}

void SCORE::All()
{
	Draw();
}