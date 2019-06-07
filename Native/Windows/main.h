#pragma once

#include <Native/Windows/PlatformMacro.h>
#include <Native/Windows/WindowsPlatform.h>
#include <Engine/Engine/IEngineBehavior.h>
#include <Engine/Engine/Engine.h>

namespace Windows
{
static void main(IEngineBehavior* behavior)
{
  Application::Run(&Engine(behavior), WindowsPlatform::Create());
}

static void main(IEngineBehavior* behavior, HWND hwnd)
{
  Application::Run(&Engine(behavior), WindowsPlatform::Create());
}
}