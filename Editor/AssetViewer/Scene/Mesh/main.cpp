#define NOMINMAX

#include <windows.h>
#include <stdlib.h>
#include <crtdbg.h> 
#include <cstddef>
#include <new>

#include "EngineBehavior.h"

// =================================================================
// Platform Setting
// =================================================================

#define GG_GRAPHICS_API_DX9 1

#include <Native/Windows/main.h>

//void* operator new(std::size_t n)
//{
//  void* p = std::malloc(n);
//  return p ? p : throw std::bad_alloc();
//}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
  _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
  EngineBehavior* behavior = new EngineBehavior();
  Windows::main(behavior);
  delete behavior;
  return (int)0;
}
