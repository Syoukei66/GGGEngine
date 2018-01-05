#include "GameComponent.h"

// =================================================================
// Constructor / Destructor
// =================================================================
GameComponent::GameComponent()
  : enabled_(false)
{
}

// =================================================================
// Setter / Getter
// =================================================================
void GameComponent::SetEnabled(bool enabled)
{
  if (this->enabled_ == enabled)
  {
    return;
  }
  this->enabled_ = enabled;
}
