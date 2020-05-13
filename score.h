#pragma once

enum SCOREDATA
{
	HIGH_SCORE,		// ハイスコア
	CURRENT_SCORE,	// 現在のスコア
	LIFE_SCORE		// ライフ
 };

class SCORE
{
private:
	int graph[3];
	int graphNumber[10];
	int highScore;
	int score;
	int life;
private:
	void Draw();
public:
	void SetScore(SCOREDATA data, int val);
	int GetScore(SCOREDATA data);
	void All();
	SCORE();
};
