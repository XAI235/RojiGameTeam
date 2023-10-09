#pragma once

#include "ScriptInformation.h"

class Parameter
{
public:

	Parameter() = default;
	virtual ~Parameter() = default;
	Parameter operator=(const Parameter& parameter);

	const static int Error = -1;

	void initialize();


	int getBGMVolume();
	
private:
	bool WindowScreenMode;				//	�X�N���[�����[�h TRUE�Ȃ�E�B���h�E���[�h�AFALSE�Ȃ�t���X�N���[��
	int Color_Bit;						//	�F�̃r�b�g���A�ʏ�Ȃ��32bit�A�y�ʉ�����Ȃ��16bit�ɕύX�\
	int Window_Hight;					//	�E�B���h�E�T�C�Y ����
	int Window_Width;					//	�E�B���h�E�T�C�Y ��
	int BGMVolume;						//	BGM�̃{�����[�� 0�`100
	int VoiceVolume;					//	�{�C�X�̃{�����[�� 0�`100
	ScriptInformation scriptinfo;		//	�V�i���I�̏��
	
	void copy(const Parameter& parameter);

};

/*
	SetAlwaysRunFlag(TRUE);								//	�E�B���h�E���m���A�N�e�B�u�ł����s ������Ȃ�
	SetWindowSizeChangeEnableFlag(TRUE);				//	�E�B���h�E�T�C�Y�����R�ɕύX�\ ������Ȃ�
	SetOutApplicationLogValidFlag(FALSE);				//	���O�o�͂����Ȃ� ������Ȃ�
	SetFullScreenResolutionMode(DX_FSRESOLUTIONMODE_DESKTOP);	//	�t���X�N���[�����ɏc������ێ����� ������Ȃ�
	SetWindowText("�ڂ���̎���");						//	�^�C�g���E�B���h�E������ ������Ȃ�
	ChangeWindowMode(TRUE);								//	�E�B���h�E���[�h�ɕύX
//	SetWindowSizeExtendRate(1.0);						//	�E�B���h�E�T�C�Y��ύX�������ꍇ�͂����ɔ{�����w�肷��
	const int COLOR_BIT = 32;							//	�F��bit���B�ʏ�32�ŗǂ����y������Ȃ��16�ɕύX����
	SetGraphMode(Define::Window_Width, Define::Window_Hight, COLOR_BIT);					//	�Q�[����ʂ̉�͓x�̐ݒ������
	if (DxLib_Init())
	{
		return false;
	}
	SetDrawScreen(DX_SCREEN_BACK);
*/