#pragma once

#include "stdafx.h"
#include <stack>
#include <memory>

class Looper final : public IOnSceneChangedListener
{
private:
	std::stack<std::shared_ptr<AbstractScene>> _sceneStack;		//	シーンのスタック
	Parameter parameter;
public:

	Looper();
	~Looper();
	bool loop() const;
	void onSceneChanged(const eScene scene, Parameter &parameter,const bool stackClear) override;

};

