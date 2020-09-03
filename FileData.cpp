#include <DxLib.h>
#include "FileData.h"

FILE_DATA::FILE_DATA()
{
	fileData.score = 0;
	fileData.highScore = 0;
}

FILE_DATA::~FILE_DATA()
{
}

// ---------- �f�[�^�̃Z�[�u ----------
bool FILE_DATA::SaveData()
{
	FILE *fp;

	fopen_s(&fp, "SaveData/saveData.dat", "wb");
	if (fp == NULL)
	{
		return false;
	}
	else
	{
		fwrite(&fileData, sizeof(fileData), 1, fp);		// ��������
		fclose(fp);

		return true;
	}
}

// ----------- �f�[�^�̃��[�h ----------
bool FILE_DATA::LoadData()
{
	FILE *fp;

	fopen_s(&fp, "SaveData/saveData.dat", "rb");
	if (fp == NULL)
	{
		return false;
	}
	else
	{
		fread(&fileData, sizeof(fileData), 1, fp);
		fclose(fp);

		return true;
	}
}

int FILE_DATA::GetScore()
{
	return fileData.score;
}

int FILE_DATA::GetHighScore()
{
	return fileData.highScore;
}

void FILE_DATA::SetScore(int score)
{
	fileData.score = score;
}

void FILE_DATA::SetHighScore(int score)
{
	fileData.highScore = score;
}