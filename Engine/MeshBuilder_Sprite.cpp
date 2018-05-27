#include "MeshBuilder_Sprite.h"
#include "MeshFactory_Sprite.h"

MeshBuilder_Sprite::MeshBuilder_Sprite()
{
}

Mesh* MeshBuilder_Sprite::Create() const
{
  return MeshFactory::Sprite::Create();
}
