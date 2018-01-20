#include "EngineAsset.h"

namespace EngineAsset
{

namespace Shader
{
const ShaderResource DEFAULT("Asset/shader/default/Default.cso");
const ShaderResource MODEL("Asset/shader/default/Model.cso");
const ShaderResource PARTICLE("Asset/shader/default/Particle.cso");
const ShaderResource PRIMITIVE("Asset/shader/default/Primitive.cso");
const ShaderResource SPRITE("Asset/shader/default/Sprite.cso");
const ShaderResource WHITE("Asset/shader/default/White.cso");
} // namespace Shader

namespace Material
{
class Material DEFAULT(Shader::DEFAULT, true);
class Material MODEL(Shader::MODEL, true);
class Material PARTICLE(Shader::PARTICLE, true);
class Material PRIMITIVE(Shader::PRIMITIVE, true);
class Material SPRITE(Shader::SPRITE, true);
class Material WHITE(Shader::SPRITE, true);
} // namespace Material

} // namespace EngineAsset