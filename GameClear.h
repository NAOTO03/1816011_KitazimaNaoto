#pragma once

#include "score.h"
#include "define.h"

class GameClear
{
public:
	void All();
	void Initialize();
	void Finalize();
	static GameClear& GetInstance()
	{
		static GameClear gameClear;
		return gameClear;
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

