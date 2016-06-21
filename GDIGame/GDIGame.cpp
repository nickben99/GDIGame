//#include <stdafx.h>
#include <windows.h>
#include <objidl.h>
#include <gdiplus.h>
#include <ctime>
#include <iostream>
#include "TargetBox.h"
#include "Turret.h"
#include "Projectile.h"

using namespace Gdiplus;
#pragma comment (lib,"Gdiplus.lib")

TargetBox* one;
TargetBox* two;
TargetBox* three;

Turret* turret;
Projectile* projectiles[3];

VOID OnPaint(HDC hdc, Gdiplus::Graphics& graphics)
{
	if ( !(one && two && three && turret) )
	{
		return;
	}
	
	one->Move();
	two->Move();
	three->Move();
	turret->Move();
	projectiles[0]->Move();
	projectiles[1]->Move();
	projectiles[2]->Move();

	one->Collision(640, 480);
	two->Collision(640, 480);
	three->Collision(640, 480);
	projectiles[0]->Collision(640, 480);
	projectiles[1]->Collision(640, 480);
	projectiles[2]->Collision(640, 480);



	one->Draw(hdc, graphics);
	two->Draw(hdc, graphics);
	three->Draw(hdc, graphics);
	turret->Draw(hdc, graphics);
	projectiles[0]->Draw(hdc, graphics);
	projectiles[1]->Draw(hdc, graphics);
	projectiles[2]->Draw(hdc, graphics);
}

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, PSTR, INT iCmdShow)
{
   HWND                hWnd;
   MSG                 msg;
   WNDCLASS            wndClass;
   GdiplusStartupInput gdiplusStartupInput;
   ULONG_PTR           gdiplusToken;
   
   // Initialize GDI+.
   GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
   
   wndClass.style          = CS_HREDRAW | CS_VREDRAW;
   wndClass.lpfnWndProc    = WndProc;
   wndClass.cbClsExtra     = 0;
   wndClass.cbWndExtra     = 0;
   wndClass.hInstance      = hInstance;
   wndClass.hIcon          = LoadIcon(NULL, IDI_APPLICATION);
   wndClass.hCursor        = LoadCursor(NULL, IDC_ARROW);
   wndClass.hbrBackground  = (HBRUSH)GetStockObject(BLACK_BRUSH);
   wndClass.lpszMenuName   = NULL;
   wndClass.lpszClassName  = TEXT("GettingStarted");
   
   RegisterClass(&wndClass);
   
   hWnd = CreateWindow(
      TEXT("GettingStarted"),   // window class name
      TEXT("Getting Started"),  // window caption
      WS_OVERLAPPEDWINDOW,      // window style
      0,            // initial x position
      0,            // initial y position
      640,            // initial x size
      480,            // initial y size
      NULL,                     // parent window handle
      NULL,                     // window menu handle
      hInstance,                // program instance handle
      NULL);                    // creation parameters
	  
   ShowWindow(hWnd, iCmdShow);
   UpdateWindow(hWnd);

   one = new TargetBox();
   two = new TargetBox();
   three = new TargetBox();

   projectiles[0] = new Projectile();
   projectiles[1] = new Projectile();
   projectiles[2] = new Projectile();

   turret = new Turret(projectiles, 3);

   one->SetPosition(100, 100);
   one->SetWidth(80);
   two->SetPosition(100, 200);
   two->SetWidth(80);
   three->SetPosition(100, 300);
   three->SetWidth(80);

   turret->SetPosition(320, 480);
   
	bool done = false;
	while(!done) // loop that runs while done = FALSE
	{	
		if (PeekMessage(&msg,NULL,0,0,PM_REMOVE)) // is there a message waiting?
		{
			if (msg.message==WM_QUIT){ // is this quit message?
				done=TRUE;}	// if so done = TRUE
			else // not a quit message (so send message to message handler WndProc)
			{
				TranslateMessage(&msg);	// translate the message
				DispatchMessage(&msg); // dispatch the message
			}
		}
		else // their are no messages
		{
			InvalidateRect(hWnd, NULL, TRUE);//force window to repaint
			UpdateWindow(hWnd);
		} // end if peekMessage
	} // end while not done 
   
	delete one;
	delete two;
	delete three;

	delete turret;

   GdiplusShutdown(gdiplusToken);
   return msg.wParam;
}  // WinMain

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC          hdc;
	PAINTSTRUCT  ps;

	switch(message)
	{
	case WM_PAINT:
	{
		hdc = BeginPaint(hWnd, &ps);

		// -------------- for double buffering purposes
		RECT rcClient;
		::GetClientRect(hWnd, &rcClient);
		int left = rcClient.left;
		int top = rcClient.top;
		int width = rcClient.right - rcClient.left;
		int height = rcClient.bottom - rcClient.top;

		HDC hdcMem = ::CreateCompatibleDC(hdc);
		const int nMemDC = ::SaveDC(hdcMem);

		HBITMAP hBitmap = ::CreateCompatibleBitmap(hdc, width, height);
		::SelectObject(hdcMem, hBitmap);

		Graphics graphics(hdcMem);
		SolidBrush back(Color(0,0,0));
		graphics.FillRectangle(&back, left, top, width, height);
		// -------------------------------------------

		OnPaint(hdcMem, graphics);
      
		//---------------------------- for double buffering
		RECT rcClip;
	    ::GetClipBox(hdc, &rcClip);
	    left = rcClip.left;
	    top = rcClip.top;
	    width = rcClip.right - rcClip.left;
	    height = rcClip.bottom - rcClip.top;
	    ::BitBlt(hdc, left, top, width, height, hdcMem, left, top, SRCCOPY);

	    ::RestoreDC(hdcMem, nMemDC);
	    ::DeleteObject(hBitmap);
		//--------------------------------------------
		
		EndPaint(hWnd, &ps);
		return 0;
	}	
	case WM_ERASEBKGND:
			return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_KEYDOWN: // a key is being held down
		switch (wParam)
		{
			case VK_ESCAPE: // escape key
				PostQuitMessage(WM_QUIT); // post quit message 
				break;
			case VK_RETURN:
				if (turret)
				{
					turret->Fire();
				}
				break;
			default: break;
		}							
		return 0;
   default:
      return DefWindowProc(hWnd, message, wParam, lParam);
   }
} // WndProc