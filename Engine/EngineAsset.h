#pragma once
#include "../Asset/Material.h"
#include "../Asset/AssetContainer.h"
#include "MeshResource.h"

namespace EngineAsset
{

namespace rcShader
{
using T_ = rcShader;
using Cont_ = const AssetContainer<T_>*;
extern Cont_ UNLIT;
extern Cont_ LAMBERT;
extern Cont_ PHONG;
extern Cont_ SPRITE;
extern Cont_ WHITE;
} // namespace Shader

namespace rcMaterial
{
extern class rcMaterial UNLIT;
extern class rcMaterial LAMBERT;
extern class rcMaterial PHONG;
extern class rcMaterial SPRITE;
extern class rcMaterial WHITE;
} // namespace rcMaterial

namespace rcCustomMesh
{
extern MeshResource QUAD;
extern MeshResource PLANE;
extern MeshResource CUBE;
} // namespace Mesh

void Load();
void Unload();

} // namespace EngineAsset