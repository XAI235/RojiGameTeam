#include "SystemMain.h"
#include "DxLib.h"

#include "Looper.h"
#include "Define.h"
#include "Parameter.h"

/*!
*	@brief	DX���C�u������Q�[���̏�������
*/

bool SystemMain::initialize() const
{
	SetAlwaysRunFlag(TRUE);								//	�E�B���h�E���m���A�N�e�B�u�ł����s
	SetWindowSizeChangeEnableFlag(TRUE);				//	�E�B���h�E�T�C�Y�����R�ɕύX�\
	SetOutApplicationLogValidFlag(FALSE);				//	���O�o�͂����Ȃ�
	SetFullScreenResolutionMode(DX_FSRESOLUTIONMODE_DESKTOP);	//	�t���X�N���[�����ɏc������ێ�����
	SetWindowText("�ڂ���̎���");				//	�^�C�g���E�B���h�E������
	ChangeWindowMode(TRUE);								//	�E�B���h�E���[�h�ɕύX
//	SetWindowSizeExtendRate(1.0);						//	�E�B���h�E�T�C�Y��ύX�������ꍇ�͂����ɔ{�����w�肷��
	const int COLOR_BIT = 32;							//	�F��bit���B�ʏ�32�ŗǂ����y������Ȃ��16�ɕύX����
	SetGraphMode(Define::Window_Width, Define::Window_Hight, COLOR_BIT);					//	�Q�[����ʂ̉�͓x�̐ݒ������
	if (DxLib_Init())
	{
		return false;
	}
	SetDrawScreen(DX_SCREEN_BACK);


    return true;
}

/*!
*	@brief	���C������
*/
void SystemMain::main() const
{

	Looper looper;
	
	while (!ScreenFlip() && !ProcessMessage() && !ClearDrawScreen())
	{
		if (!looper.loop())
		{
			break;
		}
	}
}

/*
*	@brief	DX���C�u������Q�[���̏I������
*/
void SystemMain::finalize() const
{
	DxLib_End();
}
