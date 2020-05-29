#pragma once

#include "score.h"
#include "define.h"

class GameOver
{
public:
	void All();
	void Initialize();
	void Finalize();
	static GameOver& GetInstance()
	{
		static GameOver gameOver;
		return gameOver;
	}
private:
	void Update();
	void Draw();
	bool LoadData();
private:
	// スコアクラス
	SCORE *score;
	int graph;
	int scoreGraph;
	int graphNumber[10];
	FILE_DATA fileData;
};
