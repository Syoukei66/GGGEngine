#include "Material.h"

#include <Asset/Shader/Shader.h>

// =================================================================
// GGG Statement
// =================================================================
void rcMaterial::Init(const MaterialData& data)
{
  this->Init(
    data.shader_unique_id_ != 0 ?
    AssetManager::Load<rcShader>(data.shader_unique_id_) :
    AssetManager::Load<rcShader>(DefaultUniqueID::SHADER_NO_SHADING)
  );

  this->texture_ = data.main_tex_unique_id_ != 0 ?
    AssetManager::Load<rcTexture>(data.main_tex_unique_id_) :
    nullptr;
  this->tiling_ = data.tiling_;
  this->tiling_offset_ = data.tiling_offset_;
  this->color_ = data.color_;
  this->billbording_ = data.billbording_;
  
  for (const auto& pair : data.bool_properties_)
  {
    this->BoolProperty(pair.first) = pair.second;
  }
  for (const auto& pair : data.int_properties_)
  {
    this->IntProperty(pair.first) = pair.second;
  }
  for (const auto& pair : data.float_properties_)
  {
    this->FloatProperty(pair.first) = pair.second;
  }
  for (const auto& pair : data.vec2_properties_)
  {
    this->Vec2fProperty(pair.first) = pair.second;
  }
  for (const auto& pair : data.vec3_properties_)
  {
    this->Vec3fProperty(pair.first) = pair.second;
  }
  for (const auto& pair : data.vec4_properties_)
  {
    this->Vec4fProperty(pair.first) = pair.second;
  }
  for (const auto& pair : data.color_properties_)
  {
    this->ColorProperty(pair.first) = pair.second;
  }
  for (const auto& pair : data.matrix_properties_)
  {
    this->MatrixProperty(pair.first) = pair.second;
  }
  for (const auto& pair : data.texture_properties_)
  {
    this->TextureProperty(pair.first) = AssetManager::Load<rcTexture>(pair.second);
  }
}

void rcMaterial::Init(const SharedRef<rcShader>& shader)
{
  this->shader_ = shader;
  this->technique_ = "Default";
  this->queue_ = Graphics::RenderQueue::RQ_GEOMETRY;
}

// =================================================================
// Constructor / Destructor
// =================================================================
rcMaterial::~rcMaterial()
{
  for (auto pair : this->properties_)
  {
    delete pair.second;
  }
}

// =================================================================
// Methods
// =================================================================
UniqueRef<rcMaterial> rcMaterial::Clone() const
{
  UniqueRef<rcMaterial> ret = this->InitialClone();
 
  ret->queue_ = this->queue_;
  ret->texture_ = this->texture_;
  for (auto pair : this->properties_)
  {
    ret->properties_[pair.first] = pair.second->Clone();
  }

  return ret;
}

UniqueRef<rcMaterial> rcMaterial::InitialClone() const
{
  GG_ASSERT(this->shader_, "シェーダーが未定義です");
  return rcMaterial::Create(this->shader_);
}

void rcMaterial::SetProperties(const SharedRef<rcShader>& shader) const
{
  shader->SetTechnique(this->technique_);
  shader->SetTexture("_MainTex", this->texture_);
  shader->SetColor("_Diffuse", this->color_);
  for (auto pair : this->properties_)
  {
    pair.second->Apply(shader, pair.first);
  }
}

// =================================================================
// Setter / Getter
// =================================================================
void rcMaterial::SetShader(const SharedRef<rcShader>& shader)
{
  this->shader_ = shader;
}

void rcMaterial::SetMainTexture(const SharedRef<const rcTexture>& texture)
{
  this->texture_ = texture;
}
