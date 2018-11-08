#include "EditorWindowActivity.h"

// =================================================================
// GGG Statement
// =================================================================
GG_INIT_FUNC_IMPL_2(EditorWindowActivity, const ActivityOption& option, HWND hwnd)
{
  return WindowsActivity::Init(option, hwnd);
}

