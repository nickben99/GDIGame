#include "ClockFace.h"
#include <ctime>
#include <math.h>

ClockFace::ClockFace()
	: brush(Gdiplus::Color(255, 0, 255, 0))
	, redpen(Gdiplus::Color(255, 255, 0, 0))
	, bluepen(Gdiplus::Color(255, 0, 0, 255))
	, greenpen(Gdiplus::Color(255, 0, 255, 0))
{
}

void ClockFace::SetPosition(int x, int y)
{
	xPos = x;
	yPos = y;
}

void ClockFace::SetWidth(int newWidth)
{
	width = newWidth;
}

void ClockFace::Draw(HDC hdc, Gdiplus::Graphics& graphics)
{
	int widthDiv2 = width/2;
	graphics.FillEllipse(&brush, xPos-widthDiv2, yPos-widthDiv2, width, width);
	graphics.DrawEllipse(&redpen, xPos-widthDiv2, yPos-widthDiv2, width, width);

	time_t t = time(0);   // get time now
    struct tm now;
	localtime_s( &now, & t );

	float secPercent = (now.tm_sec / 60.0f);
	float minPercent = ((now.tm_min+secPercent) / 60.0f);

	const float kPI = 3.14159f;
	float hourLen = widthDiv2 * 0.7f;
	float angle = ( ((now.tm_hour % 12)+minPercent) / 12.0f) * (2*kPI);
	int y = (int)( cos(angle) * -hourLen );
	int x = (int)( sin(angle) * hourLen );
	graphics.DrawLine(&redpen, xPos, yPos, xPos+x, yPos+y);

	float len = widthDiv2 * 0.9f;
	angle = minPercent * (2*kPI);
	y = (int)( cos(angle) * -len );
	x = (int)( sin(angle) * len );
	graphics.DrawLine(&bluepen, xPos, yPos, xPos+x, yPos+y);

	angle = secPercent * (2*kPI);
	y = (int)( cos(angle) * -len );
	x = (int)( sin(angle) * len );
	graphics.DrawLine(&bluepen, xPos, yPos, xPos+x, yPos+y);
}