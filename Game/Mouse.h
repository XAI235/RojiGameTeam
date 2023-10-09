#pragma once

#include "Singleton.h"

class Mouse : public Singleton<Mouse>
{
	Mouse();
	friend Singleton<Mouse>;

public:
	static constexpr int LEFT_CLICK = 0;
	static constexpr int RIGHT_CLICK = 1;

	bool update();								//	�X�V
	int getPressingCount(int keyCode);			//	keyCode�̃L�[��������Ă���t���[�������擾
	int GetReleasingCount(int keyCode);			//	keyCode�̃L�[��������Ă���t���[�������擾
	int isContainMousePointer(int x, int y, int width, int height);
	int getX();
	int getY();

private:
	static constexpr int KEY_NUM = 8;			//	�L�[����
	int _x, _y;
	int _buttonPressingCount[KEY_NUM];			//	������J�E���^
	int _buttounReleasingCount[KEY_NUM];		//	������J�E���^

	bool isAvailableCode(int keyCode);			//	keyCode���L���ȃL�[�ԍ����₢���킹
};

