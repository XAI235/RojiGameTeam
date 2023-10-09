#define _CRT_SECURE_NO_WARNINGS

#include "stdafx.h"
#include "ScriptInformation.h"
#include "ScriptEngin.h"

// �ڍs���Ɏg�p����֐�
int loadScript(const char* filename, ScriptInformation* ScriptInfo)
{
	int position, NowLine;
	char c;

	//�@�X�N���v�g�t�@�C���p�ϐ�
	std::FILE* fp;

	memset(ScriptInfo, 0, sizeof(ScriptInformation));

	fp = std::fopen(filename, "r");

	if (fp == NULL)
	{
		// �t�@�C���ǂݍ��݂Ɏ��s�����ꍇ
		printf("�X�N���v�g%s��ǂݍ��݂Ɏ��s���܂����B\n", filename);
		return -1;
	}

	position = 0;	//	�ǂݍ��܂��ۂɂ́AScriptInfo.currentLine�܂œǂݔ�΂��K�v

	for(;;)		//	�ꉞ�I���܂Ŗ������[�v
	{
		// 1�����ǂݍ���
		c = std::fgetc(fp);

		// �t�@�C�����I���Ȃ�ǂݍ��ݏI��
		if (std::feof(fp))
			break;

		// �󔒂��^�u�����͂̍ŏ��ɓ����Ă����ꍇ�A�����͓ǂݔ�΂�
		while ((c == ' ' || c == '\t') && position == 0 && !feof(fp))
			c = fgetc(fp);

		// �����������ł͂Ȃ��A�������ꍇ�V�������C���ɐ؂�ւ������������c?
		if (position >= SCRIPT_MAX_STRING_LENGTH - 1)
		{	//	1�s�œǂݍ��߂镶�����𒴂��Ă���
			printf("error : ���������������܂� (%d�s��)", ScriptInfo->currentLine);
			return -1;
		}
		// */

		// ���s�������o�Ă����ꍇ�ɁA���̍s�ֈڍs
		if (c == '\n' || position >= SCRIPT_MAX_LINE-1)
		{
			//\0�𕶎���̍Ō�ɕt����
			ScriptInfo->script[ScriptInfo->currentLine][position] = '\0';
			// ���̍s�ֈړ�
			ScriptInfo->currentLine++;

			// �������݈ʒu��0��
			position = 0;
		}
		else
		{
			// ��������
			ScriptInfo->script[ScriptInfo->currentLine][position] = c;

			// �������������݈ʒu�����炷
			position++;
		}
	}

	// �ő�s��
	ScriptInfo->MaxLineNumber = ScriptInfo->currentLine;

	// �ǂݍ��݂̒��̍s��0�ɂ���
	ScriptInfo->currentLine = 0;

	// �X�N���v�g�t�@�C�����̐ݒ�
	ScriptInfo->filename = (char*) filename;

	return 0;
}


/*******************************************************/
/*@name code  : char ���{�ꂩ���肳��镶              */
/*******************************************************/
int isJapaneseCharactor(unsigned char code)
{
	if ((code >= 0x81 && code <= 0x9F) || (code >= 0xE0 && code <= 0xEF))		// SHIFT_JIS��2�o�C�g�Ȃ̂ŏ��1�o�C�g�����{��ł���Ɣ���Ő؂�΂���
	{
		return 1;
	}
	return 0;
}


/*******************************************************/
/*@name message : char �\�������镶����                */
/*@name start   : int  �J�n�ʒu                        */
/*@name len     : int  �\��������(1�s�ƌ��Ă���������) */
/*******************************************************/
void writeSubString(char* message, char** g_message_buffer,int start, int len, int bufferLine)
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
/// <summary>
///		�����\���֐�
/// </summary>
/// <param name="PosX">�����\�� X���W</param>
/// <param name="PosY">�����\�� Y���W</param>
/// <param name="g_message_buffer">�\������</param>
/// <param name="color">�����̐F</param>
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

	// strtok���g����copySrc��delim��؂�ŕ�������
	for (i = 0; i < splitNum; i++)
	{
		if ((dest[i] = std::strtok(cp, delim)) == NULL)
			break;

		// 2��ڂ�strtoc���Ăяo���Ƃ���cp��NULL�ɂ���
		cp = NULL;
	}

	// �����㕶����̍Ō�ɂ�NULL�����ĕ�������
	dest[i] = NULL;
}

int decodeScript(const char* scriptMessage)
{
	// �������ꂽ�X�N���v�g
	char* message[100];
	// �����񕪊����̋�؂蕶��
	const char* delim = " ";

	splitString((char*)scriptMessage, message, delim, 100);

	// �����Ɏ��s���Ă����ꍇ
	if (message[0] == NULL)
	{
		return 0;
	}

	// script�̎d�l
	// @@message ������
	// -- ����������b�Z�[�W�Ƃ��ĕ\������
	//
	// @@drawgraph x y filename
	// -- filename�Ŏw�肵���摜�t�@�C����(x,y)�̈ʒu�ŕ\��
	if (std::strncmp(message[0], "@@message", SCRIPT_MAX_STRING_LENGTH) == 0)
	{
		// �����ɕ������\������v���O����������
	}
	else if (std::strncmp(message[0], "@@drawgraph", SCRIPT_MAX_STRING_LENGTH) == 0)
	{
		// �摜�̕\�������� filename��map�ŊǗ����āA���O�����������悤�ɂ���
		// �� : �L�� -> rouka
		// map�̓t�@�C���ǂݍ��݂��č��悤�ɂ���B
		// 
	}
}