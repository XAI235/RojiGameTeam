#pragma once

#include "Define.h"

//#define SCRIPT_MAX_STRING_LENGTH 300

typedef struct ScriptInformation_tag
{
	int MaxLineNumber;					//	スクリプト行数
	int currentLine;					//	現在の行数
	char* filename;						//	ファイル名
	char script[SCRIPT_MAX_LINE][SCRIPT_MAX_STRING_LENGTH];				//	スクリプト

}ScriptInformation;