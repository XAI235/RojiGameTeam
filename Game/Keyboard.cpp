#include "stdafx.h"


Keyboard::Keyboard()
{
	_pressingCount.fill(0);
	_releasingCount.fill(0);
}

bool Keyboard::update()
{
	char nowKeyStatus[KEY_NUM];
	GetHitKeyStateAll(nowKeyStatus);			// 今のキー入力状態を取得

	for (int i = 0; i < KEY_NUM; i++)
	{
		if (nowKeyStatus[i] != 0)				// i版のキーが押されていたら
		{
			if (_releasingCount[i] > 0)			// 端されカウンタが0より大きければ
			{
				_releasingCount[i] = 0;			// 0に戻す
			}
			_pressingCount[i]++;
		}
		else									// i番目のキーが離されいたら
		{
			if (_pressingCount[i] > 0)			// 押されカウンタが0より多きれば
			{
				_pressingCount[i] = 0;			// 0に戻す
			}

			_releasingCount[i]++;				// 離されカウンタを増やす
		}
	}

	return true;
}

/*!
@brief keyCodeのキーが押されているフレーム数を返す
*/
int Keyboard::getPressingCount(int keyCode)
{
	if (!isAvailableCode(keyCode))
	{
		return -1;
	}

	return _pressingCount[keyCode];
}

/*!
@brief keyCodeのキーが離されいるフレーム数を返す
*/
int Keyboard::getReleasingCount(int keyCode)
{
	if (!isAvailableCode(keyCode))
	{
		return -1;
	}
	return _releasingCount[keyCode];
}

/*!
@breief　keyCodeが有効な値か否か返す
*/
bool Keyboard::isAvailableCode(int keyCode)
{
	if (!(0 <= keyCode && keyCode < KEY_NUM))
	{
		return false;
	}

	return true;
}