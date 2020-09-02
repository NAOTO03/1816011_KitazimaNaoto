#pragma once

// �v���g�^�C�v�錾
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
	// �X�R�A�N���X
	SCORE *score;
	int graph;
	int scoreGraph;
	int graphNumber[10];
	FILE_DATA fileData;
};
