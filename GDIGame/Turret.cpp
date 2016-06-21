#include "Turret.h"
#include "Projectile.h"

Turret::Turret(Projectile** proj, int numProj)
	: xPos(0)
	, yPos(0)
	, mOrientation(0)
	, mpProjectiles(proj)
	, maxProjectiles(numProj)
	, redpen(Gdiplus::Color(255, 255, 0, 0))
{
}

void Turret::Move()
{
}

void Turret::Fire()
{
	mpProjectiles[0]->SetActive(true);
	mpProjectiles[0]->SetVeloc(0, -1);
	mpProjectiles[0]->SetPosition(xPos, yPos);
}

void Turret::Draw(HDC hdc, Gdiplus::Graphics& graphics)
{
	graphics.DrawLine(&redpen, xPos, yPos, xPos, yPos-100);
}

void Turret::SetPosition(int x, int y)
{
	xPos = x;
	yPos = y;
}