#pragma once

#include "define.h"

// プロトタイプ宣言
class SCORE;

class GameClear
{
public:
	void Initialize();
	void Finalize();
	static GameClear& GetInstance()
	{
		static GameClear gameClear;
		return gameClear;
	}
	void All();
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

