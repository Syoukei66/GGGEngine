#include "GameComponent.h"

// =================================================================
// Constructor / Destructor
// =================================================================
GameComponent::GameComponent()
  : is_enabled_(false)
{
}

// =================================================================
// Setter / Getter
// =================================================================
void GameComponent::SetEnabled(bool enabled)
{
  if (this->is_enabled_ == enabled)
  {
    return;
  }
  this->is_enabled_ = enabled;
}
