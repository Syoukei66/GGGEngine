#include "MeshBuilder_Sprite.h"
#include "MeshFactory_Sprite.h"

MeshBuilder_Sprite::MeshBuilder_Sprite()
{
}

rcMesh* MeshBuilder_Sprite::CreateMesh(bool read_only) const
{
  return MeshFactory::Sprite::Create(read_only);
}
