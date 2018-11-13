#pragma once

#include <Entity/AssetEntity.h>

class TextureAssetEntity : public AssetEntity
{
  ENTITY_ID(ID_TEXTURE);

  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  TextureAssetEntity(AssetInfo* info);

  // =================================================================
  // Methods from AssetEntity
  // =================================================================
public:
  virtual void RegisterAssetManager(T_UINT32 uid, const std::string& extension) const override;

  // =================================================================
  // Setter / Getter
  // =================================================================
public:

  // =================================================================
  // Data Members
  // =================================================================
private:

};
