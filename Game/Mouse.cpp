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
		if ((nowButtonState >> i) & 1)				//	i番目のボタンが押されていたら
		{
			if (_buttounReleasingCount[i] > 0)		//	離されカウンタが0寄り大きければ
				_buttounReleasingCount[i] = 0;		//	0に戻す

			_buttonPressingCount[i]++;				//	押してんぞ
		}
		else
		{
			if (_buttonPressingCount[i] > 0)			//	i番目のキーが離されていたら
				_buttonPressingCount[i] = 0;

			_buttounReleasingCount[i]++;					// 離されカウンタを増やす
		}
	}

	return true;
}

// keyCodeのキーが押されているフレーム数を返す
int Mouse::getPressingCount(int keyCode)
{
	if (!isAvailableCode(keyCode))
	{
		return -1;
	}
	return _buttonPressingCount[keyCode];
}

// keyCodeのキーが離されているフレーム数を返す
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

// keyCodeが有効な値をチェック
bool Mouse::isAvailableCode(int keyCode)
{
	if (!(0 <= keyCode && keyCode < KEY_NUM))
	{
		return false;
	}

	return true;
}
