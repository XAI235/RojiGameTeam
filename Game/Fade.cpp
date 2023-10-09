#include "stdafx.h"

#include "Fade.h"

/*-------------------------------------------------------------*/
/*  コンストラクタ											　 */
/*-------------------------------------------------------------*/
/*
Fade::Fade()
{
	bright = 0;				//初期値
}

bool Fade::Fadeout(float fade_speed, int r, int g, int b)
{
	ClearDrawScreen();
	SetDrawBright((int)bright, (int)bright, (int)bright);

	DrawBox(0, 0, 1280, 720, GetColor(r, g, b), true);

	//輝度が0以下になったら
	if (bright < 0)
	{
		//　画面の輝度を戻しておく
		SetDrawBright(255, 255, 255);

		// trueを返す
		return true;
	}
	else
	{
		// 輝度を加算
		bright -= fade_speed;
	}

	return false;
}

bool Fade::Fadein(float fade_speed, int r, int g, int b)
{
	ClearDrawScreen();
	SetDrawBright((int)bright, (int)bright, (int)bright);

	DrawBox(0, 0, 1280, 720, GetColor(r, g, b), true);

	//輝度が255を超えたら
	if (bright > 255)
	{
		//　画面の輝度を戻しておく
		SetDrawBright(255, 255, 255);

		// trueを返す
		return true;
	}
	else
	{
		// 輝度を加算
		bright += fade_speed;
	}

	return false;
}
//*/

Fade::~Fade()
{
}

bool Fade::Fadeout(int const& PictHandle, float &bright, float fade_speed)
{
	ClearDrawScreen();

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, bright);
	DrawGraph(0, 0, PictHandle, TRUE);

	//輝度が0以下になったら
	if (bright < 0)
	{
		//　画面の輝度を戻しておく
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 0);
		bright = 0;
		// trueを返す
		return true;
	}
	else
	{
		// 輝度を加算
		bright -= fade_speed;
	}

	return false;
}

bool Fade::Fadein(int const& PictHandle, float& bright, float fade_speed)
{
	ClearDrawScreen();

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, bright);
	DrawGraph(0, 0, PictHandle, TRUE);

	//輝度が255以上になったら
	if (bright > 255)
	{
		//　画面の輝度を戻しておく
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
		// trueを返す

		bright = 255;
		return true;
	}
	else
	{
		// 輝度を加算
		bright += fade_speed;
	}

	return false;
}

/*bool Fade::Fadeout(float& bright, float fade_speed, int r, int g, int b)
{
	ClearDrawScreen();
	SetDrawBright((int)bright, (int)bright, (int)bright);

	DrawBox(0, 0, 1280, 720, GetColor(r, g, b), true);

	//輝度が0以下になったら
	if (bright < 0)
	{
		//　画面の輝度を戻しておく
		SetDrawBright(0, 0, 0);

		// trueを返す
		return true;
	}
	else
	{
		// 輝度を加算
		bright -= fade_speed;
	}

	return false;
}

bool Fade::Fadein(float& bright, float fade_speed, int r, int g, int b)
{
	ClearDrawScreen();
	SetDrawBright((int)bright, (int)bright, (int)bright);

	
	DrawBox(0, 0, 1280, 720, GetColor(r, g, b), true);

	std::cout << bright << std::endl;


	//輝度が255を超えたら
	if (bright > 255)
	{
		//　画面の輝度を戻しておく
		SetDrawBright(255, 255, 255);

		// trueを返す
		return true;
	}
	else
	{
		// 輝度を加算
		bright += fade_speed;
	}

	return false;
}
//*/