#pragma once

#include <Native/Windows/PlatformMacro.h>
#include <Native/Windows/WindowsPlatform.h>
#include <Engine/Engine/IEngineBehavior.h>
#include <Engine/Engine/Engine.h>

namespace Windows
{
static void main(IEngineBehavior* behavior)
{
  Engine* engine = new Engine(behavior);
  Application::Run(engine, WindowsPlatform::Create());
  delete engine;
}

static void main(IEngineBehavior* behavior, HWND hwnd)
{
  Engine* engine = new Engine(behavior);
  Application::Run(engine, WindowsPlatform::Create());
  delete engine;
}
}