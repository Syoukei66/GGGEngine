#include "AssetEntityFileLeaf.h"

// =================================================================
// GGG Statement
// =================================================================
GG_CREATE_FUNC_IMPL_1(AssetEntityFileLeaf, const SharedRef<AssetEntity>&, entity)
{
  this->entity_ = entity;
  return true;
}