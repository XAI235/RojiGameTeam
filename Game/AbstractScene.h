#pragma once

#include "IOnChangeListener.h"

typedef struct GraphicNode_tag
{
	int id;						// 画像のid 利用していない場合は0をセット
	int graphicHandle;			// 画像のグラフィックハンドル
}GraphicNode;

typedef struct VisibleGraphicNode_tag
{
	int graphicId;				// 画像のid GraphicNodeのidとは別物 利用していない場合は0がセットされている
	int graphicHandle;			// 画像のグラフィックハンドル
	int x, y;					// 表示する画像の座標
	int bright;					// 輝度情報
	int mode;					// 画像描画モード 0: 輝度変化なし 1: フェードイン 2: フェードアウト
}VisibleGraphicNode;


class IOnSceneChangedListener;

class AbstractScene
{
private:
protected:
	IOnSceneChangedListener* _impSceneChanged;
	GraphicNode g_graphicManager[GRAPHIC_MAX_NUM];
	VisibleGraphicNode g_visibleGraphic[VISIBLE_GRAPHIC_MAX_NUM];
	void initGraphicNode();
	int getGraphicIdPosition(int id);
	int getGraphicHandle(int id);
	int addGraphicNode(int id, const char* graphicFilename);
	int removeGraphicNode(int graphicId);
	int removeAllGraphicNode();

	int addVisibleGraphic(int id, int graphicId, int posX, int posY, int drawMode);
	void drawVisibleGraphic();
	int getVisibleGraphicIdPosition(int id);
	int removeVisibleGraphic(int graphicId);
	int removeAllVisibleGraphic();

	int checkGraphic();
	int checkVisibleGraphic();

	eScene NextScene;
public:
	AbstractScene(IOnSceneChangedListener* impl,const Parameter &parameter);
	virtual ~AbstractScene() = default;
	virtual void update() = 0;
	virtual void draw() = 0;
	
};

