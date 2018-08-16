#include "MeshBuilder_Sprite.h"
#include "MeshFactory_Sprite.h"

MeshBuilder_Sprite::MeshBuilder_Sprite()
{
}

rcCustomMesh* MeshBuilder_Sprite::CreateMesh() const
{
  return MeshFactory::Sprite::Create();
}
