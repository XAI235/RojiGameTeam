#pragma once


#define TITLE_BACKGROUND	1
#define SELECT_MASK			10

class TitleScene : public AbstractScene
{
private:
	Parameter param;
//	int Picture[2];
	int BGM;
	float bright;
public:
	TitleScene(IOnSceneChangedListener* impl, const Parameter& parameter);
	virtual ~TitleScene() = default;
	void update()	override;
	void draw() override;
};

