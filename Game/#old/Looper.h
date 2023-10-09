#pragma once

#include <stack>
#include <memory>
#include "AbstractScene.h"
#include "IOnChangeListener.h"

class Looper final : public IOnSceneChangedListener
{
private:
	
	std::stack<std::shared_ptr<AbstractScene>> _sceneStack;		//	シーンのスタック
public:

	Looper();
	~Looper();
	bool loop() const;
	void onSceneChanged(const eScene scene, Parameter &parameter,const bool stackClear) override;

};

