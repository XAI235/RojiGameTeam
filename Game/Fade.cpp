#include "stdafx.h"

#include "Fade.h"

/*-------------------------------------------------------------*/
/*  �R���X�g���N�^											�@ */
/*-------------------------------------------------------------*/
/*
Fade::Fade()
{
	bright = 0;				//�����l
}

bool Fade::Fadeout(float fade_speed, int r, int g, int b)
{
	ClearDrawScreen();
	SetDrawBright((int)bright, (int)bright, (int)bright);

	DrawBox(0, 0, 1280, 720, GetColor(r, g, b), true);

	//�P�x��0�ȉ��ɂȂ�����
	if (bright < 0)
	{
		//�@��ʂ̋P�x��߂��Ă���
		SetDrawBright(255, 255, 255);

		// true��Ԃ�
		return true;
	}
	else
	{
		// �P�x�����Z
		bright -= fade_speed;
	}

	return false;
}

bool Fade::Fadein(float fade_speed, int r, int g, int b)
{
	ClearDrawScreen();
	SetDrawBright((int)bright, (int)bright, (int)bright);

	DrawBox(0, 0, 1280, 720, GetColor(r, g, b), true);

	//�P�x��255�𒴂�����
	if (bright > 255)
	{
		//�@��ʂ̋P�x��߂��Ă���
		SetDrawBright(255, 255, 255);

		// true��Ԃ�
		return true;
	}
	else
	{
		// �P�x�����Z
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

	//�P�x��0�ȉ��ɂȂ�����
	if (bright < 0)
	{
		//�@��ʂ̋P�x��߂��Ă���
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 0);
		bright = 0;
		// true��Ԃ�
		return true;
	}
	else
	{
		// �P�x�����Z
		bright -= fade_speed;
	}

	return false;
}

bool Fade::Fadein(int const& PictHandle, float& bright, float fade_speed)
{
	ClearDrawScreen();

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, bright);
	DrawGraph(0, 0, PictHandle, TRUE);

	//�P�x��255�ȏ�ɂȂ�����
	if (bright > 255)
	{
		//�@��ʂ̋P�x��߂��Ă���
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
		// true��Ԃ�

		bright = 255;
		return true;
	}
	else
	{
		// �P�x�����Z
		bright += fade_speed;
	}

	return false;
}

/*bool Fade::Fadeout(float& bright, float fade_speed, int r, int g, int b)
{
	ClearDrawScreen();
	SetDrawBright((int)bright, (int)bright, (int)bright);

	DrawBox(0, 0, 1280, 720, GetColor(r, g, b), true);

	//�P�x��0�ȉ��ɂȂ�����
	if (bright < 0)
	{
		//�@��ʂ̋P�x��߂��Ă���
		SetDrawBright(0, 0, 0);

		// true��Ԃ�
		return true;
	}
	else
	{
		// �P�x�����Z
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


	//�P�x��255�𒴂�����
	if (bright > 255)
	{
		//�@��ʂ̋P�x��߂��Ă���
		SetDrawBright(255, 255, 255);

		// true��Ԃ�
		return true;
	}
	else
	{
		// �P�x�����Z
		bright += fade_speed;
	}

	return false;
}
//*/