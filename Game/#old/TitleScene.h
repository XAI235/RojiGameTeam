#pragma once

#include "AbstractScene.h"

class TitleScene : public AbstractScene
{
private:
	int GrMenu;
	int SdMenu;
public:
	TitleScene(IOnSceneChangedListener* impl, const Parameter& parameter);
	virtual ~TitleScene() = default;
	void update()	override;
	void draw() override;
};

