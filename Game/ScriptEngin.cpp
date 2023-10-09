#define _CRT_SECURE_NO_WARNINGS

#include "stdafx.h"
#include "ScriptInformation.h"
#include "ScriptEngin.h"

// 移行時に使用する関数
int loadScript(const char* filename, ScriptInformation* ScriptInfo)
{
	int position, NowLine;
	char c;

	//　スクリプトファイル用変数
	std::FILE* fp;

	memset(ScriptInfo, 0, sizeof(ScriptInformation));

	fp = std::fopen(filename, "r");

	if (fp == NULL)
	{
		// ファイル読み込みに失敗した場合
		printf("スクリプト%sを読み込みに失敗しました。\n", filename);
		return -1;
	}

	position = 0;	//	読み込ます際には、ScriptInfo.currentLineまで読み飛ばす必要

	for(;;)		//	一応終わるまで無限ループ
	{
		// 1文字読み込み
		c = std::fgetc(fp);

		// ファイルが終わりなら読み込み終了
		if (std::feof(fp))
			break;

		// 空白かタブが文章の最初に入っていた場合、そこは読み飛ばし
		while ((c == ' ' || c == '\t') && position == 0 && !feof(fp))
			c = fgetc(fp);

		// 文字数制限ではなく、超えた場合新しいラインに切り替えた方がいい…?
		if (position >= SCRIPT_MAX_STRING_LENGTH - 1)
		{	//	1行で読み込める文字数を超えている
			printf("error : 文字数が多すぎます (%d行目)", ScriptInfo->currentLine);
			return -1;
		}
		// */

		// 改行文字が出てきた場合に、次の行へ移行
		if (c == '\n' || position >= SCRIPT_MAX_LINE-1)
		{
			//\0を文字列の最後に付ける
			ScriptInfo->script[ScriptInfo->currentLine][position] = '\0';
			// 次の行へ移動
			ScriptInfo->currentLine++;

			// 書き込み位置を0に
			position = 0;
		}
		else
		{
			// 書き込み
			ScriptInfo->script[ScriptInfo->currentLine][position] = c;

			// 文字を書き込み位置をずらす
			position++;
		}
	}

	// 最大行数
	ScriptInfo->MaxLineNumber = ScriptInfo->currentLine;

	// 読み込みの中の行を0にする
	ScriptInfo->currentLine = 0;

	// スクリプトファイル名の設定
	ScriptInfo->filename = (char*) filename;

	return 0;
}


/*******************************************************/
/*@name code  : char 日本語か判定される文              */
/*******************************************************/
int isJapaneseCharactor(unsigned char code)
{
	if ((code >= 0x81 && code <= 0x9F) || (code >= 0xE0 && code <= 0xEF))		// SHIFT_JISは2バイトなので上位1バイトが日本語であると判定で切ればおｋ
	{
		return 1;
	}
	return 0;
}


/*******************************************************/
/*@name message : char 表示させる文字列                */
/*@name start   : int  開始位置                        */
/*@name len     : int  表示文字列(1行と見てもいいかも) */
/*******************************************************/
void writeSubString(char* message, char** g_message_buffer,int start, int len, int bufferLine)
{
	int i;

	// 文字数
	int maxLen = std::strlen(message);

	// startの位置の変更
	// startの位置までに日本語があった場合1を足していく
	for (i = 0; i < start && message[i] != '\0';)
	{
		if (isJapaneseCharactor(message[i]))
		{
			i += 2;				// 日本語は2バイト
			start++;			// 2バイトなのでスタート位置がずれる
		}
		else
		{
			i++;
		}
	}

	if (start >= maxLen)		// スタート位置が文字列の長さより後ろならば
	{
		return;					// この文字列は即終了
	}

	for (i = 0; i < len && message[start + i] != '\0';)
	{
		if (isJapaneseCharactor(message[start + i]))
		{
			// 日本語ならば2文字分表示
			g_message_buffer[bufferLine][i] = message[start + i];
			g_message_buffer[bufferLine][i + 1] = message[start + i + 1];

			// lenは日本語なため、1バイト分追加
			len++;

			i += 2;
		}
		else
		{
			g_message_buffer[bufferLine][i] = message[start + i];
			i += 1;
		}
	}

	g_message_buffer[bufferLine][i] = '\0';
}
/// <summary>
///		文字表示関数
/// </summary>
/// <param name="PosX">文字表示 X座標</param>
/// <param name="PosY">文字表示 Y座標</param>
/// <param name="g_message_buffer">表示文字</param>
/// <param name="color">文字の色</param>
void drawString(int PosX, int PosY, char* g_message_buffer, unsigned int color)
{
	/*
	for (int i = 0; i < MESSAGE_MAX_LINE; i++)
	{

		ChangeFont(cFont_Name);
		SetFontSize(iMESSAGE_FONT_SIZE);
		DrawString(150, 510 + BETWEEN_LINES * i, g_message_buffer[i], FontColor);

		//Sleep(40);
	}
	*/
}
void splitString(char* src, char* dest[], const char* delim, int splitNum)
{
	int i;
	char* cp;
	char* copySrc;

	copySrc = new char[sizeof(char) * SCRIPT_MAX_STRING_LENGTH + 1];
	std::strncpy(copySrc, src, SCRIPT_MAX_STRING_LENGTH);
	cp = copySrc;

	// strtokを使ってcopySrcをdelim区切りで分割する
	for (i = 0; i < splitNum; i++)
	{
		if ((dest[i] = std::strtok(cp, delim)) == NULL)
			break;

		// 2回目にstrtocが呼び出すときはcpをNULLにする
		cp = NULL;
	}

	// 分割後文字列の最後にはNULLを入れて分割する
	dest[i] = NULL;
}

int decodeScript(const char* scriptMessage)
{
	// 分割されたスクリプト
	char* message[100];
	// 文字列分割時の区切り文字
	const char* delim = " ";

	splitString((char*)scriptMessage, message, delim, 100);

	// 分割に失敗していた場合
	if (message[0] == NULL)
	{
		return 0;
	}

	// scriptの仕様
	// @@message 文字列
	// -- 文字列をメッセージとして表示する
	//
	// @@drawgraph x y filename
	// -- filenameで指定した画像ファイルを(x,y)の位置で表示
	if (std::strncmp(message[0], "@@message", SCRIPT_MAX_STRING_LENGTH) == 0)
	{
		// ここに文字列を表示するプログラムを書く
	}
	else if (std::strncmp(message[0], "@@drawgraph", SCRIPT_MAX_STRING_LENGTH) == 0)
	{
		// 画像の表示をする filenameはmapで管理して、名前だけを書くようにする
		// 例 : 廊下 -> rouka
		// mapはファイル読み込みして作るようにする。
		// 
	}
}