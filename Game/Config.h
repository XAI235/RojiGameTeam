#pragma once
class Config
{
	int iResolutionMode;					// フルスクリーン時の縦横比の維持
	int iChangeWindowMode;				// ウィンドウモードのオンオフ
	int iColor_bit;						// 色のbit数。通常なら32bit、軽量化するなら16bitに変更
	int iSetDrawScreen;					// スクリーンの描画先を指定、基本は裏描画
	int Window_Width, Window_Hight;

	void Apply_Config();

public:
	Config();							// Config.datがない場合
	Config(int ResolutionMode, int ChangeWindowMode, int Color_bit, int SetDrawScreen, int Width, int Hight);

	
};

