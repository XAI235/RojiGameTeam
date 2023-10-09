#include <Windows.h>
#include <string>

#include "DxLib.h"
#include "Error.h"

void Error::finish(char* errorMessage, LPCTSTR lpszFuncName, int lineN)
{
	char funcName[1024];
	std::sprintf(funcName, "%s", lpszFuncName);

	printf("異常が発声しました。\n%s\n%s (%d)"
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
