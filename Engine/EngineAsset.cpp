#include "EngineAsset.h"
#include "MeshBuilder_Cube.h"
#include "MeshBuilder_Plane.h"
#include "MeshBuilder_Sprite.h"
#include "GraphicsConstants.h"

namespace EngineAsset
{

namespace Shader
{
const ShaderAsset DEFAULT("Asset/shader/default/Default.cso");
const ShaderAsset LAMBERT("Asset/shader/default/Lambert.cso");
const ShaderAsset PHONG("Asset/shader/default/Phong.cso");
const ShaderAsset PARTICLE("Asset/shader/default/Particle.cso");
const ShaderAsset PRIMITIVE("Asset/shader/default/Primitive.cso");
const ShaderAsset SPRITE("Asset/shader/default/Sprite.cso");
const ShaderAsset WHITE("Asset/shader/default/White.cso");
} // namespace Shader

namespace Material
{
class Material DEFAULT(Shader::DEFAULT, true);
class Material LAMBERT(Shader::LAMBERT, true);
class Material PHONG(Shader::PHONG, true);
class Material PARTICLE(Shader::PARTICLE, true);
class Material PRIMITIVE(Shader::PRIMITIVE, true);
class Material SPRITE(Shader::SPRITE, true);
class Material WHITE(Shader::WHITE, true);
} // namespace Material

namespace Mesh
{
class MeshResource QUAD(new MeshBuilder_Sprite());
class MeshResource PLANE(new MeshBuilder_Plane(GraphicsConstants::V_FORMAT_PNUTC, 1.0f, 1.0f, 1, 1));
class MeshResource CUBE(new MeshBuilder_Cube(GraphicsConstants::V_FORMAT_PNUTC, 1.0f, 1.0f, 1.0f, 1, 1, 1));
} // namespace Mesh

} // namespace EngineAsset