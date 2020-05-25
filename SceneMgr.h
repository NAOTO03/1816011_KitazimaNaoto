#pragma once

// �v���g�^�C�v�錾
class Title;
class Game;
class GameClear;
class GameOver;

typedef enum
{
	SCENE_TITLE,	// �^�C�g�����
	SCENE_GAME,		// �Q�[�����
	SCENE_CLEAR,	// �N���A���
	SCENE_GAMEOVER, // �Q�[���I�[�o�[���
	SCENE_NONE,		// ����
}SCENE;

class SceneMgr
{
public:
	void All();
	void Finalize();
	void ChangeScene(SCENE nextScene);	// �����@nextScene �ɃV�[����ύX����
	static SceneMgr& GetInstance()
	{
		static SceneMgr sceneMgr;
		return sceneMgr;
	}
private:
	Title* title;
	Game* game;
	GameClear* gameClear;
	GameOver* gameOver;
};

