#pragma once

enum SCOREDATA
{
	HIGH_SCORE,		// ハイスコア
	CURRENT_SCORE,	// 現在のスコア
	LIFE_SCORE,		// ライフ
	POWER_SCORE		// パワー
 };

class SCORE
{
public:
	void SetScore(SCOREDATA data, int val);
	int GetScore(SCOREDATA data);
	void All();
	SCORE();
private:
	void Draw();
private:
	int graph[4];
	int graphNumber[10];
	int highScore;
	int score;
	int life;
	int power;
};
