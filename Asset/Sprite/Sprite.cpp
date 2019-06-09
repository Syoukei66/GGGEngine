#include "Sprite.h"

#include <Asset/TextureAtlas/TextureAtlas.h>
#include <Asset/Mesh/Mesh.h>

// =================================================================
// GGG Statement
// =================================================================
GG_ASSET_INIT(rcSprite, SpriteData)
{
  const SharedRef<rcTextureAtlas>& atlas = AssetManager::Load<rcTextureAtlas>(data.texture_atlas_unique_id_);
  this->texture_ = atlas->GetTexture();
  this->mesh_ = atlas->GetMesh();
  this->submesh_index_ = data.submesh_index_;
  return true;
}
