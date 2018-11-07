#include "TextureAtlas.h"

// =================================================================
// GGG Statement
// =================================================================
GG_INIT_FUNC_IMPL_1(rcTextureAtlas, const TextureAtlasData& data)
{
  this->texture_ = AssetManager::Load<rcTexture>(data.texture_unique_id_);
  this->mesh_ = AssetManager::Load<rcMesh>(data.mesh_unique_id_);
  return true;
}
