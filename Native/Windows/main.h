#pragma once

#include <Native/Windows/PlatformMacro.h>
#include <Native/Windows/WindowsApplicationSetting_Game.h>

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
}