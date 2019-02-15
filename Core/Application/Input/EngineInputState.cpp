#include "EngineInputState.h"

// =================================================================
// Methods
// =================================================================
void EngineInputState::Prepare()
{
  for (auto& itr : this->analog_input_)
  {
    itr.second.Prepare();
  }
  for (auto& itr : this->digital_input_)
  {
    itr.second.Prepare();
  }
}

