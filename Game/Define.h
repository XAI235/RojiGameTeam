#pragma once

#ifndef INCLUDE_DEFINE
#define INCLUDE_DEFINE

/*
#define MESSAGE_FONT_SIZE 32
#define NAME_FONT_SIZE 24
#define MESSAGE_MAX_LENGTH = 27;						// ��s�ŕ\������ő啶����
#define MESSAGE_MAX_LINE = 3;							// �\������ő�s��
#define BETWEEN_LINE = 50;								// �s�Ԃ̃T�C�Y
// */

// �X�N���v�g�ő�s��
#define SCRIPT_MAX_LINE			 1000
// �X�N���v�g�ő啶����
#define SCRIPT_MAX_STRING_LENGTH 300

// �O���t�B�b�N�̍ő�o�^��
#define GRAPHIC_MAX_NUM 10
// ��ʂɕ\���ł���ő�摜��
#define VISIBLE_GRAPHIC_MAX_NUM 10

// �t�F�[�h�C���@�t�F�[�h�A�E�g�̃X�s�[�h
#define GRAPHIC_FADEIN_FADEOUT_SPEED 1
// �P�x�̍ő�l
#define GRAPHIC_MAX_BRIGHT 255
// �P�x�̍ŏ��l
#define GRAPHIC_MIN_BRIGHT 0
// �摜�`�惂�[�h
#define GRAPHIC_MODE_NONE 0
#define GRAPHIC_MODE_FADEIN 1
#define GRAPHIC_MODE_FADEOUT 2

#define GAME_TEXT_FARST_CHAPTER "./Data/scenario/Scenario_data.txt"

#endif

class Define final
{
public:
	const static int Window_Width;
	const static int Window_Hight;

	//const static int SCRIPT_MAX_STRING_LENGTH;
};

