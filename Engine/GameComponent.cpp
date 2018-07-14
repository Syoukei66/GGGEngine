#include "GameComponent.h"

// =================================================================
// Constructor / Destructor
// =================================================================
void GameComponent::Release()
{
  delete this;
}

GameComponent::GameComponent(GameObject* entity)
  : entity_(entity)
  , enabled_(true)
{
}

GameComponent::~GameComponent()
{
}
