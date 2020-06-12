//-----------------------------------------------------------------------------
//  メイン処理.
//-----------------------------------------------------------------------------
#include "DxLib.h"
#include "SceneMgr.h"

//-----------------------------------------------------------------------------
//  メイン関数.
//-----------------------------------------------------------------------------

int gameCount;

char key[256];

// キーの入力状態を更新する
int UpdateKey() 
{
	char tmpKey[256]; // 現在のキーの入力状態を格納する
	GetHitKeyStateAll(tmpKey); // 全てのキーの入力状態を得る

	for (int i = 0; i < 256; i++)
	{
		if (tmpKey[i] != 0)
		{ 
			// i番のキーコードに対応するキーが押されていたら
			key[i]++;     // 加算
		}
		else
		{              
			// 押されていなければ
			key[i] = 0;   // 0にする
		}
	}
	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// 画面モードの設定
	SetGraphMode(900, 600, 16);		// 解像度を900*600、colorを16bitに設定.
	ChangeWindowMode(TRUE);			// ウインドウモードに.
	SetBackgroundColor(192, 192, 192);	// 灰色

	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}

	// グラフィックの描画先を裏画面にセット
	SetDrawScreen(DX_SCREEN_BACK);

	// ゲームクラス生成
	SceneMgr &sceneMgr = SceneMgr::GetInstance();

	sceneMgr.Initialize();

	// ゲームループ.
	while (1)
	{

		// 画面を初期化(真っ黒にする)
		ClearDrawScreen();

		UpdateKey();

		sceneMgr.All();

		// 裏画面の内容を表画面にコピーする（描画の確定）.
		ScreenFlip();

		//  Windows 特有の面倒な処理をＤＸライブラリにやらせる
		// マイナスの値（エラー値）が返ってきたらループを抜ける
		if (ProcessMessage() < 0)
		{
			break;
		}
		// もしＥＳＣキーが押されていたらループから抜ける
		else if (CheckHitKey(KEY_INPUT_ESCAPE))
		{
			break;
		}
	}

	sceneMgr.Finalize();

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}

