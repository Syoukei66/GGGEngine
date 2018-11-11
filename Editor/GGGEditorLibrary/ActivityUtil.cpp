#include "ActivityUtil.h"

#include "EngineBehavior.h"

#define GG_GRAPHICS_API_DX9 1

void GGGEditorLibrary::Run(HWND main_activity_hwnd)
{
  _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
  EngineBehavior* behavior = new EngineBehavior();
  Windows::main(behavior);
  delete behavior;
}
