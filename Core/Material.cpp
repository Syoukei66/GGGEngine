#include "Material.h"
#include "AssetManager.h"

// =================================================================
// Factory Method
// =================================================================
UniqueResource<rcMaterial> rcMaterial::CreateFromFile(const char* path)
{
  MaterialData* data = MaterialData::Deserialize(path);
  UniqueResource<rcMaterial> ret = rcMaterial::Create(data);
  delete data;
  return ret;
}

UniqueResource<rcMaterial> rcMaterial::Create(const SharedRef<rcShader>& resource)
{
  rcMaterial* ret = new rcMaterial(resource);
  ret->Resource::Init();
  return UniqueResource<rcMaterial>(ret);
}

UniqueResource<rcMaterial> rcMaterial::Create(const MaterialData* data)
{
  SharedRef<rcShader> shader = data->shader_unique_id_ != 0 ? 
    AssetManager::Load<rcShader>(data->shader_unique_id_) : 
    AssetManager::Load<rcShader>(DefaultUniqueID::SHADER_NO_SHADING);
  rcMaterial* ret = new rcMaterial(shader);
  
  ret->texture_ = data->main_tex_unique_id_ != 0 ?
    AssetManager::Load<rcTexture>(data->main_tex_unique_id_) :
    nullptr;
  ret->tiling_ = data->tiling_;
  ret->tiling_offset_ = data->tiling_offset_;
  ret->color_ = data->color_;
  ret->billbording_ = data->billbording_;

  for (const auto& pair : data->texture_properties_)
  {
    ret->TextureProperty(pair.first) = AssetManager::Load<rcTexture>(pair.second);
  }

  for (const auto& pair : data->properties_)
  {
    ret->properties_[pair.first] = pair.second->Clone();
  }
  ret->Resource::Init();
  return UniqueResource<rcMaterial>(ret);
}

// =================================================================
// Constructor / Destructor
// =================================================================
rcMaterial::rcMaterial(const SharedRef<rcShader>& shader)
  : shader_(shader)
  , technique_("Default")
  , queue_(Graphics::RenderQueue::RQ_GEOMETRY)
  , properties_()
  , texture_()
  , tiling_()
  , tiling_offset_()
  , color_()
  , billbording_()
{
}

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
UniqueResource<rcMaterial> rcMaterial::Clone() const
{
  UniqueResource<rcMaterial> ret = this->InitialClone();
 
  ret->queue_ = this->queue_;
  ret->texture_ = this->texture_;
  for (auto pair : this->properties_)
  {
    ret->properties_[pair.first] = pair.second->Clone();
  }

  return ret;
}

UniqueResource<rcMaterial> rcMaterial::InitialClone() const
{
  NATIVE_ASSERT(this->shader_, "シェーダーが未定義です");
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
// setter/getter
// =================================================================
void rcMaterial::SetShader(const SharedRef<rcShader>& shader)
{
  this->shader_ = shader;
}

void rcMaterial::SetMainTexture(const SharedRef<const rcTexture>& texture)
{
  this->texture_ = texture;
}
