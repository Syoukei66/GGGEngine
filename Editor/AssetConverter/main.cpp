#include <crtdbg.h> 
#include <cstddef>

#include "EngineBehavior.h"

// =================================================================
// Platform Setting
// =================================================================

#define GG_GRAPHICS_API_DX9 1

#include <Native/Windows/main.h>

int main()
{
  _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
  EngineBehavior* behavior = new EngineBehavior();
  Windows::main(behavior);
  delete behavior;
  return (int)0;
}
