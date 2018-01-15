#include <Windows.h>
#include <EngineSetting.h>

#include "DirectXActivity.h"

//#include <stdlib.h>
//#include <crtdbg.h> 

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
  //_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
  DirectXActivity* activity = new DirectXActivity(hInstance, hPrevInstance, lpCmdLine, nShowCmd);
  EngineSetting* setting = new EngineSetting();
  activity->Run(setting);
  WPARAM msg = activity->GetMsgWparam();
  delete setting;
  delete activity;
  return (int)0;
}
