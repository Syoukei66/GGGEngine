#pragma once

#include <Windows.h>

//#ifdef GG_EXPORTS
//#define GG_API __declspec(dllexport)
//#else
//#define GG_API __declspec(dllimport)
//#endif

namespace GGGEditorLibrary
{

void Run(HWND main_activity_hwnd);

}