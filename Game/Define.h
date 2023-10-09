#pragma once

#ifndef INCLUDE_DEFINE
#define INCLUDE_DEFINE

/*
#define MESSAGE_FONT_SIZE 32
#define NAME_FONT_SIZE 24
#define MESSAGE_MAX_LENGTH = 27;						// 一行で表示する最大文字数
#define MESSAGE_MAX_LINE = 3;							// 表示する最大行数
#define BETWEEN_LINE = 50;								// 行間のサイズ
// */

// スクリプト最大行数
#define SCRIPT_MAX_LINE			 1000
// スクリプト最大文字数
#define SCRIPT_MAX_STRING_LENGTH 300

// グラフィックの最大登録数
#define GRAPHIC_MAX_NUM 10
// 画面に表示できる最大画像数
#define VISIBLE_GRAPHIC_MAX_NUM 10

// フェードイン　フェードアウトのスピード
#define GRAPHIC_FADEIN_FADEOUT_SPEED 1
// 輝度の最大値
#define GRAPHIC_MAX_BRIGHT 255
// 輝度の最小値
#define GRAPHIC_MIN_BRIGHT 0
// 画像描画モード
#define GRAPHIC_MODE_NONE 0
#define GRAPHIC_MODE_FADEIN 1
#define GRAPHIC_MODE_FADEOUT 2

#define GAME_TEXT_FARST_CHAPTER "./Data/scenario/Scenario_data.txt"

#endif

class Define final
{
public:
	const static int Window_Width;
	const static int Window_Hight;

	//const static int SCRIPT_MAX_STRING_LENGTH;
};

