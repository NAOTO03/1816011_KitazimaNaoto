#pragma once

enum SCOREDATA
{
	HIGH_SCORE,		// �n�C�X�R�A
	CURRENT_SCORE,	// ���݂̃X�R�A
	LIFE_SCORE,		// ���C�t
	POWER_SCORE		// �p���[
 };

class SCORE
{
private:
	int graph[4];
	int graphNumber[10];
	int highScore;
	int score;
	int life;
	int power;
private:
	void Draw();
public:
	void SetScore(SCOREDATA data, int val);
	int GetScore(SCOREDATA data);
	void All();
	SCORE();
};
