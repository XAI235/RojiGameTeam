#include "stdafx.h"
#include <stdio.h>
#include <share.h>
#include <windows.h>


#include "Parameter.h"

void Parameter::initialize()
{
	if (_fsopen("./Data/config.dat", "r", _SH_DENYNO) == nullptr)
	{
		// 初めて起動した時のみconfig.datを作成する
		MessageBox(NULL, TEXT("./Data/config.datがないことがわかったよ"), TEXT("メッセージボックス"), MB_OK);
		WindowScreenMode = true;
		BGMVolume = 45;
		scriptinfo.MaxLineNumber = 0;
		scriptinfo.currentLine = 0;
		scriptinfo.filename = NULL;
		//scriptinfo.script = NULL;
		/*scriptinfo.script = new char*[1000];
		for (int i = 0; i < 1000; i++)
		{
			scriptinfo.script[i] = new char[SCRIPT_MAX_STRING_LENGTH];
		}*/
	}
	else
	{
		MessageBox(NULL, TEXT("./Data/config.datがあるよ"), TEXT("メッセージボックス"), MB_OK);
		WindowScreenMode = true;
		BGMVolume = 45;

	}

}


int Parameter::getBGMVolume()
{
	return 255*BGMVolume/100;
}

void Parameter::copy(const Parameter& parameter)
{
	WindowScreenMode = parameter.WindowScreenMode;
	Color_Bit = parameter.Color_Bit;
	Window_Hight = parameter.Window_Hight;
	Window_Width = parameter.Window_Width;
	BGMVolume = parameter.BGMVolume;
	VoiceVolume = parameter.VoiceVolume;

	return;
}


Parameter Parameter::operator=(const Parameter& parameter)
{
	if (this != &parameter)
	{
		copy(parameter);
	}

	return *this;
}
// */