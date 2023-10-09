
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
*	@brief	_スタックのトップシーンの処理をする
*/
bool Looper::loop() const
{
	Keyboard::getIns()->update();
	Mouse::getIns()->update();
	_sceneStack.top()->update();		//	スタックのトップシーンの更新
	_sceneStack.top()->draw();			//	スタックのトップシーンを描画

	std::cout << "Stack size : " << _sceneStack.size() << std::endl;
	return true;
}

/*
*	@brief	シーン変更(各シーンからコールバックされる)
*	@param	scene	変更するシーンのenum
*	@param	stackClear	現在のシーンのスタックをクリアするか
*/
void Looper::onSceneChanged(const eScene scene, Parameter& parameter,const bool stackClear)
{
	Parameter tmpParam = parameter;
	if (stackClear)		// スタッククリアならば
	{
		while (!_sceneStack.empty())		//	空になるまでポップする
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
