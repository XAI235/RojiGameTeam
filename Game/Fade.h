#pragma once
/*
class Fade
{
	float bright;
public:
	Fade();
	bool Fadeout(float fade_speed, int r = 255, int g = 255, int b = 255);
	bool Fadein(float fade_speed, int r = 255, int g = 255, int b = 255);
};
*/


class Fade
{
public :
	virtual ~Fade();

	/*virtual bool Fadeout(float& bright, float fade_speed, int r = 255, int g = 255, int b = 255);
	virtual bool Fadein(float& bright, float fade_speed, int r = 255, int g = 255, int b = 255); //*/
	virtual bool Fadeout(int const& PictHandle, float& bright, float fade_speed);
	virtual bool Fadein(int const& PictHandle, float& bright, float fade_speed);
};

