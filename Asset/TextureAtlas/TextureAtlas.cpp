#include "TextureAtlas.h"

// =================================================================
// GGG Statement
// =================================================================
void rcTextureAtlas::Init(const TextureAtlasData& data)
{
  this->texture_ = AssetManager::Load<rcTexture>(data.texture_unique_id_);
  this->mesh_ = AssetManager::Load<rcMesh>(data.mesh_unique_id_);
}
