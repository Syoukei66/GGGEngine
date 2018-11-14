#include "AssetEntityFileLeaf.h"

// =================================================================
// GGG Statement
// =================================================================
GG_INIT_FUNC_IMPL_1(AssetEntityFileLeaf, const SharedRef<AssetEntity>& entity)
{
  this->entity_ = entity;
  return true;
}