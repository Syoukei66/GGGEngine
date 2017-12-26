#include <Windows.h>
#include <EngineSetting.h>

#include "DirectXActivity.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
  DirectXActivity* activity = new DirectXActivity(hInstance, hPrevInstance, lpCmdLine, nShowCmd);
  EngineSetting* setting = new EngineSetting();
  activity->Run(setting);
  WPARAM msg = activity->GetMsgWparam();
  delete setting;
  delete activity;
  return (int)msg;
}
