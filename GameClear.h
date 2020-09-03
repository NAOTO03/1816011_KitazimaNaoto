#pragma once

// �v���g�^�C�v�錾
class SCORE;
class FILE_DATA;

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
private:
	// �X�R�A�N���X
	SCORE *score;
	int graph;
	int scoreGraph;
	int graphNumber[10];
	FILE_DATA *fileData;
};

