#define _CRT_SECURE_NO_WARNINGS
#include "stdafx.h"
#include "ScriptInformation.h"
#include "ScriptEngin.h"


/*int GameScene::isJapaneseCharactor(unsigned char code)
{
	if ((code >= 0x81 && code <= 0x9F) || (code >= 0xE0 && code <= 0xEF))		// SHIFT_JISは2バイトなので上位1バイトが日本語であると判定で切ればおｋ
	{
		return 1;
	}
	return 0;
}
*/
/*******************************************************/
/*@name message : char 表示させる文字列                */
/*@name start   : int  開始位置                        */
/*@name len     : int  表示文字列(1行と見てもいいかも) */
/*******************************************************/
/*
void GameScene::writeSubString(char* message, int start, int len, int posX, int PosY,  int bufferLine)
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
// */


GameScene::GameScene(IOnSceneChangedListener* impl, const Parameter& parameter) : AbstractScene(impl, parameter)
{
	param = parameter;
	NextScene = eScene::None;
	currentCursor = 0;
	currentLineCursor = 0;

	

	iFont_color = GetColor(255, 255, 255);

	FontColor = GetColor(0, 0, 0);			// 黒色に設定
	
	addGraphicNode(TESTBACKGROUND_NUM, MESSAGE_WINDOW_PATH);


	addVisibleGraphic(g_graphicManager[getGraphicIdPosition(TESTBACKGROUND_NUM)].id, g_graphicManager[getGraphicIdPosition(TESTBACKGROUND_NUM)].id, 0, 0, GRAPHIC_MODE_FADEIN);
	//GraphicHandle = LoadGraph(Message_Window_Path);
	//g_message = new char[sizeof(char) * MESSAGE_MAX_LENGTH * MESSAGE_MAX_LINE * 2];
	//g_message_buffer = new char* [sizeof(char*) * MESSAGE_MAX_LINE * 2];
	g_message = (char*)malloc(sizeof(char) * MESSAGE_MAX_LENGTH * MESSAGE_MAX_LINE * 2);
	g_message_buffer = (char **)malloc(sizeof(char*) * MESSAGE_MAX_LINE*2);

	memset(&g_message, 0, sizeof(char) * MESSAGE_MAX_LENGTH * MESSAGE_MAX_LINE * 2);
	memset(&g_message, 0, sizeof(char) * MESSAGE_MAX_LENGTH * MESSAGE_MAX_LINE * 2);

	for (int i = 0; i < MESSAGE_MAX_LINE; i++)
	{
		//g_message_buffer[i] = new char[sizeof(char) * MESSAGE_MAX_LENGTH * 2];
		g_message_buffer[i] = (char *)malloc(sizeof(char) * MESSAGE_MAX_LENGTH * 2);
	}

	std::strcpy(g_message, "ねぇ、君が思うより君はダメになってなんかないよ今までと違う声かもしれない、歌かもしれないでも、君の歌を待ってる人がいるんだよ");
}

void GameScene::update()
{
	if (Mouse::getIns()->getPressingCount(Mouse::getIns()->LEFT_CLICK))
	{
		g_visibleGraphic[getGraphicIdPosition(TITLE_BACKGROUND)].mode = GRAPHIC_MODE_FADEOUT;
		NextScene = eScene::Title;

	}


	if (g_message[currentCursor] != '\0')
	{
		currentCursor++;
	}

	if ((currentCursor % MESSAGE_MAX_LENGTH == 0))
	{
		if (g_message[currentCursor] != '\0')
		{
			currentLineCursor++;
		}
	}

	for (int i = 0; i < MESSAGE_MAX_LINE; i++)
	{
		if (i == currentLineCursor)
		{
			//writeSubString(g_message, g_message_buffer, i * MESSAGE_MAX_LENGTH, currentCursor - MESSAGE_MAX_LENGTH * i, 150, 510 + iMESSAGE_FONT_SIZE * i, i);
			writeSubString(g_message, g_message_buffer, i * MESSAGE_MAX_LENGTH, currentCursor - MESSAGE_MAX_LENGTH * i,  i);
			break;
		}
		else
		{				//	メッセージをそのまま表示
			//writeSubString(g_message, g_message_buffer, i * MESSAGE_MAX_LENGTH, MESSAGE_MAX_LENGTH, 150, 510 + iMESSAGE_FONT_SIZE * i, i);
			writeSubString(g_message, g_message_buffer, i * MESSAGE_MAX_LENGTH, MESSAGE_MAX_LENGTH, i);
		}
	}

	if (NextScene != eScene::None && g_visibleGraphic[getGraphicIdPosition(TITLE_BACKGROUND)].bright <= 0)
	{
		//StopSoundMem(BGM);
		const bool stackClear = false;
		_impSceneChanged->onSceneChanged(NextScene, param, stackClear);
	}

}

void GameScene::draw()
{
	//DrawGraph(0, 0, GraphicHandle, TRUE);

	drawVisibleGraphic();

	for (int i = 0; i < MESSAGE_MAX_LINE; i++)
	{

		ChangeFont(cFont_Name);
		SetFontSize(iMESSAGE_FONT_SIZE);
		DrawString(150, 510 + BETWEEN_LINES * i, g_message_buffer[i], FontColor);

		//Sleep(40);
	}

}
