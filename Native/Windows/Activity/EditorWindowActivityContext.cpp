#include "EditorWindowActivityContext.h"

// =================================================================
// GGG Statement
// =================================================================
GG_INIT_FUNC_IMPL_1(EditorWindowActivityContext, HWND hwnd)
{
  this->window_handle_ = hwnd;
  return true;
}

// =================================================================
// Methods from ActivityContext
// =================================================================
void EditorWindowActivityContext::OnStart(const ActivityOption& option)
{
}

void EditorWindowActivityContext::OnEnd()
{
}
