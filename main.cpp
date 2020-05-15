//-----------------------------------------------------------------------------
//  メイン処理.
//-----------------------------------------------------------------------------
#include "DxLib.h"
#include "Game.h" 

//-----------------------------------------------------------------------------
//  メイン関数.
//-----------------------------------------------------------------------------

int gameCount;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE);

	// 画面モードの設定
	SetGraphMode(900, 480, 16);		// 解像度を900*480、colorを16bitに設定.
	ChangeWindowMode(TRUE);			// ウインドウモードに.
	// SetBackgroundColor(255, 255, 255);
	SetBackgroundColor(220, 220, 220);

	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}

	// グラフィックの描画先を裏画面にセット
	SetDrawScreen(DX_SCREEN_BACK);

	// ゲームクラス生成
	Game &game = Game::GetInstance();

	// ゲームループ.
	while (1)
	{

		// 画面を初期化(真っ黒にする)
		ClearDrawScreen();

		game.All();

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

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}

