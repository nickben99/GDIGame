#ifndef _ClockFace_h_
#define _ClockFace_h_

#include <windows.h>
#include <objidl.h>
#include <gdiplus.h>

namespace Gdiplus
{
	class Graphics;
};

class ClockFace
{
public:
	ClockFace();
	void SetPosition(int x, int y);
	void SetWidth(int newWidth);
	void Draw(HDC hdc, Gdiplus::Graphics& graphics);

private:
	int xPos;
	int yPos;
	int width;

	Gdiplus::SolidBrush brush;
	Gdiplus::Pen redpen;
	Gdiplus::Pen bluepen;
	Gdiplus::Pen greenpen;
};

#endif
