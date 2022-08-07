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
*	@brief	_スタックのトップシーンの処理をする
*/
bool Looper::loop() const
{
	_sceneStack.top()->update();		//	スタックのトップシーンの更新
	_sceneStack.top()->draw();			//	スタックのトップシーンを描画
	return true;
}

/*
*	@brief	シーン変更(各シーンからコールバックされる)
*	@param	scene	変更するシーンのenum
*	@param	stackClear	現在のシーンのスタックをクリアするか
*/
void Looper::onSceneChanged(const eScene scene, Parameter& parameter,const bool stackClear)
{
}
