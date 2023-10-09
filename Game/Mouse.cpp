#include "stdafx.h"

Mouse::Mouse() : _buttonPressingCount(), _buttounReleasingCount(), _x(), _y()
{
}

bool Mouse::update()
{
	int nowButtonState = GetMouseInput();
	GetMousePoint(&_x, &_y);
	for (int i = 0; i < KEY_NUM; i++)
	{
		if ((nowButtonState >> i) & 1)				//	i�Ԗڂ̃{�^����������Ă�����
		{
			if (_buttounReleasingCount[i] > 0)		//	������J�E���^��0���傫�����
				_buttounReleasingCount[i] = 0;		//	0�ɖ߂�

			_buttonPressingCount[i]++;				//	�����Ă�
		}
		else
		{
			if (_buttonPressingCount[i] > 0)			//	i�Ԗڂ̃L�[��������Ă�����
				_buttonPressingCount[i] = 0;

			_buttounReleasingCount[i]++;					// ������J�E���^�𑝂₷
		}
	}

	return true;
}

// keyCode�̃L�[��������Ă���t���[������Ԃ�
int Mouse::getPressingCount(int keyCode)
{
	if (!isAvailableCode(keyCode))
	{
		return -1;
	}
	return _buttonPressingCount[keyCode];
}

// keyCode�̃L�[��������Ă���t���[������Ԃ�
int Mouse::GetReleasingCount(int keyCode)
{
	if (!isAvailableCode(keyCode))
	{
		return -1;
	}
	return _buttounReleasingCount[keyCode];
}

int Mouse::isContainMousePointer(int x, int y, int width, int height)
{
	if ((_x >= x && _x <= x + width) &&(_y >= y && _y <= y + height))
	{
		return 1;
	}
	return 0;
}

int Mouse::getX()
{
	return _x;
}

int Mouse::getY()
{
	return _y;
}

// keyCode���L���Ȓl���`�F�b�N
bool Mouse::isAvailableCode(int keyCode)
{
	if (!(0 <= keyCode && keyCode < KEY_NUM))
	{
		return false;
	}

	return true;
}
