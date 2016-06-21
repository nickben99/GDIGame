#ifndef _TargetBox_h_
#define _TargetBox_h_

#include <windows.h>
#include "ClockFace.h"

namespace Gdiplus
{
	class Graphics;
};

class TargetBox
{
public:
	TargetBox();
	void SetPosition(int x, int y);
	void SetWidth(int newWidth);

	void Move();
	void Collision(int screenWidth, int screenHeight);
	void Draw(HDC hdc, Gdiplus::Graphics& graphics);

private:
	ClockFace face;
	int xPos;
	int yPos;
	int width;
	int xVeloc;
	int yVeloc;
	HBRUSH hOrange;
};

#endif
