#include "Activity.h"

#include <chrono>

#include <Core/Application/Object/ObjectManager.h>
#include <Core/Application/Platform/API/Audio/AudioAPI.h>
#include <Core/Application/Platform/API/Graphics/GraphicsAPI.h>
#include <Core/Application/Platform/API/Input/InputAPI.h>

#include <Core/Application/Platform/Platform.h>

// =================================================================
// GGG Statement
// =================================================================
GG_INIT_FUNC_IMPL_1(Activity, const ActivityOption& option)
{
  this->option_ = option;
  return true;
}

// =================================================================
// Methods
// =================================================================
bool Activity::DrawEnabled(T_FLOAT delta_time)
{
  this->elapsed_time_ += delta_time;
  if (this->elapsed_time_ >= this->option_.render_cycle)
  {
    this->elapsed_time_ = fmodf(this->elapsed_time_, this->option_.render_cycle);
    return true;
  }
  return false;
}
