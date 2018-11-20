#include "CharacterModelAssetImporter.h"

#include <Constants/Extensions.h>
#include <Converter/AssetConverterContext.h>
#include <Util/FileUtil.h>

#include <Director.h>

#include <Entity/File/Model/DynamicMesh/ModelDynamicMeshAssetEntity.h>

#include <Entity/File/Model/AssimpImportUtil.h>

// =================================================================
// Constructor / Destructor
// =================================================================
CharacterModelAssetImporter::CharacterModelAssetImporter(const std::vector<std::string>& extensions)
  : AssetImporter(extensions)
{
}

// =================================================================
// Methods
// =================================================================
//SharedRef<ModelDynamicMeshAssetEntity> ImportMesh(const AssetMetaData* model_asset_info, const aiScene* scene, AssetConverterContext* context)
//{
//}

SharedRef<CharacterModelAssetEntity> CharacterModelAssetImporter::ImportProcess(AssetMetaData* meta, AssetConverterContext* context)
{
  return SharedRef<CharacterModelAssetEntity>();
}
