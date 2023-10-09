#include "stdafx.h"


/*
*	@brief	コンストラクタ
*	@param	impl	シーン変更のリスナー
*	@param	parameter	前のシーンから渡されたパラメータ
*/
AbstractScene::AbstractScene(IOnSceneChangedListener* impl, const Parameter& parameter) : _impSceneChanged(impl), g_graphicManager(), g_visibleGraphic()//, param(parameter)
{ 
	initGraphicNode();
}

void AbstractScene::initGraphicNode()
{
	
	//g_graphicManager = new GraphicNode[GRAPHIC_MAX_NUM];
	//g_visibleGraphic = new VisibleGraphicNode[VISIBLE_GRAPHIC_MAX_NUM];
	
	// グラフィック管理初期化
	memset(&g_graphicManager, 0, sizeof(GraphicNode));

	// 表示するグラフィックの管理初期化
	memset(&g_visibleGraphic, 0, sizeof(VisibleGraphicNode));
}

int AbstractScene::getGraphicIdPosition(int id)
{
	for (int i = 0; i < GRAPHIC_MAX_NUM; i++)
	{
		if (g_graphicManager[i].id == id)
		{
			return i;
		}
	}

	return -1;
}

int AbstractScene::getGraphicHandle(int id)
{
	int i = 0;
	for (i = 0; i < GRAPHIC_MAX_NUM; i++)
	{
		if (id == g_graphicManager[i].id)
			return g_graphicManager[i].graphicHandle;
	}
	return -1;
}

int AbstractScene::addGraphicNode(int id, const char* graphicFilename)
{
	int i;
	// idの重複確認
	for (i = 0; i < GRAPHIC_MAX_NUM; i++)
	{
		if (id == g_graphicManager[i].id)
		{
			std::cout << "idが重複しています(id " << id << ")" << std::endl;
			// printf("idが重複しています(id %d)\n", id);
			return -1;
		}
	}

	// 利用していないノードを見つける
	for (i = 0; i < GRAPHIC_MAX_NUM; i++)
	{
		if (g_graphicManager[i].id == 0)
			break;
	}

	// グラフィックノードに空きがない場合
	if (i == GRAPHIC_MAX_NUM)
	{
		std::cout << "グラフィックノードの空きがありません(id " << id << ")" << std::endl;
		// printf("グラフィックノードの空きがありません(id %d)\n".id);
		return -1;
	}

	// idをセット
	g_graphicManager[i].id = id;

	// 画像読み込み
	g_graphicManager[i].graphicHandle = LoadGraph(graphicFilename);

	if (g_graphicManager[i].graphicHandle == -1)
	{
		std::cout << "画像の読み込みに失敗しました(id " << id << ")" << std::endl;
		// printf("画像の読み込みに失敗しました(id %d)\n", id);
		// グラフィックノードを空き状態にする
		g_graphicManager[i].id = 0;
		g_graphicManager[i].graphicHandle = 0;
		return -1;
	}

	return 0;
}

int AbstractScene::removeGraphicNode(int id)
{
	int i;
	for (i = 0; i < GRAPHIC_MAX_NUM; i++)
	{
		// 指定したグラフィックが見つかった
		if (id == g_graphicManager[i].id)
		{
			// データ削除
			g_graphicManager[i].id = 0;
			g_graphicManager[i].graphicHandle = 0;
			return 0;
		}
	}
	// 削除できなかった場合
	return -1;
}

int AbstractScene::removeAllGraphicNode()
{
	for (int i = 0; i < GRAPHIC_MAX_NUM; i++)
	{
		// idが振られている場所なら
		if (g_graphicManager[i].id != 0)
		{
			// データ削除
			g_graphicManager[i].id = 0;
			g_graphicManager[i].graphicHandle = 0;
			return 0;
		}
	}
	// 削除できなかった場合
	return -1;
}

// 画像に画像を表示する
// id二はGraphicNodeのidを指定, graphicIdは今から描画する画像にidをつける
// posX, posYは画像の表示する位置
// drawModeは表示のさせ方, GRAPHIC_MODE_NONE: そのまま表示, GRAPHIC_MODE_FADEIN: フェードイン
// 戻り値 -1 : 失敗　0 : 成功
int AbstractScene::addVisibleGraphic(int id, int graphicId, int posX, int posY, int drawMode)
{
	int i;
	// idからグラフィックハンドルを取得
	int handle = getGraphicHandle(id);

	if (handle == -1)
	{
		std::cout << "ID: " << id << "の画像は登録されていません" << std::endl;
		return -1;
	}

	// graphicIDが重複していないかの確認
	for (i = 0; i < VISIBLE_GRAPHIC_MAX_NUM; i++)
	{
		if (graphicId == g_visibleGraphic[i].graphicId)
		{
			std::cout << "graphic idが重複しています(id " << graphicId << ")" << std::endl;
			return -1;
		}
	}

	// 利用していないノードを見つける
	for (i = 0; i < VISIBLE_GRAPHIC_MAX_NUM; i++)
	{
		if (g_visibleGraphic[i].graphicHandle == 0)
			break;
	}

	if (i == VISIBLE_GRAPHIC_MAX_NUM)
	{
		std::cout << "画面にこれ以上表示できません(id " << graphicId << ")" << std::endl;
		return -1;
	}

	// 情報登録
	// グラフィックハンドル登録
	g_visibleGraphic[i].graphicHandle = handle;
	// graphicIdを登録
	g_visibleGraphic[i].graphicId = graphicId;
	// 座標の指定
	g_visibleGraphic[i].x = posX;
	g_visibleGraphic[i].y = posY;

	// 輝度情報の登録
	switch (drawMode)
	{
	case GRAPHIC_MODE_FADEIN :
		g_visibleGraphic[i].bright = 0;
		break;
	case GRAPHIC_MODE_FADEOUT:
	case GRAPHIC_MODE_NONE:
		g_visibleGraphic[i].bright = 255;
		break;
	}
		
	
	// モード
	g_visibleGraphic[i].mode = drawMode;

	return 0;
}

