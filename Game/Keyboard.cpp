#include "stdafx.h"


Keyboard::Keyboard()
{
	_pressingCount.fill(0);
	_releasingCount.fill(0);
}

bool Keyboard::update()
{
	char nowKeyStatus[KEY_NUM];
	GetHitKeyStateAll(nowKeyStatus);			// ���̃L�[���͏�Ԃ��擾

	for (int i = 0; i < KEY_NUM; i++)
	{
		if (nowKeyStatus[i] != 0)				// i�ł̃L�[��������Ă�����
		{
			if (_releasingCount[i] > 0)			// �[����J�E���^��0���傫�����
			{
				_releasingCount[i] = 0;			// 0�ɖ߂�
			}
			_pressingCount[i]++;
		}
		else									// i�Ԗڂ̃L�[�������ꂢ����
		{
			if (_pressingCount[i] > 0)			// ������J�E���^��0��葽�����
			{
				_pressingCount[i] = 0;			// 0�ɖ߂�
			}

			_releasingCount[i]++;				// ������J�E���^�𑝂₷
		}
	}

	return true;
}

/*!
@brief keyCode�̃L�[��������Ă���t���[������Ԃ�
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
@brief keyCode�̃L�[�������ꂢ��t���[������Ԃ�
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
@breief�@keyCode���L���Ȓl���ۂ��Ԃ�
*/
bool Keyboard::isAvailableCode(int keyCode)
{
	if (!(0 <= keyCode && keyCode < KEY_NUM))
	{
		return false;
	}

	return true;
}