#include "TitleScene.h"
#include "IOnChangeListener.h"
#include "DxLib.h"

TitleScene::TitleScene(IOnSceneChangedListener* impl, const Parameter& parameter) : AbstractScene(impl, parameter)
{
	GrMenu = LoadGraph("./Data/image/bg/menu.png");
	SdMenu = LoadSoundMem("./Data/bgm/title.wav");
}

void TitleScene::update()
{
}

void TitleScene::draw()
{
	if (CheckSoundMem(SdMenu) == 0)
	{
		PlaySoundMem(SdMenu, DX_PLAYTYPE_BACK);
	}

	DrawGraph(0, 0, GrMenu, TRUE);
}
