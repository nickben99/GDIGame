#ifndef _Turret_h_
#define _Turret_h_

#include <windows.h>
#include <objidl.h>
#include <gdiplus.h>

namespace Gdiplus
{
	class Graphics;
};

class Projectile;

class Turret
{
public:
	Turret(Projectile** proj, int numProj);

	void Move();
	void Draw(HDC hdc, Gdiplus::Graphics& graphics);

	void SetPosition(int x, int y);

	void Fire();

private:
	int xPos;
	int yPos;
	float mOrientation;

	Projectile** mpProjectiles;
	int maxProjectiles;

	Gdiplus::Pen redpen;
};

#endif
