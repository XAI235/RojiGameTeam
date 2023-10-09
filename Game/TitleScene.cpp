#include "stdafx.h"

TitleScene::TitleScene(IOnSceneChangedListener* impl, const Parameter& parameter) : AbstractScene(impl, parameter) 
{

	param = parameter;
	NextScene = eScene::None;
	addGraphicNode(TITLE_BACKGROUND, "./Data/image/bg/menu.png");
	addGraphicNode(SELECT_MASK, "./Data/image/system/textwindow/ueninoru.png");	//��ԏ�ɓ���̂�id���ő吔�̈ʒu�ɂ���
	//Picture[0] = LoadGraph("./Data/image/bg/menu.png");
	//Picture[1] = LoadGraph("./Data/image/system/textwindow/ueninoru.png");

	addVisibleGraphic(g_graphicManager[getGraphicIdPosition(TITLE_BACKGROUND)].id, g_graphicManager[getGraphicIdPosition(TITLE_BACKGROUND)].id, 0, 0, GRAPHIC_MODE_FADEIN);
	BGM = LoadSoundMem("./Data/bgm/title.wav");
	bright = 0;
}

void TitleScene::update()
{
	
	if (checkGraphic() == 0)
	{
		addGraphicNode(TITLE_BACKGROUND, "./Data/image/bg/menu.png");
	}

	if (checkVisibleGraphic() == 0)
	{
		addVisibleGraphic(g_graphicManager[getGraphicIdPosition(TITLE_BACKGROUND)].id, g_graphicManager[getGraphicIdPosition(TITLE_BACKGROUND)].id, 0, 0, GRAPHIC_MODE_FADEIN);
	}
	// */

	if (Mouse::getIns()->isContainMousePointer(35, 382, 300, 49))	// ���߂���
	{
		int i;
		i = getGraphicIdPosition(SELECT_MASK);
		if (i != -1)
		{
			addVisibleGraphic(g_graphicManager[i].id, g_graphicManager[i].id, -300, 382, GRAPHIC_MODE_NONE);
		}

		if (Mouse::getIns()->getPressingCount(Mouse::LEFT_CLICK) > 0)
		{
			g_visibleGraphic[getGraphicIdPosition(TITLE_BACKGROUND)].mode = GRAPHIC_MODE_FADEOUT;
			NextScene = eScene::Game;
		}
	}
	else if (Mouse::getIns()->isContainMousePointer(35, 462, 300, 49))	// ��������
	{
		int i;
		i = getGraphicIdPosition(SELECT_MASK);
		if (i != -1)
		{
			addVisibleGraphic(g_graphicManager[i].id, g_graphicManager[i].id, -300, 462, GRAPHIC_MODE_NONE);
		}

		if (Mouse::getIns()->getPressingCount(Mouse::LEFT_CLICK) > 0)
		{
			MessageBox(NULL, TEXT("�܂���������ĂȂ���"), TEXT("���b�Z�[�W�{�b�N�X"), MB_OK);
		}
	}
	else if (Mouse::getIns()->isContainMousePointer(35, 542, 300, 49))	// �ݒ�
	{
		int i;
		i = getGraphicIdPosition(SELECT_MASK);
		if (i != -1)
		{
			addVisibleGraphic(g_graphicManager[i].id, g_graphicManager[i].id, -300, 542, GRAPHIC_MODE_NONE);
		}

		if (Mouse::getIns()->getPressingCount(Mouse::LEFT_CLICK) > 0)
		{
			MessageBox(NULL, TEXT("�܂���������ĂȂ���"), TEXT("���b�Z�[�W�{�b�N�X"), MB_OK);
		}
	}
	else if (Mouse::getIns()->isContainMousePointer(35, 623, 300, 49)) //
	{
		int i;
		i = getGraphicIdPosition(SELECT_MASK);
		if (i != -1)
		{
			addVisibleGraphic(g_graphicManager[i].id, g_graphicManager[i].id, 250, 623, GRAPHIC_MODE_NONE);
		}

		if (Mouse::getIns()->getPressingCount(Mouse::LEFT_CLICK) > 0)
		{
			DxLib_End();
		}

	}
	else
	{
		int i;
		i = getVisibleGraphicIdPosition(SELECT_MASK);
		if (i != -1)
		{
			removeVisibleGraphic(g_visibleGraphic[i].graphicId);
		}

	}

	if (NextScene != eScene::None && g_visibleGraphic[getGraphicIdPosition(TITLE_BACKGROUND)].bright <= 0)
	{
		StopSoundMem(BGM);
		// removeAllGraphicNode();
		removeAllVisibleGraphic();
		const bool stackClear = false;
		_impSceneChanged->onSceneChanged(NextScene, param, stackClear);
		NextScene = eScene::None;
	}
	
}

void TitleScene::draw()
{
	if (CheckSoundMem(BGM) == 0) 
	{	
		ChangeVolumeSoundMem(param.getBGMVolume(), BGM);
		PlaySoundMem(BGM, DX_PLAYTYPE_BACK);
	}


	drawVisibleGraphic();

	
}