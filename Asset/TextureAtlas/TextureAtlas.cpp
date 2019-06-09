#include "TextureAtlas.h"

// =================================================================
// GGG Statement
// =================================================================
GG_ASSET_INIT(rcTextureAtlas, TextureAtlasData)
{
  this->texture_ = AssetManager::Load<rcTexture>(data.texture_unique_id_);
  this->mesh_ = AssetManager::Load<rcMesh>(data.mesh_unique_id_);
  return true;
}
