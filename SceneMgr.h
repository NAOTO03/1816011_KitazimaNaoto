#pragma once

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
public:
	void All();
private:
	void Initialize();
	void Finalize();
	void Update();
	void Draw();
	void ChangeScene(SCENE nextScene);	// 引数　nextScene にシーンを変更する
};

