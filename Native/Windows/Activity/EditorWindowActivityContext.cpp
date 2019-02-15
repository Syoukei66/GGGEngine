#include "EditorWindowActivityContext.h"

// =================================================================
// Constructor / Destructor
// =================================================================
EditorWindowActivityContext::EditorWindowActivityContext(HWND hwnd)
{
  this->window_handle_ = hwnd;
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
