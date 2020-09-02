#pragma once

// プロトタイプ宣言
class SCORE;

class GameOver
{
public:
	void Initialize();
	void Finalize();
	static GameOver& GetInstance()
	{
		static GameOver gameOver;
		return gameOver;
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
