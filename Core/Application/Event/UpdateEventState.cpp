#include "UpdateEventState.h"

// =================================================================
// Constructor / Destructor
// =================================================================
UpdateEventState::UpdateEventState()
  : delta_time_()
{
  this->time_ = std::chrono::system_clock::now();
}

// =================================================================
// Methods
// =================================================================
void UpdateEventState::Update()
{
  auto time = std::chrono::system_clock::now();
  this->delta_time_ = std::chrono::duration_cast<std::chrono::microseconds>(time - this->time_).count() * 0.001f * 0.001f;
  this->time_ = time;
}
