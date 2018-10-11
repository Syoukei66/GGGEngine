#include "MeshBuilder_Sprite.h"
#include <Core/MeshFactory_Sprite.h>

MeshBuilder_Sprite::MeshBuilder_Sprite()
{
}

MeshData* MeshBuilder_Sprite::CreateMesh() const
{
  return MeshFactory::Sprite::Create();
}
