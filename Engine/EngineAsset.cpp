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
class Material DEFAULT(Shader::DEFAULT);
class Material MODEL(Shader::MODEL);
class Material PARTICLE(Shader::PARTICLE);
class Material PRIMITIVE(Shader::PRIMITIVE);
class Material SPRITE(Shader::SPRITE);
class Material WHITE(Shader::SPRITE);
} // namespace Material

} // namespace EngineAsset