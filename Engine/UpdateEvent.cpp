#include "UpdateEvent.h"
#include <stdlib.h>

// =================================================================
// UpdateState
// =================================================================
UpdateEventState::UpdateEventState()
  : frame_elapsed_since_scene_create_(0)
  , milliseconds_elapsed_since_scene_create_(0)
  , delta_time_(0)
{}

void UpdateEventState::OnSceneChanged()
{
  this->frame_elapsed_since_scene_create_ = 0;
  this->milliseconds_elapsed_since_scene_create_ = 0;
}

void UpdateEventState::Update(T_UINT32 milliseconds_elapsed)
{
  this->frame_elapsed_since_scene_create_++;
  this->milliseconds_elapsed_since_scene_create_ += milliseconds_elapsed;
  this->delta_time_ = milliseconds_elapsed;
}
