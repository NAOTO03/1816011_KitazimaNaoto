#include "SceneMgr.h"
#include "DxLib.h"
#include "Title.h"
#include "Game.h"
#include "GameClear.h"
#include "GameOver.h"

static SCENE scene = SCENE_TITLE;       //シーン管理変数
static SCENE nextScene = SCENE_NONE;    //次のシーン管理変数

static void InitializeModule(SCENE scene); //指定モジュールを初期化する
static void FinalizeModule(SCENE scene);   //指定モジュールの終了処理を行う

// 初期化
void SceneMgr::Initialize()
{
	InitializeModule(scene);
}

//終了処理
void SceneMgr::Finalize() 
{
	FinalizeModule(scene);
}

void SceneMgr::All()
{
	// タイトルクラス作成
	Title &title = Title::GetInstance();
	// ゲームクラス生成
	Game &game = Game::GetInstance();
	// ゲームクリアクラス生成
	GameClear &gameClear = GameClear::GetInstance();
	// ゲームオーバークラス生成
	GameOver &gameOver = GameOver::GetInstance();

	if (fadeIn)
	{
		if (!FadeInScreen(5)) fadeIn = false;
	}
	else if (fadeOut)
	{
		if (!FadeOutScreen(5))
		{
			FinalizeModule(scene);		//現在のシーンの終了処理を実行
			scene = nextScene;			//次のシーンを現在のシーンセット
			nextScene = SCENE_NONE;     //次のシーン情報をクリア
			InitializeModule(scene);    //現在のシーンを初期化
			fadeOut = false;
			fadeIn = true;
		}
	}

	if (nextScene != SCENE_NONE)	     //次のシーンがセットされていたら
	{
		fadeOut = true;
	}
		

	//シーンによって処理を分岐
	switch (scene)
	{       
	case SCENE_TITLE:   
		title.All();
		break;
	case SCENE_GAME:
		game.All();
		break;
	case SCENE_CLEAR:
		gameClear.All();
		break;
	case SCENE_GAMEOVER:
		gameOver.All();
		break;
	}
}

// 引数 nextScene にシーンを変更する
void SceneMgr::ChangeScene(SCENE NextScene)
{
	nextScene = NextScene;    //次のシーンをセットする
}

// 引数sceneモジュールを初期化する
static void InitializeModule(SCENE scene)
{
	// タイトルクラス作成
	Title &title = Title::GetInstance();
	// ゲームクラス生成
	Game &game = Game::GetInstance();
	// ゲームクリアクラス生成
	GameClear &gameClear = GameClear::GetInstance();
	// ゲームオーバークラス生成
	GameOver &gameOver = GameOver::GetInstance();

	//シーンによって処理を分岐
	switch (scene)
	{
	case SCENE_TITLE:
		title.Initialize();
		break;
	case SCENE_GAME:
		game.Initialize();
		break;
	case SCENE_CLEAR:
		gameClear.Initialize();
		break;
	case SCENE_GAMEOVER:
		gameOver.Initialize();
		break;
	}
}

// 引数sceneモジュールの終了処理を行う
static void FinalizeModule(SCENE scene) 
{
	// タイトルクラス作成
	Title &title = Title::GetInstance();
	// ゲームクラス生成
	Game &game = Game::GetInstance();
	// ゲームクリアクラス生成
	GameClear &gameClear = GameClear::GetInstance();
	// ゲームオーバークラス生成
	GameOver &gameOver = GameOver::GetInstance();

	//シーンによって処理を分岐
	switch (scene)
	{
	case SCENE_TITLE:
		title.Finalize();
		break;
	case SCENE_GAME:
		game.~Game();
		break;
	case SCENE_CLEAR:
		gameClear.Finalize();
		break;
	case SCENE_GAMEOVER:
		gameOver.Finalize();
		break;
	}
}

// ﾌｪｰﾄﾞｲﾝ処理
bool SceneMgr::FadeInScreen(int fadeStep)
{
	fadeCnt += fadeStep;
	if (fadeCnt <= 255) 
	{
		SetDrawBright(fadeCnt, fadeCnt, fadeCnt);
		return true;
	}
	else 
	{
		fadeCnt = 0;
		SetDrawBright(255, 255, 255);
		return false;
	}
}

// ﾌｪｰﾄﾞｱｳﾄ処理
bool SceneMgr::FadeOutScreen(int fadeStep)
{
	fadeCnt += fadeStep;
	if (fadeCnt <= 255)
	{
		SetDrawBright(255 - fadeCnt, 255 - fadeCnt, 255 - fadeCnt);
		return true;
	}
	else
	{
		fadeCnt = 0;
		SetDrawBright(0, 0, 0);
		return false;
	}
}