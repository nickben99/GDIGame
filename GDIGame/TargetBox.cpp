#include "TargetBox.h"
#include <objidl.h>
#include <gdiplus.h>

TargetBox::TargetBox()
	: xVeloc(1)
	, yVeloc(1)
{
	hOrange = CreateSolidBrush(RGB(255,180,0));
}

void TargetBox::SetPosition(int x, int y)
{
	xPos = x;
	yPos = y;
	face.SetPosition(x, y);
}

void TargetBox::SetWidth(int newWidth)
{
	width = newWidth;
	face.SetWidth(width);
	face.SetPosition(xPos, yPos);
}

void TargetBox::Move()
{
	SetPosition(xPos+xVeloc, yPos+yVeloc);
}

void TargetBox::Collision(int screenWidth, int screenHeight)
{
	int widthDiv2 = (width/2);
	if (xPos+widthDiv2 > screenWidth)
	{
		xVeloc *= -1;
		xPos = screenWidth-widthDiv2;
	}
	else if (xPos-widthDiv2 < 0)
	{
		xVeloc *= -1;
		xPos = widthDiv2;
	}

	if (yPos+widthDiv2 > screenHeight)
	{
		yVeloc *= -1;
		yPos = screenHeight-widthDiv2;
	}
	else if (yPos-widthDiv2 < 0)
	{
		yVeloc *= -1;
		yPos = widthDiv2;
	}
}

void TargetBox::Draw(HDC hdc, Gdiplus::Graphics& graphics)
{
	RECT secondbackground;

	int widthDiv2 = (width/2);
	SetRect(&secondbackground, xPos-widthDiv2, yPos-widthDiv2, xPos+widthDiv2, yPos+widthDiv2);
    FillRect(hdc, &secondbackground, hOrange);

	face.Draw(hdc, graphics);
}