#pragma once

#include "ScriptInformation.h"

class Parameter
{
public:

	Parameter() = default;
	virtual ~Parameter() = default;
	Parameter operator=(const Parameter& parameter);

	const static int Error = -1;

	void initialize();


	int getBGMVolume();
	
private:
	bool WindowScreenMode;				//	スクリーンモード TRUEならウィンドウモード、FALSEならフルスクリーン
	int Color_Bit;						//	色のビット数、通常ならば32bit、軽量化するならば16bitに変更可能
	int Window_Hight;					//	ウィンドウサイズ 高さ
	int Window_Width;					//	ウィンドウサイズ 幅
	int BGMVolume;						//	BGMのボリューム 0～100
	int VoiceVolume;					//	ボイスのボリューム 0～100
	ScriptInformation scriptinfo;		//	シナリオの情報
	
	void copy(const Parameter& parameter);

};

/*
	SetAlwaysRunFlag(TRUE);								//	ウィンドウがノンアクティブでも実行 いじらない
	SetWindowSizeChangeEnableFlag(TRUE);				//	ウィンドウサイズを自由に変更可能 いじらない
	SetOutApplicationLogValidFlag(FALSE);				//	ログ出力をしない いじらない
	SetFullScreenResolutionMode(DX_FSRESOLUTIONMODE_DESKTOP);	//	フルスクリーン時に縦横費を維持する いじらない
	SetWindowText("ぼくらの時間");						//	タイトルウィンドウをつける いじらない
	ChangeWindowMode(TRUE);								//	ウィンドウモードに変更
//	SetWindowSizeExtendRate(1.0);						//	ウィンドウサイズを変更したい場合はここに倍率を指定する
	const int COLOR_BIT = 32;							//	色のbit数。通常32で良いが軽くするならば16に変更する
	SetGraphMode(Define::Window_Width, Define::Window_Hight, COLOR_BIT);					//	ゲーム画面の解析度の設定をする
	if (DxLib_Init())
	{
		return false;
	}
	SetDrawScreen(DX_SCREEN_BACK);
*/