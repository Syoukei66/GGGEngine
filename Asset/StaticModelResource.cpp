#include "StaticModelResource.h"
#include "../Asset/CerealStaticModelIO.h"

// =================================================================
// Factory Method
// =================================================================
StaticModelResource* StaticModelResource::Create(const char* path)
{
  return new StaticModelResource(ModelIO::StaticModel::Import(path));
}

// =================================================================
// Constructor / Destructor
// =================================================================
StaticModelResource::StaticModelResource(StaticModelData* data)
  : data_(data)
  , vertex_buffer_(INativeVertexBuffer::Create(data->vertex_count_, data->polygon_count_, data->vertex_format_))
  , index_buffers_(data->submesh_count_)
  , mesh_(vertex_buffer_, index_buffers_.data(), data->submesh_count_)
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
    StandardMaterial* mat = this->materials_[i] = (StandardMaterial*)asset->default_material->Clone();
    const StaticModelMaterialData& mat_data = data->materials_[i];

    AssetContainer<Texture>* albedo_map = AssetManager::GetInstance().GetAsset<Texture>(mat_data.albedo_map_);
    if (albedo_map)
    {
      mat->SetAlbedoMap(albedo_map->GetContents());
    }

    AssetContainer<Texture>* normal_map = AssetManager::GetInstance().GetAsset<Texture>(mat_data.normal_map_);
    AssetContainer<Texture>* metallic_map = AssetManager::GetInstance().GetAsset<Texture>(mat_data.metallic_map_);
    AssetContainer<Texture>* emission_map = AssetManager::GetInstance().GetAsset<Texture>(mat_data.emission_map_);
    AssetContainer<Texture>* occlusion_map = AssetManager::GetInstance().GetAsset<Texture>(mat_data.occlusion_map_);
    AssetContainer<Texture>* detail_albedo_map = AssetManager::GetInstance().GetAsset<Texture>(mat_data.detail_albedo_map_);
    AssetContainer<Texture>* detail_normal_map = AssetManager::GetInstance().GetAsset<Texture>(mat_data.detail_normal_map_);
    AssetContainer<Texture>* detail_mask_map = AssetManager::GetInstance().GetAsset<Texture>(mat_data.detail_mask_map_);
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

// =================================================================
// Methods
// =================================================================
GameObject3D* StaticModelResource::CreateGameObject()
{
  GameObject3D* ret = new GameObject3D();
  NATIVE_ASSERT(false, "Ç‹ÇæÇ≈Ç´ÇƒÇ‹ÇπÇÒÅI");
  return ret;
}
