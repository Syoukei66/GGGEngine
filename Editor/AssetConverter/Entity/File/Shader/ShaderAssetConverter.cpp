#include "ShaderAssetConverter.h"
#include <Editor/Tools/ShaderCompiler/Parser/ShaderCompiler.h>
#include <Entity/AssetMetaData.h>
#include <Entity/AssetEntity.h>
#include <Converter/AssetConverterContext.h>

// =================================================================
// Methods from AssetConverter
// =================================================================
IAssetDataContainer* ShaderAssetConverter::ImportProcess(AssetMetaData* meta, AssetConverterContext* context) const
{
  ShaderData* data = new ShaderData();

  data->name_ = "test";

  PassData pass = PassData();

  std::string code = FileUtil::TextFile_Read(meta->GetInputPath().c_str());

  try
  {
    ShaderCompiler(code, meta->GetInputDirectoryPath()).Compile(data);
  }
  catch (ParseException e)
  {
    SharedRef<AssetEntity> entity = context->GetEntity(DefaultUniqueID::SHADER_ERRROR);
    Log::Info(e.message.c_str());
    (*data) = *entity->GetData<ShaderData>();
  }

  return new AssetDataContainer<ShaderData>(data, this);
}
