#pragma once

enum SCOREDATA
{
	HIGH_SCORE,		// �n�C�X�R�A
	CURRENT_SCORE,	// ���݂̃X�R�A
	LIFE_SCORE		// ���C�t
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
