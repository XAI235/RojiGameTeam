#pragma once

#include "IOnChangeListener.h"

class IOnSceneChangedListener;

class AbstractScene
{
protected:
	IOnSceneChangedListener* _impSceneChanged;
public:
	AbstractScene(IOnSceneChangedListener* impl, const Parameter& parameter);
	virtual ~AbstractScene() = default;
	virtual void update() = 0;
	virtual void draw() = 0;
};

