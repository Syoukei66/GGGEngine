#pragma once
#include "ShaderResource.h"
#include "Material.h"
#include "MeshResource.h"

namespace EngineAsset
{

namespace Shader
{
extern const ShaderAsset DEFAULT;
extern const ShaderAsset LAMBERT;
extern const ShaderAsset PHONG;
extern const ShaderAsset PARTICLE;
extern const ShaderAsset PRIMITIVE;
extern const ShaderAsset SPRITE;
extern const ShaderAsset WHITE;
} // namespace Shader

namespace Material
{
extern class Material DEFAULT;
extern class Material LAMBERT;
extern class Material PHONG;
extern class Material PARTICLE;
extern class Material PRIMITIVE;
extern class Material SPRITE;
extern class Material WHITE;
} // namespace Material

namespace Mesh
{
extern MeshResource QUAD;
extern MeshResource PLANE;
extern MeshResource CUBE;
} // namespace Mesh

} // namespace EngineAsset