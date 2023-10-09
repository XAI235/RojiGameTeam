#include "stdafx.h"


/*
*	@brief	�R���X�g���N�^
*	@param	impl	�V�[���ύX�̃��X�i�[
*	@param	parameter	�O�̃V�[������n���ꂽ�p�����[�^
*/
AbstractScene::AbstractScene(IOnSceneChangedListener* impl, const Parameter& parameter) : _impSceneChanged(impl), g_graphicManager(), g_visibleGraphic()//, param(parameter)
{ 
	initGraphicNode();
}

void AbstractScene::initGraphicNode()
{
	
	//g_graphicManager = new GraphicNode[GRAPHIC_MAX_NUM];
	//g_visibleGraphic = new VisibleGraphicNode[VISIBLE_GRAPHIC_MAX_NUM];
	
	// �O���t�B�b�N�Ǘ�������
	memset(&g_graphicManager, 0, sizeof(GraphicNode));

	// �\������O���t�B�b�N�̊Ǘ�������
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
	// id�̏d���m�F
	for (i = 0; i < GRAPHIC_MAX_NUM; i++)
	{
		if (id == g_graphicManager[i].id)
		{
			std::cout << "id���d�����Ă��܂�(id " << id << ")" << std::endl;
			// printf("id���d�����Ă��܂�(id %d)\n", id);
			return -1;
		}
	}

	// ���p���Ă��Ȃ��m�[�h��������
	for (i = 0; i < GRAPHIC_MAX_NUM; i++)
	{
		if (g_graphicManager[i].id == 0)
			break;
	}

	// �O���t�B�b�N�m�[�h�ɋ󂫂��Ȃ��ꍇ
	if (i == GRAPHIC_MAX_NUM)
	{
		std::cout << "�O���t�B�b�N�m�[�h�̋󂫂�����܂���(id " << id << ")" << std::endl;
		// printf("�O���t�B�b�N�m�[�h�̋󂫂�����܂���(id %d)\n".id);
		return -1;
	}

	// id���Z�b�g
	g_graphicManager[i].id = id;

	// �摜�ǂݍ���
	g_graphicManager[i].graphicHandle = LoadGraph(graphicFilename);

	if (g_graphicManager[i].graphicHandle == -1)
	{
		std::cout << "�摜�̓ǂݍ��݂Ɏ��s���܂���(id " << id << ")" << std::endl;
		// printf("�摜�̓ǂݍ��݂Ɏ��s���܂���(id %d)\n", id);
		// �O���t�B�b�N�m�[�h���󂫏�Ԃɂ���
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
		// �w�肵���O���t�B�b�N����������
		if (id == g_graphicManager[i].id)
		{
			// �f�[�^�폜
			g_graphicManager[i].id = 0;
			g_graphicManager[i].graphicHandle = 0;
			return 0;
		}
	}
	// �폜�ł��Ȃ������ꍇ
	return -1;
}

int AbstractScene::removeAllGraphicNode()
{
	for (int i = 0; i < GRAPHIC_MAX_NUM; i++)
	{
		// id���U���Ă���ꏊ�Ȃ�
		if (g_graphicManager[i].id != 0)
		{
			// �f�[�^�폜
			g_graphicManager[i].id = 0;
			g_graphicManager[i].graphicHandle = 0;
			return 0;
		}
	}
	// �폜�ł��Ȃ������ꍇ
	return -1;
}

