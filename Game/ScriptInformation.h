#pragma once

#include "Define.h"

//#define SCRIPT_MAX_STRING_LENGTH 300

typedef struct ScriptInformation_tag
{
	int MaxLineNumber;					//	�X�N���v�g�s��
	int currentLine;					//	���݂̍s��
	char* filename;						//	�t�@�C����
	char script[SCRIPT_MAX_LINE][SCRIPT_MAX_STRING_LENGTH];				//	�X�N���v�g

}ScriptInformation;