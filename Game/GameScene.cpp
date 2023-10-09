#define _CRT_SECURE_NO_WARNINGS
#include "stdafx.h"
#include "ScriptInformation.h"
#include "ScriptEngin.h"


/*int GameScene::isJapaneseCharactor(unsigned char code)
{
	if ((code >= 0x81 && code <= 0x9F) || (code >= 0xE0 && code <= 0xEF))		// SHIFT_JIS��2�o�C�g�Ȃ̂ŏ��1�o�C�g�����{��ł���Ɣ���Ő؂�΂���
	{
		return 1;
	}
	return 0;
}
*/
/*******************************************************/
/*@name message : char �\�������镶����                */
/*@name start   : int  �J�n�ʒu                        */
/*@name len     : int  �\��������(1�s�ƌ��Ă���������) */
/*******************************************************/
/*
void GameScene::writeSubString(char* message, int start, int len, int posX, int PosY,  int bufferLine)
{
	int i;

	// ������
	int maxLen = std::strlen(message);

	// start�̈ʒu�̕ύX
	// start�̈ʒu�܂łɓ��{�ꂪ�������ꍇ1�𑫂��Ă���
	for (i = 0; i < start && message[i] != '\0';)
	{
		if (isJapaneseCharactor(message[i]))
		{
			i += 2;				// ���{���2�o�C�g
			start++;			// 2�o�C�g�Ȃ̂ŃX�^�[�g�ʒu�������
		}
		else
		{
			i++;
		}
	}

	if (start >= maxLen)		// �X�^�[�g�ʒu��������̒��������Ȃ��
	{
		return;					// ���̕�����͑��I��
	}

	for (i = 0; i < len && message[start + i] != '\0';)
	{
		if (isJapaneseCharactor(message[start + i]))
		{
			// ���{��Ȃ��2�������\��
			g_message_buffer[bufferLine][i] = message[start + i];
			g_message_buffer[bufferLine][i + 1] = message[start + i + 1];

			// len�͓��{��Ȃ��߁A1�o�C�g���ǉ�
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

	FontColor = GetColor(0, 0, 0);			// ���F�ɐݒ�
	
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

	std::strcpy(g_message, "�˂��A�N���v�����N�̓_���ɂȂ��ĂȂ񂩂Ȃ��捡�܂łƈႤ����������Ȃ��A�̂�������Ȃ��ł��A�N�̉̂�҂��Ă�l������񂾂�");
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
		{				//	���b�Z�[�W�����̂܂ܕ\��
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
