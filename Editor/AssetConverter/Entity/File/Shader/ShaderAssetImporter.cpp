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

  // ���_�V�F�[�_�[�R���p�C��

  // �s�N�Z���V�F�[�_�[�R���p�C��


  return ShaderAssetEntity::Create(meta, data);
}
