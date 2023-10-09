#define _CRT_SECURE_NO_WARNINGS


#include "stdafx.h"

#include "SystemMain.h"



#include "Looper.h"
#include "Define.h"
#include "Parameter.h"

// */
//#include "../../NobelParts/NobelParts.h"



/*!
*	@brief	DXライブラリやゲームの初期処理
*/
bool SystemMain::initialize() const
{
	// 後で設定した設定に関係なく設定する
	SetAlwaysRunFlag(TRUE);								//	ウィンドウがノンアクティブでも実行
	SetWindowSizeChangeEnableFlag(FALSE);				//	ウィンドウサイズを自由に変更可能
	SetOutApplicationLogValidFlag(FALSE);				//	ログ出力をしない
	SetFullScreenResolutionMode(DX_FSRESOLUTIONMODE_DESKTOP);	//	フルスクリーン時に縦横費を維持する
	SetWindowText("ぼくらの時間");				//	タイトルウィンドウをつける
	ChangeWindowMode(TRUE);								//	ウィンドウモードに変更
//	SetWindowSizeExtendRate(1.0);						//	ウィンドウサイズを変更したい場合はここに倍率を指定する
	const int COLOR_BIT = 32;							//	色のbit数。通常32で良いが軽くするならば16に変更する
//	SetGraphMode(Define::Window_Width, Define::Window_Hight, COLOR_BIT);					//	ゲーム画面の解析度の設定をする
	SetGraphMode(1280, 720, COLOR_BIT);					//	ゲーム画面の解析度の設定をする
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

	AllocConsole();
	freopen("CONOUT$", "w", stdout);
	freopen("CONIN$", "r", stdin);

	
	while (!ScreenFlip() && !ProcessMessage() && !ClearDrawScreen())
	{
		//Nobel_Parts();
		
		if (!looper.loop())
		{
			break;
		}

		//std::cout << "X : " << Mouse::getIns()->getX() << " Y : " << Mouse::getIns()->getY() << std::endl;

	}

	FreeConsole();

}

/*
*	@brief	DXライブラリやゲームの終了処理
*/
void SystemMain::finalize() const
{
	DxLib_End();
}
