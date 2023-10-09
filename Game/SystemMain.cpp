#define _CRT_SECURE_NO_WARNINGS


#include "stdafx.h"

#include "SystemMain.h"



#include "Looper.h"
#include "Define.h"
#include "Parameter.h"

// */
//#include "../../NobelParts/NobelParts.h"



/*!
*	@brief	DX���C�u������Q�[���̏�������
*/
bool SystemMain::initialize() const
{
	// ��Őݒ肵���ݒ�Ɋ֌W�Ȃ��ݒ肷��
	SetAlwaysRunFlag(TRUE);								//	�E�B���h�E���m���A�N�e�B�u�ł����s
	SetWindowSizeChangeEnableFlag(FALSE);				//	�E�B���h�E�T�C�Y�����R�ɕύX�\
	SetOutApplicationLogValidFlag(FALSE);				//	���O�o�͂����Ȃ�
	SetFullScreenResolutionMode(DX_FSRESOLUTIONMODE_DESKTOP);	//	�t���X�N���[�����ɏc������ێ�����
	SetWindowText("�ڂ���̎���");				//	�^�C�g���E�B���h�E������
	ChangeWindowMode(TRUE);								//	�E�B���h�E���[�h�ɕύX
//	SetWindowSizeExtendRate(1.0);						//	�E�B���h�E�T�C�Y��ύX�������ꍇ�͂����ɔ{�����w�肷��
	const int COLOR_BIT = 32;							//	�F��bit���B�ʏ�32�ŗǂ����y������Ȃ��16�ɕύX����
//	SetGraphMode(Define::Window_Width, Define::Window_Hight, COLOR_BIT);					//	�Q�[����ʂ̉�͓x�̐ݒ������
	SetGraphMode(1280, 720, COLOR_BIT);					//	�Q�[����ʂ̉�͓x�̐ݒ������
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

	AllocConsole();
	freopen("CONOUT$", "w", stdout);
	freopen("CONIN$", "r", stdin);

	
	while (!ScreenFlip() && !ProcessMessage() && !ClearDrawScreen())
	{
		//Nobel_Parts();
		
		if (!looper.loop())
		{
			break;
		}

		//std::cout << "X : " << Mouse::getIns()->getX() << " Y : " << Mouse::getIns()->getY() << std::endl;

	}

	FreeConsole();

}

/*
*	@brief	DX���C�u������Q�[���̏I������
*/
void SystemMain::finalize() const
{
	DxLib_End();
}
