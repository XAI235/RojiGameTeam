#include "stdafx.h"

#include "Fade.h"

/*-------------------------------------------------------------*/
/*  ƒRƒ“ƒXƒgƒ‰ƒNƒ^											@ */
/*-------------------------------------------------------------*/
/*
Fade::Fade()
{
	bright = 0;				//‰Šú’l
}

bool Fade::Fadeout(float fade_speed, int r, int g, int b)
{
	ClearDrawScreen();
	SetDrawBright((int)bright, (int)bright, (int)bright);

	DrawBox(0, 0, 1280, 720, GetColor(r, g, b), true);

	//‹P“x‚ª0ˆÈ‰º‚É‚È‚Á‚½‚ç
	if (bright < 0)
	{
		//@‰æ–Ê‚Ì‹P“x‚ğ–ß‚µ‚Ä‚¨‚­
		SetDrawBright(255, 255, 255);

		// true‚ğ•Ô‚·
		return true;
	}
	else
	{
		// ‹P“x‚ğ‰ÁZ
		bright -= fade_speed;
	}

	return false;
}

bool Fade::Fadein(float fade_speed, int r, int g, int b)
{
	ClearDrawScreen();
	SetDrawBright((int)bright, (int)bright, (int)bright);

	DrawBox(0, 0, 1280, 720, GetColor(r, g, b), true);

	//‹P“x‚ª255‚ğ’´‚¦‚½‚ç
	if (bright > 255)
	{
		//@‰æ–Ê‚Ì‹P“x‚ğ–ß‚µ‚Ä‚¨‚­
		SetDrawBright(255, 255, 255);

		// true‚ğ•Ô‚·
		return true;
	}
	else
	{
		// ‹P“x‚ğ‰ÁZ
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

	//‹P“x‚ª0ˆÈ‰º‚É‚È‚Á‚½‚ç
	if (bright < 0)
	{
		//@‰æ–Ê‚Ì‹P“x‚ğ–ß‚µ‚Ä‚¨‚­
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 0);
		bright = 0;
		// true‚ğ•Ô‚·
		return true;
	}
	else
	{
		// ‹P“x‚ğ‰ÁZ
		bright -= fade_speed;
	}

	return false;
}

bool Fade::Fadein(int const& PictHandle, float& bright, float fade_speed)
{
	ClearDrawScreen();

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, bright);
	DrawGraph(0, 0, PictHandle, TRUE);

	//‹P“x‚ª255ˆÈã‚É‚È‚Á‚½‚ç
	if (bright > 255)
	{
		//@‰æ–Ê‚Ì‹P“x‚ğ–ß‚µ‚Ä‚¨‚­
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
		// true‚ğ•Ô‚·

		bright = 255;
		return true;
	}
	else
	{
		// ‹P“x‚ğ‰ÁZ
		bright += fade_speed;
	}

	return false;
}

/*bool Fade::Fadeout(float& bright, float fade_speed, int r, int g, int b)
{
	ClearDrawScreen();
	SetDrawBright((int)bright, (int)bright, (int)bright);

	DrawBox(0, 0, 1280, 720, GetColor(r, g, b), true);

	//‹P“x‚ª0ˆÈ‰º‚É‚È‚Á‚½‚ç
	if (bright < 0)
	{
		//@‰æ–Ê‚Ì‹P“x‚ğ–ß‚µ‚Ä‚¨‚­
		SetDrawBright(0, 0, 0);

		// true‚ğ•Ô‚·
		return true;
	}
	else
	{
		// ‹P“x‚ğ‰ÁZ
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


	//‹P“x‚ª255‚ğ’´‚¦‚½‚ç
	if (bright > 255)
	{
		//@‰æ–Ê‚Ì‹P“x‚ğ–ß‚µ‚Ä‚¨‚­
		SetDrawBright(255, 255, 255);

		// true‚ğ•Ô‚·
		return true;
	}
	else
	{
		// ‹P“x‚ğ‰ÁZ
		bright += fade_speed;
	}

	return false;
}
//*/