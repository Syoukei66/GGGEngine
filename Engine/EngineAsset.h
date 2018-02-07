#pragma once
#include "ShaderResource.h"
#include "Material.h"
#include "MeshResource.h"

namespace EngineAsset
{

namespace Shader
{
extern const ShaderResource DEFAULT;
extern const ShaderResource MODEL;
extern const ShaderResource PARTICLE;
extern const ShaderResource PRIMITIVE;
extern const ShaderResource SPRITE;
extern const ShaderResource WHITE;
} // namespace Shader

namespace Material
{
extern class Material DEFAULT;
extern class Material MODEL;
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