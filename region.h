// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//
// WINDOWS SKINNING TUTORIAL - by Vander Nunes - virtware.net
// This is the source-code that shows what is discussed in the tutorial.
// The code is simplified for the sake of clarity, but all the needed
// features for handling skinned windows is present. Please read
// the article for more information.
//
// region.h
// 28/02/2002 : initial release.
//
// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-


#ifndef _REGION_H_

  #define _REGION_H_
  #include <windows.h>

  // app window handle
  HWND hWnd=NULL;

  // region toggle
  bool bRegioned;

  // app window procedure
  LRESULT CALLBACK WndProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam);

  // window creation helper
  bool MakeWindow(int iWidth, int iHeight);

#endif
