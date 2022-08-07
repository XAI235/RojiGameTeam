#include "Looper.h"
#include "DxLib.h"
#include "TitleScene.h"
#include "Parameter.h"



Looper::Looper()
{
	Parameter parameter;
	_sceneStack.push(std::make_shared<TitleScene>(this, parameter));
}

Looper::~Looper()
{
}

/*!
*	@brief	_�X�^�b�N�̃g�b�v�V�[���̏���������
*/
bool Looper::loop() const
{
	_sceneStack.top()->update();		//	�X�^�b�N�̃g�b�v�V�[���̍X�V
	_sceneStack.top()->draw();			//	�X�^�b�N�̃g�b�v�V�[����`��
	return true;
}

/*
*	@brief	�V�[���ύX(�e�V�[������R�[���o�b�N�����)
*	@param	scene	�ύX����V�[����enum
*	@param	stackClear	���݂̃V�[���̃X�^�b�N���N���A���邩
*/
void Looper::onSceneChanged(const eScene scene, Parameter& parameter,const bool stackClear)
{
}
