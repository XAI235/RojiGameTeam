#include <list>

#include "DxLib.h"
#include "Fps.h"
#include "CalcUtils.h"

const static int LIST_LEN_MAX = 120;		//	�ő�120�t���[���܂őҋ@
const static int FPS = 60;
const static int UPINTVL = 60;

Fps::Fps() : _counter(0), _fps(0)
{

}

void Fps::wait()
{
	_counter++;
	Sleep(getWaiteTime());
	regist();
	if (_counter == UPINTVL)
	{
		updateAverage();
		_counter = 0;
	}
}

void Fps::draw() const
{
	if (_fps == 0)
	{
		return;
	}

	DrawFormatString(0, 0, GetColor(255, 255, 255), "%04.1ffps", _fps);
}

void Fps::updateAverage()
{
	int len = (int)_list.size();
	if (len < LIST_LEN_MAX)
	{
		return;						//	�܂����Ϗo�����Ԃ���Ȃ�
	}

	int tookTime = _list.back() - _list.front();
	float average = (float)tookTime / (len - 1);			// ����
	if (average == 0)				//	0����X������˂���
		return;

	_fps = CalcUtils::roundPoint(1000 / average, 2);
}

void Fps::regist()
{
	_list.push_back(GetNowCount());		//	���݂̎������L��
	if (_list.size() > LIST_LEN_MAX)
	{
		_list.pop_front();
	}
	
}

unsigned Fps::getWaiteTime() const
{
	int len = (int)_list.size();
	if (len == 0)
	{
		return 0;
	}

	int shouldTookTime = (int)(1000 / 60.f * (len));			//	�v�Z�ォ����ׂ�����
	int actuallyTookTime = GetNowCount() - _list.front();		//	���ۂɂ�����������
	int waitTime = shouldTookTime - actuallyTookTime;			//	�҂ׂ�����
	waitTime = waitTime > 0 ? waitTime : 0;	
	return (unsigned)(waitTime);
}
