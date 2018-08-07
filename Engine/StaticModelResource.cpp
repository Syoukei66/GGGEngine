#include "StaticModelResource.h"
#include "EngineAsset.h"

static const char* PROPERTY_TINT = "_Tint";
static const char* PROPERTY_MAIN_TEX = "_MainTex";
static const char* PROPERTY_NORMAL_MAP = "_NormalMap";
static const char* PROPERTY_BUMP_SCALE = "_BumpScale";
static const char* PROPERTY_METALLIC_MAP = "_MetallicMap";
static const char* PROPERTY_METALLIC = "_Metallic";
static const char* PROPERTY_SMOOTHNESS = "_Smoothness";
static const char* PROPERTY_EMISSION_MAP = "_EmissionMap";
static const char* PROPERTY_EMISSION = "_Emission";
static const char* PROPERTY_OCCLUSION_MAP = "_OcclusionMap";
static const char* PROPERTY_OCCLUSION_STRENGTH = "_OcclusionStrength";
static const char* PROPERTY_TILING = "_Tiling";
static const char* PROPERTY_TILING_OFFSET = "_TilingOffset";

static const char* PROPERTY_DETAIL_TEX = "_DetailTex";
static const char* PROPERTY_DETAIL_NORMAL_MAP = "_DetailNormalMap";
static const char* PROPERTY_DETAIL_BUMP_SCALE = "_DetailBumpScale";
static const char* PROPERTY_DETAIL_MASK = "_DetailMask";
static const char* PROPERTY_DETAIL_TILING = "_DetailTiling";
static const char* PROPERTY_DETAIL_TILING_OFFSET = "_DetailTilingOffset";

static const char* PROPERTY_ALPHA_CUTOFF = "_AlphaCutoff";

StaticModelResource::StaticModelResource(StaticModelData* data)
  : data_(data)
  , vertex_buffer_(INativeVertexBuffer::Create(data->vertex_count_, data->polygon_count_, data->vertex_format_))
  , index_buffers_(data->submesh_count_)
  , mesh_(vertex_buffer_, index_buffers_.data, data->submesh_count_)
  , materials_(data->material_count_)
{
  //Vertex Buffer
  T_FLOAT* vertex_data;
  this->vertex_buffer_->Lock((void**)&vertex_data);
  const T_UINT32 vertex_count = data->vertex_count_ * data->vertex_size_;
  for (T_UINT32 i = 0; i < vertex_count; ++i)
  {
    vertex_data[i] = data->data_[i];
  }
  this->vertex_buffer_->Unlock();

  //Index Buffer
  for (T_UINT32 i = 0, ii = 0; i < data->submesh_count_; ++i)
  {
    T_UINT32* index_data;
    this->index_buffers_[i] = INativeIndexBuffer::Create(data->submesh_index_counts_[i]);
    this->index_buffers_[i]->Lock((void**)&index_data);
    for (T_UINT32 j = 0; j < data->submesh_index_counts_[i]; ++j)
    {
      index_data[j] = data->indices_[ii + j];
    }
    this->index_buffers_[i]->Unlock();
    ii += data->submesh_index_counts_[i];
  }

  //Material
  for (T_UINT8 i = 0; i < data->material_count_; ++i)
  {
    Material* mat = this->materials_[i] = EngineAsset::Material::DEFAULT.Clone();
    if (data->materials_[i].albedo_map_ != 0)
    {
      //白一色テクスチャが求められる
      mat->TextureProperty(PROPERTY_MAIN_TEX) = Texture::Create(data->);
    }
    else
    {
      mat = 
    }
  }
}

StaticModelResource::~StaticModelResource()
{
  for (INativeIndexBuffer* index_buffer : this->index_buffers_)
  {
    delete index_buffer;
  }
  delete this->vertex_buffer_;
  delete this->data_;
}

GameObject3D* StaticModelResource::CreateGameObject()
{
  GameObject3D* ret = new GameObject3D();
  NATIVE_ASSERT(false, "まだできてません！");
  return ret;
}
