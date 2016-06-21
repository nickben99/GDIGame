#include "Projectile.h"

Projectile::Projectile()
	: brush(Gdiplus::Color(255, 255, 255, 0)) 
	, mActive(false)
	, width(10)
{
}

void Projectile::Move()
{
	if (mActive)
	{
		xPos+=xVeloc; 
		yPos+=yVeloc;
	}
}

void Projectile::Collision(int screenWidth, int screenHeight)
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

void Projectile::Draw(HDC hdc, Gdiplus::Graphics& graphics)
{
	if (!mActive)
		return;

	int widthDiv2 = width/2;
	graphics.FillEllipse(&brush, xPos-widthDiv2, yPos-widthDiv2, width, width);
}