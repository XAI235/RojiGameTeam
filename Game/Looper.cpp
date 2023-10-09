
#include "stdafx.h"
#include "Looper.h"
#include "eScene.h"
#include "Parameter.h"




Looper::Looper()
{
	parameter.initialize();
	_sceneStack.push(std::make_shared<IntroductionScene>(this, parameter));
	
}

Looper::~Looper()
{
}

/*!
*	@brief	_�X�^�b�N�̃g�b�v�V�[���̏���������
*/
bool Looper::loop() const
{
	Keyboard::getIns()->update();
	Mouse::getIns()->update();
	_sceneStack.top()->update();		//	�X�^�b�N�̃g�b�v�V�[���̍X�V
	_sceneStack.top()->draw();			//	�X�^�b�N�̃g�b�v�V�[����`��

	std::cout << "Stack size : " << _sceneStack.size() << std::endl;
	return true;
}

/*
*	@brief	�V�[���ύX(�e�V�[������R�[���o�b�N�����)
*	@param	scene	�ύX����V�[����enum
*	@param	stackClear	���݂̃V�[���̃X�^�b�N���N���A���邩
*/
void Looper::onSceneChanged(const eScene scene, Parameter& parameter,const bool stackClear)
{
	Parameter tmpParam = parameter;
	if (stackClear)		// �X�^�b�N�N���A�Ȃ��
	{
		while (!_sceneStack.empty())		//	��ɂȂ�܂Ń|�b�v����
		{
			_sceneStack.pop();
		}

	}

	switch (scene)
	{
	case eScene::Intro:
		_sceneStack.push(std::make_shared<IntroductionScene>(this, tmpParam));
		break;
	case eScene::Title:
		if (!_sceneStack.empty())
		{
			_sceneStack.pop();
		}
		else
		{
			_sceneStack.push(std::make_shared<TitleScene>(this, tmpParam));
		}
		break;
	case eScene::Game:
		_sceneStack.push(std::make_shared<GameScene>(this, tmpParam));
		break;
	case eScene::Config:
	default:
		break;
	}
}
