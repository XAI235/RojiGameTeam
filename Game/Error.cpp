#define _CRT_SECURE_NO_WARNINGS

#include <Windows.h>

#include "stdafx.h"
#include "Error.h"

void Error::finish(char* errorMessage, LPCTSTR lpszFuncName, int lineN)
{
	char funcName[1024];
	std::sprintf(funcName, "%s", lpszFuncName);

	printf("àŸèÌÇ™î≠ê∫ÇµÇ‹ÇµÇΩÅB\n%s\n%s (%d)"
		, errorMessage
		, funcName
		, lineN);

	while (!ProcessMessage())
	{
		ClearDrawScreen();
		ScreenFlip();
	}

	DxLib_End();

	exit(99);

}