void AbstractScene::drawVisibleGraphic()
{
	int i;
	for (i = 0; i < VISIBLE_GRAPHIC_MAX_NUM; i++)
	{
		if (g_visibleGraphic[i].graphicId != 0)
		{
			if (g_visibleGraphic[i].mode == GRAPHIC_MODE_FADEIN)
			{
				// 輝度を上げる
				g_visibleGraphic[i].bright += GRAPHIC_FADEIN_FADEOUT_SPEED;
				// 輝度が最大値に達したとき
				if (g_visibleGraphic[i].bright > GRAPHIC_MAX_BRIGHT)
				{
					g_visibleGraphic[i].bright = GRAPHIC_MAX_BRIGHT;
					// フェードイン解除
					g_visibleGraphic[i].mode = GRAPHIC_MODE_NONE;
 				}
			}
			else if(g_visibleGraphic[i].mode == GRAPHIC_MODE_FADEOUT)
			{
				// 輝度を下げる
				g_visibleGraphic[i].bright -= GRAPHIC_FADEIN_FADEOUT_SPEED;
				// 輝度が0以下になった場合
				if (g_visibleGraphic[i].bright < GRAPHIC_MIN_BRIGHT)
				{
					g_visibleGraphic[i].bright = GRAPHIC_MIN_BRIGHT;
					// フェードアウト解除
					g_visibleGraphic[i].mode = GRAPHIC_MODE_NONE;
				}
			}
			// 輝度をセット
			SetDrawBright(g_visibleGraphic[i].bright, g_visibleGraphic[i].bright, g_visibleGraphic[i].bright);

			// アルファブレンドを行う
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, g_visibleGraphic[i].bright);
			// 指定した座標に画像描画
			
			DrawGraph(g_visibleGraphic[i].x, g_visibleGraphic[i].y, g_visibleGraphic[i].graphicHandle, TRUE);

			//std::cout << "Index" << i << " Image Bright : " << g_visibleGraphic[i].bright << std::endl;
		}
	}

	// 輝度情報をデフォルトに戻しておく
	SetDrawBright(GRAPHIC_MAX_BRIGHT, GRAPHIC_MAX_BRIGHT, GRAPHIC_MAX_BRIGHT);

	// ブレンドモードを元に戻しておく
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, GRAPHIC_MAX_BRIGHT);

}

int AbstractScene::getVisibleGraphicIdPosition(int id)
{
	for (int i = 0; i < VISIBLE_GRAPHIC_MAX_NUM; i++)
	{
		if (g_visibleGraphic[i].graphicId == id)
		{
			return i;
		}
	}

	return -1;
}

int AbstractScene::removeVisibleGraphic(int graphicId)
{
	int i;
	for (i = 0; i < VISIBLE_GRAPHIC_MAX_NUM; i++)
	{
		// 指定したグラフィックが見つかった
		if(graphicId == g_visibleGraphic[i].graphicId)
		{
			// データの削除
			g_visibleGraphic[i].graphicHandle = 0;
			g_visibleGraphic[i].graphicId = 0;
			g_visibleGraphic[i].x = 0;
			g_visibleGraphic[i].y = 0;
			return 0;
		}
	}
	// 削除できなかった場合
	return -1;
}

int AbstractScene::removeAllVisibleGraphic()
{
	for (int i = 0; i < VISIBLE_GRAPHIC_MAX_NUM; i++)
	{
		// 指定したグラフィックが見つかった
		if (g_visibleGraphic[i].graphicId != 0)
		{
			// データの削除
			g_visibleGraphic[i].graphicHandle = 0;
			g_visibleGraphic[i].graphicId = 0;
			g_visibleGraphic[i].x = 0;
			g_visibleGraphic[i].y = 0;
			return 0;
		}
	}
	// 削除できなかった場合
	return -1;
}

int AbstractScene::checkGraphic()
{
	int i;
	for (i = 0; i < GRAPHIC_MAX_NUM; i++)
	{
		if (g_graphicManager[i].id != 0)		// 画像が登録されていれば
		{
			return 1;								// 1を返す
		}
	}
	return 0;
}

int AbstractScene::checkVisibleGraphic()
{
	int i;
	for (i = 0; i < VISIBLE_GRAPHIC_MAX_NUM; i++)
	{
		if (g_visibleGraphic[i].graphicId != 0)		// 画像が登録されていれば
		{
			return 1;								// 1を返す
		}
	}
	return 0;
}

