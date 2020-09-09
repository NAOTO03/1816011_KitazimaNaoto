#pragma once

// �v���g�^�C�v�錾
class Title;
class DESCRIPTION;
class Game;
class GameClear;
class GameOver;

typedef enum
{
	SCENE_TITLE,		// �^�C�g�����
	SCENE_DESCRIPTION,	// ����������
	SCENE_GAME,			// �Q�[�����
	SCENE_CLEAR,		// �N���A���
	SCENE_GAMEOVER,		// �Q�[���I�[�o�[���
	SCENE_NONE,			// ����
}SCENE;

class SceneMgr
{
public:
	void Initialize();
	void Finalize();
	void ChangeScene(SCENE nextScene);	// �����@nextScene �ɃV�[����ύX����
	static SceneMgr& GetInstance()
	{
		static SceneMgr sceneMgr;
		return sceneMgr;
	}
	void All();
private:
	Title* title;
	DESCRIPTION* description;
	Game* game;
	GameClear* gameClear;
	GameOver* gameOver;
	bool FadeInScreen(int fadeStep);
	bool FadeOutScreen(int fadeStep);
	// ̪��ޏ����p
	int bright;
	int fadeCnt;
	bool fadeIn;
	bool fadeOut;

};

