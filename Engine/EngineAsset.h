#pragma once
#include "../Asset/Material.h"
#include "../Asset/AssetContainer.h"
#include "MeshResource.h"

namespace EngineAsset
{

namespace Shader
{
using T_ = INativeShader;
using Cont_ = const AssetContainer<T_>*;
extern Cont_ UNLIT;
extern Cont_ LAMBERT;
extern Cont_ PHONG;
extern Cont_ SPRITE;
extern Cont_ WHITE;
} // namespace Shader

namespace Material
{
extern class Material UNLIT;
extern class Material LAMBERT;
extern class Material PHONG;
extern class Material SPRITE;
extern class Material WHITE;
} // namespace Material

namespace Mesh
{
extern MeshResource QUAD;
extern MeshResource PLANE;
extern MeshResource CUBE;
} // namespace Mesh

void Load();
void Unload();

} // namespace EngineAsset