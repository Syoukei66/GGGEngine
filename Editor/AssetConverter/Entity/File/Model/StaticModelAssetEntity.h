#pragma once

#include <Entity/File/FileAssetEntity.h>

class StaticModelAssetEntity : public FileAssetEntity<StaticModelData, rcStaticModel>
{
  // =================================================================
  // GGG Statement
  // =================================================================
  ENTITY_ID(ID_STATIC_MODEL);
  GG_OBJECT(StaticModelAssetEntity);
  GG_CREATE_FUNC_2(StaticModelAssetEntity, AssetMetaData*, StaticModelData*)
  {
    return FileAssetEntity<StaticModelData, rcStaticModel>::Init(arg0, arg1);
  }

};