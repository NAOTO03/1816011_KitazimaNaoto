#pragma once

struct FileData
{
	int score;
	int highScore;
};

class FILE_DATA
{
public:
	FILE_DATA();
	~FILE_DATA();
	bool SaveData();
	bool LoadData();
	int GetScore();
	int GetHighScore();
	void SetScore(int score);
	void SetHighScore(int score);
private:
	FileData fileData;
};

