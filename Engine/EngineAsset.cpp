#include "EngineAsset.h"
#include "MeshData_Cube.h"
#include "MeshData_Plane.h"
#include "MeshData_Sprite.h"

namespace EngineAsset
{

namespace Shader
{
const ShaderResource DEFAULT("Asset/shader/default/Default.cso");
const ShaderResource LAMBERT("Asset/shader/default/Lambert.cso");
const ShaderResource PHONG("Asset/shader/default/Phong.cso");
const ShaderResource PARTICLE("Asset/shader/default/Particle.cso");
const ShaderResource PRIMITIVE("Asset/shader/default/Primitive.cso");
const ShaderResource SPRITE("Asset/shader/default/Sprite.cso");
const ShaderResource WHITE("Asset/shader/default/White.cso");
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
class MeshResource QUAD(MeshData_Sprite::GetInstance());
class MeshResource PLANE(MeshData_Plane::GetInstance());
class MeshResource CUBE(MeshData_Cube::GetInstance());
} // namespace Mesh

} // namespace EngineAsset