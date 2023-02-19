// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//
// WINDOWS SKINNING TUTORIAL - by Vander Nunes - virtware.net
// This is the source-code that shows what is discussed in the tutorial.
// The code is simplified for the sake of clarity, but all the needed
// features for handling skinned windows is present. Please read
// the article for more information.
//
// skintest.cpp
// 28/02/2002 : initial release.
//
// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-


// #include "skintest.h"
// #include "resource.h"

// // include our custom skin class
//#include "skin.h"
#include <windows.h>

// app window handle
   HWND hWnd=NULL;

// app window procedure
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam);

// window creation helper
bool MakeWindow(int iWidth, int iHeight);



// ------------------------------------------------------------------------
// Build a basic region and set it to the window.
// ------------------------------------------------------------------------
void RegionMe()
{
  // --------------------------------------------------
  // create an elliptical region.
  // we use a negative starting y coordinate to make
  // the ellipse cover a bit more of the caption.
  // --------------------------------------------------
  HRGN hRegion1 = CreateEllipticRgn(20,-20,190,150);

  // --------------------------------------------------
  // create one more elliptical region in other place.
  // --------------------------------------------------
  HRGN hRegion2 = CreateEllipticRgn(140,100,300,240);

  // --------------------------------------------------
  // combine the two regions to build a new region
  // that will be the sum of the two.
  // the resulting region will be stored in region1,
  // like if we were making something like:
  // hRegion1 = hRegion1 + hRegion2.
  // --------------------------------------------------
  CombineRgn(hRegion1, hRegion1, hRegion2, RGN_OR);

  // --------------------------------------------------
  // assign the region to the window
  // --------------------------------------------------
  SetWindowRgn(hWnd, hRegion1, true);

  // --------------------------------------------------
  // delete the region objects
  // --------------------------------------------------
  DeleteObject(hRegion1);
  DeleteObject(hRegion2);

  // --------------------------------------------------
  // flag just to make sure our app knows about it.
  // --------------------------------------------------
 // bRegioned = true;
}

// ------------------------------------------------------------------------
// The application entry point
// ------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
  // -------------------------------------------------
  // instantiate a skin but do not activate yet
  // -------------------------------------------------

  //CSkin skSkin(IDR_SKINREGION, IDB_SKIN);
  //CSkin skSkin(0, 0);

 
  // -------------------------------------------------
  // create the application window.
  // -------------------------------------------------

    //if ( !MakeWindow(skSkin.Width(), skSkin.Height()) ) return -1;
      if ( !MakeWindow(320, 240) ) return -1;
 RegionMe();
//   // activate the skin
    // skSkin.Hook(hWnd);
    // skSkin.Enable(true);

//   // show our fancy window =)

    ShowWindow(hWnd, SW_SHOW);
    


  // -------------------------------------------------
  // now just keep the application going...
  // -------------------------------------------------

  MSG mMsg;

  while (1)
  {

    if(PeekMessage(&mMsg, 0, 0, 0, PM_REMOVE))
    {
      // -------------------------------------------------
      // the quit message
      // can arrive at any time from our window procedure.
      // -------------------------------------------------
      if(mMsg.message == WM_QUIT)
      { break; }

      // -------------------------------------------------
      // the common stuff, just translate&dispatch.
      // -------------------------------------------------
      TranslateMessage(&mMsg);
      DispatchMessage(&mMsg);
    }

  }


  // -------------------------------------------------
  // free allocated resources
  // -------------------------------------------------

  DestroyWindow(hWnd);


  // tchau!
  return 0;
}



// ------------------------------------------------------------------------
// A Basic, still smart window creation function.
// ------------------------------------------------------------------------
bool MakeWindow(int iWidth, int iHeight)
{
  // our window class
  WNDCLASS wndWc;

  // ---------------------------------------------------------
  // fill window class members
  // ---------------------------------------------------------
  wndWc.style = CS_OWNDC;
  wndWc.lpfnWndProc = (WNDPROC) WndProc;
  wndWc.cbClsExtra = 0;
  wndWc.cbWndExtra = 0;
  wndWc.hInstance = GetModuleHandle(NULL);
  wndWc.hIcon = NULL;
  wndWc.hCursor = LoadCursor(0, IDC_ARROW);
  wndWc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
  wndWc.lpszMenuName = NULL;
  wndWc.lpszClassName = L"w32skin";

  // register class
  if (!RegisterClass(&wndWc)) return false;
  // ---------------------------------------------------------

  // get actual screen resolution
  int iSw = (WORD)GetSystemMetrics(SM_CXSCREEN);       // width
  int iSh = (WORD)GetSystemMetrics(SM_CYSCREEN);       // height

  // make a rectangle on the center of the screen
  RECT rc = { (iSw - iWidth)/2, (iSh - iHeight)/2, iWidth, iHeight };

  // create the window.
  // note the WS_POPUP flag, no caption, no borders, no nothing.
  hWnd = CreateWindow(L"w32skin", L"w32skin",
                      WS_POPUP,
                      rc.left,rc.top, iWidth,iHeight,
                      NULL, NULL, GetModuleHandle(NULL), NULL);

  // return result
  return (hWnd?true:false);
}



// ------------------------------------------------------------------------
// Our application window procedure.
// Here we'll process the messages sent to our application window,
// but note that BEFORE getting here, the skin window procedure will
// be called and will evaluate WM_PAINT and WM_LBUTTONDOWN.
// ------------------------------------------------------------------------
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam)
{

	switch(uMessage)
   {
		case WM_KEYDOWN:
     {
       // ---------------------------------------------------------
       // pressing ESC will finish the app.
       // ---------------------------------------------------------
       switch (wParam)
       {
         case VK_ESCAPE:
           PostQuitMessage(0);
           break;
       }
       break;
     }
   }

  // ---------------------------------------------------------
  // call the default window procedure to keep things going.
  // ---------------------------------------------------------
  return DefWindowProc(hWnd,uMessage,wParam,lParam);
}


