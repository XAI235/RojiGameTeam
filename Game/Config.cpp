#include "stdafx.h"

void Config::Apply_Config()
{

}

Config::Config()
{
	this->iResolutionMode = DX_FSRESOLUTIONMODE_DESKTOP;
	this->iChangeWindowMode = TRUE;
	this->iColor_bit = 32;
	this->iSetDrawScreen = DX_SCREEN_BACK;
	this->Window_Width = 1280;
	this->Window_Hight = 720;
	
}
