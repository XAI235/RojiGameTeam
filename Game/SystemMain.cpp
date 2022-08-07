#include "SystemMain.h"
#include "DxLib.h"

#include "Looper.h"
#include "Define.h"
#include "Parameter.h"

/*!
*	@brief	DXライブラリやゲームの初期処理
*/

bool SystemMain::initialize() const
{
	SetAlwaysRunFlag(TRUE);								//	ウィンドウがノンアクティブでも実行
	SetWindowSizeChangeEnableFlag(TRUE);				//	ウィンドウサイズを自由に変更可能
	SetOutApplicationLogValidFlag(FALSE);				//	ログ出力をしない
	SetFullScreenResolutionMode(DX_FSRESOLUTIONMODE_DESKTOP);	//	フルスクリーン時に縦横費を維持する
	SetWindowText("ぼくらの時間");				//	タイトルウィンドウをつける
	ChangeWindowMode(TRUE);								//	ウィンドウモードに変更
//	SetWindowSizeExtendRate(1.0);						//	ウィンドウサイズを変更したい場合はここに倍率を指定する
	const int COLOR_BIT = 32;							//	色のbit数。通常32で良いが軽くするならば16に変更する
	SetGraphMode(Define::Window_Width, Define::Window_Hight, COLOR_BIT);					//	ゲーム画面の解析度の設定をする
	if (DxLib_Init())
	{
		return false;
	}
	SetDrawScreen(DX_SCREEN_BACK);


    return true;
}

/*!
*	@brief	メイン処理
*/
void SystemMain::main() const
{

	Looper looper;
	
	while (!ScreenFlip() && !ProcessMessage() && !ClearDrawScreen())
	{
		if (!looper.loop())
		{
			break;
		}
	}
}

/*
*	@brief	DXライブラリやゲームの終了処理
*/
void SystemMain::finalize() const
{
	DxLib_End();
}
