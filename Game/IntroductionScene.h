#pragma once


class IntroductionScene : public AbstractScene
{
	Parameter param;
	int NowDrawLogos;
	int counter;
	bool NextToLogos;
	int* pX;
	int* pY;
public:
	IntroductionScene(IOnSceneChangedListener* impl, const Parameter& parameter);
	virtual ~IntroductionScene() = default;

	void update();
	void draw();
};

