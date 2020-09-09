#pragma once

// プロトタイプ宣言
class Title;
class DESCRIPTION;
class Game;
class GameClear;
class GameOver;

typedef enum
{
	SCENE_TITLE,		// タイトル画面
	SCENE_DESCRIPTION,	// 操作説明画面
	SCENE_GAME,			// ゲーム画面
	SCENE_CLEAR,		// クリア画面
	SCENE_GAMEOVER,		// ゲームオーバー画面
	SCENE_NONE,			// 無し
}SCENE;

class SceneMgr
{
public:
	void Initialize();
	void Finalize();
	void ChangeScene(SCENE nextScene);	// 引数　nextScene にシーンを変更する
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
	// ﾌｪｰﾄﾞ処理用
	int bright;
	int fadeCnt;
	bool fadeIn;
	bool fadeOut;

};

