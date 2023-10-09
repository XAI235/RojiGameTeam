#pragma once

#include "IOnChangeListener.h"

typedef struct GraphicNode_tag
{
	int id;						// �摜��id ���p���Ă��Ȃ��ꍇ��0���Z�b�g
	int graphicHandle;			// �摜�̃O���t�B�b�N�n���h��
}GraphicNode;

typedef struct VisibleGraphicNode_tag
{
	int graphicId;				// �摜��id GraphicNode��id�Ƃ͕ʕ� ���p���Ă��Ȃ��ꍇ��0���Z�b�g����Ă���
	int graphicHandle;			// �摜�̃O���t�B�b�N�n���h��
	int x, y;					// �\������摜�̍��W
	int bright;					// �P�x���
	int mode;					// �摜�`�惂�[�h 0: �P�x�ω��Ȃ� 1: �t�F�[�h�C�� 2: �t�F�[�h�A�E�g
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

