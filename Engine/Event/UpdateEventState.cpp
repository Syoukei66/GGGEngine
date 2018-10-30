#include "UpdateEventState.h"

// =================================================================
// UpdateState
// =================================================================
void UpdateEventState::OnSceneChanged()
{
  Self().frame_elapsed_since_scene_create_ = 0;
  Self().milliseconds_elapsed_since_scene_create_ = 0;
}

void UpdateEventState::Update(T_UINT32 milliseconds_elapsed)
{
  Self().frame_elapsed_since_scene_create_++;
  Self().milliseconds_elapsed_since_scene_create_ += milliseconds_elapsed;
  Self().delta_time_ = milliseconds_elapsed;
}