#pragma once

#include <Native/Windows/PlatformMacro.h>
#include <Native/Windows/WindowsApplicationSetting_Game.h>
#include <Native/Windows/WindowsApplicationSetting_Editor.h>

namespace Windows
{
void main(IEngineBehavior* behavior)
{
  Engine* engine = new Engine(behavior);
  WindowsApplicationSetting_Game* setting = new WindowsApplicationSetting_Game();
  Application::Run(engine, setting);
  delete setting;
  delete engine;
}

void main(IEngineBehavior* behavior, HWND hwnd)
{
  Engine* engine = new Engine(behavior);
  WindowsApplicationSetting_Editor* setting = new WindowsApplicationSetting_Editor(hwnd);
  Application::Run(engine, setting);
  delete setting;
  delete engine;
}
}