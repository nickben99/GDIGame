#ifndef _Projectile_h_
#define _Projectile_h_

#include <windows.h>
#include <objidl.h>
#include <gdiplus.h>

namespace Gdiplus
{
	class Graphics;
};

class Projectile
{
public:
	Projectile();

	void Move();
	void Collision(int screenWidth, int screenHeight);
	void Draw(HDC hdc, Gdiplus::Graphics& graphics);

	inline void SetActive(bool active)
	{
		mActive = active;
	}

	inline void SetVeloc(int x, int y)
	{
		xVeloc = x;
		yVeloc = y;
	}

	inline void SetPosition(int x, int y)
	{
		xPos = x;
		yPos = y;
	}

private:
	Gdiplus::SolidBrush brush;

	bool mActive;
	int xPos, yPos, xVeloc, yVeloc;
	int width;
};

#endif
