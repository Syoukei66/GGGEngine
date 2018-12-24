#include "ShaderAssetImporter.h"

// =================================================================
// Constructor / Destructor
// =================================================================
ShaderAssetImporter::ShaderAssetImporter(const std::vector<std::string>& extensions)
  : AssetImporter(extensions)
{
}

// =================================================================
// Methods
// =================================================================
SharedRef<ShaderAssetEntity> ShaderAssetImporter::ImportProcess(AssetMetaData* meta, AssetConverterContext* context)
{
  ShaderData* data = new ShaderData();

  data->name_ = "test";

  PassData pass = PassData();

  std::string code = FileUtil::TextFile_Read(meta->GetInputPath().c_str());

  // 頂点シェーダーコンパイル

  // ピクセルシェーダーコンパイル


  return ShaderAssetEntity::Create(meta, data);
}
