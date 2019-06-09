#include "GameComponent.h"

// =================================================================
// GGG Statement
// =================================================================
GG_INIT_FUNC_IMPL_1(GameComponent, GameObject*, obj)
{
  this->enabled_ = true;
  this->obj_ = obj;
  return true;
}
