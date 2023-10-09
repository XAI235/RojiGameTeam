#include "stdafx.h"

#define HOROTAN 1
#define XAI 2

#define HOROTAN_X 270
#define HOROTAN_Y 146
#define XAI_X 256
#define XAI_Y 245
IntroductionScene::IntroductionScene(IOnSceneChangedListener* impl, const Parameter& parameter) : AbstractScene(impl, parameter)
{
	param = parameter;
	NowDrawLogos = HOROTAN;
	counter = 0;
	NextToLogos = FALSE;
	pX = new int[2];
	pY = new int[2];
	pX[0] = HOROTAN_X;
	pX[1] = XAI_X;
	pY[0] = HOROTAN_X;
	pY[1] = XAI_Y;
	addGraphicNode(HOROTAN, "./Data/image/TestPicture/rogos/horotan_rogo.jpg");
	addGraphicNode(XAI, "./Data/image/TestPicture/rogos/xai_rogo_resize.png");

	addVisibleGraphic(HOROTAN, HOROTAN, HOROTAN_X, HOROTAN_Y, GRAPHIC_MODE_FADEIN);

}

void IntroductionScene::update()
{
	if (counter >= 555 && !NextToLogos)	// ‘å‘Ì9•b‚®‚ç‚¢
	{
		NextToLogos = TRUE;
		g_visibleGraphic[getVisibleGraphicIdPosition(NowDrawLogos)].mode = GRAPHIC_MODE_FADEOUT;
	}

	counter++;

	if (NextToLogos && g_visibleGraphic[getVisibleGraphicIdPosition(NowDrawLogos)].bright <= 0)
	{
		NextToLogos = 0;
		removeAllVisibleGraphic();
		NowDrawLogos++;
		counter = 0;
		addVisibleGraphic(NowDrawLogos, NowDrawLogos, pX[NowDrawLogos - 1] , pY[NowDrawLogos-1], GRAPHIC_MODE_FADEIN);
		
	}

	if (NowDrawLogos == 3)
	{
		removeAllGraphicNode();
		const bool stackClear = TRUE;
		_impSceneChanged->onSceneChanged(eScene::Title , param, stackClear);
	}
	
}

void IntroductionScene::draw()
{
	drawVisibleGraphic();
}

