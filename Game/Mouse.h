#pragma once

#include "Singleton.h"

class Mouse : public Singleton<Mouse>
{
	Mouse();
	friend Singleton<Mouse>;

public:
	static constexpr int LEFT_CLICK = 0;
	static constexpr int RIGHT_CLICK = 1;

	bool update();								//	更新
	int getPressingCount(int keyCode);			//	keyCodeのキーが押されているフレーム数を取得
	int GetReleasingCount(int keyCode);			//	keyCodeのキーが離されているフレーム数を取得
	int isContainMousePointer(int x, int y, int width, int height);
	int getX();
	int getY();

private:
	static constexpr int KEY_NUM = 8;			//	キー総数
	int _x, _y;
	int _buttonPressingCount[KEY_NUM];			//	押されカウンタ
	int _buttounReleasingCount[KEY_NUM];		//	離されカウンタ

	bool isAvailableCode(int keyCode);			//	keyCodeが有効なキー番号か問い合わせ
};

