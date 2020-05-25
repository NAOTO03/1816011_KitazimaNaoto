#pragma once

// プロトタイプ宣言
class Title;
class Game;
class GameClear;
class GameOver;

typedef enum
{
	SCENE_TITLE,	// タイトル画面
	SCENE_GAME,		// ゲーム画面
	SCENE_CLEAR,	// クリア画面
	SCENE_GAMEOVER, // ゲームオーバー画面
	SCENE_NONE,		// 無し
}SCENE;

class SceneMgr
{
public:
	void All();
	void Finalize();
	void ChangeScene(SCENE nextScene);	// 引数　nextScene にシーンを変更する
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

