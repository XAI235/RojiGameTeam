#pragma once
class Config
{
	int iResolutionMode;					// �t���X�N���[�����̏c����̈ێ�
	int iChangeWindowMode;				// �E�B���h�E���[�h�̃I���I�t
	int iColor_bit;						// �F��bit���B�ʏ�Ȃ�32bit�A�y�ʉ�����Ȃ�16bit�ɕύX
	int iSetDrawScreen;					// �X�N���[���̕`�����w��A��{�͗��`��
	int Window_Width, Window_Hight;

	void Apply_Config();

public:
	Config();							// Config.dat���Ȃ��ꍇ
	Config(int ResolutionMode, int ChangeWindowMode, int Color_bit, int SetDrawScreen, int Width, int Hight);

	
};

