#pragma once

class rcMaterial;
class rcMesh;

struct ModelData
{
  // =================================================================
  // GGG Statement
  // =================================================================
  GG_SERIALIZABLE(ModelData)
  {
    archive(mesh_unique_id_);
    archive(material_unique_ids_);
  }

  // =================================================================
  // Data Member
  // =================================================================
public:
  T_FIXED_UINT32 mesh_unique_id_;
  std::vector<T_FIXED_UINT32> material_unique_ids_;
};

class rcModel : public GGAssetObject
{
  // =================================================================
  // GGG Statement
  // =================================================================
  GG_ASSET(rcModel, ModelData);

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  GG_INLINE SharedRef<const rcMesh> GetMesh() const
  {
    return this->mesh_;
  }

  GG_INLINE SharedRef<const rcMaterial> GetMaterial(T_UINT32 index) const
  {
    return this->materials_.at(index);
  }

  GG_INLINE T_UINT32 GetMaterialCount() const
  {
    return this->materials_.size();
  }

  // =================================================================
  // Data Member
  // =================================================================
protected:
  SharedRef<const rcMesh> mesh_;
  std::vector<SharedRef<const rcMaterial>> materials_;

};
