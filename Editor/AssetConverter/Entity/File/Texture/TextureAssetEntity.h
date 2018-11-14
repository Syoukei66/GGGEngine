#pragma once

#include <Entity/AssetEntity.h>

class TextureAssetEntity : public AssetEntity
{
  // =================================================================
  // GGG Statement
  // =================================================================
  ENTITY_ID(ID_TEXTURE);
  GG_OBJECT(TextureAssetEntity);
  GG_CREATE_FUNC_1(TextureAssetEntity, AssetInfo*);

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