// �摜�ɉ摜��\������
// id���GraphicNode��id���w��, graphicId�͍�����`�悷��摜��id������
// posX, posY�͉摜�̕\������ʒu
// drawMode�͕\���̂�����, GRAPHIC_MODE_NONE: ���̂܂ܕ\��, GRAPHIC_MODE_FADEIN: �t�F�[�h�C��
// �߂�l -1 : ���s�@0 : ����
int AbstractScene::addVisibleGraphic(int id, int graphicId, int posX, int posY, int drawMode)
{
	int i;
	// id����O���t�B�b�N�n���h�����擾
	int handle = getGraphicHandle(id);

	if (handle == -1)
	{
		std::cout << "ID: " << id << "�̉摜�͓o�^����Ă��܂���" << std::endl;
		return -1;
	}

	// graphicID���d�����Ă��Ȃ����̊m�F
	for (i = 0; i < VISIBLE_GRAPHIC_MAX_NUM; i++)
	{
		if (graphicId == g_visibleGraphic[i].graphicId)
		{
			std::cout << "graphic id���d�����Ă��܂�(id " << graphicId << ")" << std::endl;
			return -1;
		}
	}

	// ���p���Ă��Ȃ��m�[�h��������
	for (i = 0; i < VISIBLE_GRAPHIC_MAX_NUM; i++)
	{
		if (g_visibleGraphic[i].graphicHandle == 0)
			break;
	}

	if (i == VISIBLE_GRAPHIC_MAX_NUM)
	{
		std::cout << "��ʂɂ���ȏ�\���ł��܂���(id " << graphicId << ")" << std::endl;
		return -1;
	}

	// ���o�^
	// �O���t�B�b�N�n���h���o�^
	g_visibleGraphic[i].graphicHandle = handle;
	// graphicId��o�^
	g_visibleGraphic[i].graphicId = graphicId;
	// ���W�̎w��
	g_visibleGraphic[i].x = posX;
	g_visibleGraphic[i].y = posY;

	// �P�x���̓o�^
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
		
	
	// ���[�h
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
				// �P�x���グ��
				g_visibleGraphic[i].bright += GRAPHIC_FADEIN_FADEOUT_SPEED;
				// �P�x���ő�l�ɒB�����Ƃ�
				if (g_visibleGraphic[i].bright > GRAPHIC_MAX_BRIGHT)
				{
					g_visibleGraphic[i].bright = GRAPHIC_MAX_BRIGHT;
					// �t�F�[�h�C������
					g_visibleGraphic[i].mode = GRAPHIC_MODE_NONE;
 				}
			}
			else if(g_visibleGraphic[i].mode == GRAPHIC_MODE_FADEOUT)
			{
				// �P�x��������
				g_visibleGraphic[i].bright -= GRAPHIC_FADEIN_FADEOUT_SPEED;
				// �P�x��0�ȉ��ɂȂ����ꍇ
				if (g_visibleGraphic[i].bright < GRAPHIC_MIN_BRIGHT)
				{
					g_visibleGraphic[i].bright = GRAPHIC_MIN_BRIGHT;
					// �t�F�[�h�A�E�g����
					g_visibleGraphic[i].mode = GRAPHIC_MODE_NONE;
				}
			}
			// �P�x���Z�b�g
			SetDrawBright(g_visibleGraphic[i].bright, g_visibleGraphic[i].bright, g_visibleGraphic[i].bright);

			// �A���t�@�u�����h���s��
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, g_visibleGraphic[i].bright);
			// �w�肵�����W�ɉ摜�`��
			
			DrawGraph(g_visibleGraphic[i].x, g_visibleGraphic[i].y, g_visibleGraphic[i].graphicHandle, TRUE);

			//std::cout << "Index" << i << " Image Bright : " << g_visibleGraphic[i].bright << std::endl;
		}
	}

	// �P�x�����f�t�H���g�ɖ߂��Ă���
	SetDrawBright(GRAPHIC_MAX_BRIGHT, GRAPHIC_MAX_BRIGHT, GRAPHIC_MAX_BRIGHT);

	// �u�����h���[�h�����ɖ߂��Ă���
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
		// �w�肵���O���t�B�b�N����������
		if(graphicId == g_visibleGraphic[i].graphicId)
		{
			// �f�[�^�̍폜
			g_visibleGraphic[i].graphicHandle = 0;
			g_visibleGraphic[i].graphicId = 0;
			g_visibleGraphic[i].x = 0;
			g_visibleGraphic[i].y = 0;
			return 0;
		}
	}
	// �폜�ł��Ȃ������ꍇ
	return -1;
}

int AbstractScene::removeAllVisibleGraphic()
{
	for (int i = 0; i < VISIBLE_GRAPHIC_MAX_NUM; i++)
	{
		// �w�肵���O���t�B�b�N����������
		if (g_visibleGraphic[i].graphicId != 0)
		{
			// �f�[�^�̍폜
			g_visibleGraphic[i].graphicHandle = 0;
			g_visibleGraphic[i].graphicId = 0;
			g_visibleGraphic[i].x = 0;
			g_visibleGraphic[i].y = 0;
			return 0;
		}
	}
	// �폜�ł��Ȃ������ꍇ
	return -1;
}

int AbstractScene::checkGraphic()
{
	int i;
	for (i = 0; i < GRAPHIC_MAX_NUM; i++)
	{
		if (g_graphicManager[i].id != 0)		// �摜���o�^����Ă����
		{
			return 1;								// 1��Ԃ�
		}
	}
	return 0;
}

int AbstractScene::checkVisibleGraphic()
{
	int i;
	for (i = 0; i < VISIBLE_GRAPHIC_MAX_NUM; i++)
	{
		if (g_visibleGraphic[i].graphicId != 0)		// �摜���o�^����Ă����
		{
			return 1;								// 1��Ԃ�
		}
	}
	return 0;
}

