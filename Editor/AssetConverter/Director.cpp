#include "Director.h"

#include <Util/FileUtil.h>
#include <Entity/Default/DefaultAsset.h>

#include <Entity/File/Raw/CSV/CsvAssetEntity.h>
#include <Entity/File/Raw/Json/JsonAssetEntity.h>
#include <Entity/File/Raw/Sound/SoundAssetEntity.h>

#include <Entity/File/Model/Material/ModelMaterialAssetEntity.h>
#include <Entity/File/Model/StaticModel/StaticModelAssetEntity.h>
#include <Entity/File/Model/CharacterModel/CharacterModelAssetEntity.h>

#include <Entity/File/Shader/ShaderAssetEntity.h>

#include <Entity/File/Texture/TextureAssetEntity.h>

#include <Entity/Default/Material/DefaultMaterialAssetConverterFactory.h>

// =================================================================
// Methods
// =================================================================
void AssetConverterDirector::Init()
{
  AssetConverterDirector* self = &Self();

  GG_ASSERT(!self->setting_ && !self->converter_manager_ && !self->context_, "Init���Q��A���ŌĂяo����܂���");
 
  FileUtil::PrepareDefaultDirectories();

  // (1)
  // �ݒ�̃��[�h
  self->setting_ = CerealIO::Json::SafeImport<Setting>(FileUtil::GetSettingPath().c_str());
  if (!self->setting_)
  {
    self->setting_ = Setting::Create();
  }

  // (2)
  // UniqueId�e�[�u���̃��[�h
  self->unique_id_table_ = CerealIO::Json::SafeImport<UniqueIdTable>(FileUtil::GetMidDataUniqueIdTablePath().c_str());
  if (!self->unique_id_table_)
  {
    self->unique_id_table_load_failed_ = true;
    self->unique_id_table_ = new UniqueIdTable();
  }

  // (3)
  // Converter�̓o�^
  self->converter_manager_ = new AssetConverterManager();
  self->context_ = new AssetConverterContext(self->unique_id_table_, self->converter_manager_);
  AssetManager::Init(self->unique_id_table_);

  // Raw
  self->converter_manager_->AddConverter(CsvAssetEntity::CreateConverter());
  self->converter_manager_->AddConverter(JsonAssetEntity::CreateConverter());
  self->converter_manager_->AddConverter(SoundAssetEntity::CreateConverter());

  // Texture
  self->converter_manager_->AddConverter(TextureAssetEntity::CreateConverter());

  // Shader
  self->converter_manager_->AddConverter(ShaderAssetEntity::CreateConverter());

  // Mesh
  self->converter_manager_->AddConverter(self->setting_->default_mesh_asset_converter_factory.Create(self->context_));

  // Material
  self->converter_manager_->AddConverter(ModelMaterialAssetEntity::CreateConverter());
  self->converter_manager_->AddConverter(DefaultMaterialAssetConverterFactory::Create(self->context_));

  // Model
  self->converter_manager_->AddConverter(StaticModelAssetEntity::CreateConverter());
  self->converter_manager_->AddConverter(CharacterModelAssetEntity::CreateConverter());

  // (4)
  // �f�t�H���gUniqueId�̓o�^
  using namespace DefaultUniqueID;
  using namespace DefaultAsset;
  self->context_->RegisterDefaultUniqueID(SHADER_ERRROR, SHADER_PATH_ERROR);

  self->context_->RegisterDefaultUniqueID(SHADER_FLAT, SHADER_PATH_UNLIT);
  self->context_->RegisterDefaultUniqueID(SHADER_GOURAUD, SHADER_PATH_LAMBERT);
  self->context_->RegisterDefaultUniqueID(SHADER_PHONG, SHADER_PATH_PHONG);
  self->context_->RegisterDefaultUniqueID(SHADER_BLIN, SHADER_PATH_WHITE);
  self->context_->RegisterDefaultUniqueID(SHADER_TOON, SHADER_PATH_WHITE);
  self->context_->RegisterDefaultUniqueID(SHADER_OREN_NAYAR, SHADER_PATH_WHITE);
  self->context_->RegisterDefaultUniqueID(SHADER_MINNAERT, SHADER_PATH_WHITE);
  self->context_->RegisterDefaultUniqueID(SHADER_COOK_TORRANCE, SHADER_PATH_WHITE);
  self->context_->RegisterDefaultUniqueID(SHADER_NO_SHADING, SHADER_PATH_WHITE);
  self->context_->RegisterDefaultUniqueID(SHADER_FRESNEL, SHADER_PATH_WHITE);

  self->context_->RegisterDefaultUniqueID(MESH_CUBE, MESH_PATH_CUBE);
  self->context_->RegisterDefaultUniqueID(MESH_PLANE, MESH_PATH_PLANE);
  self->context_->RegisterDefaultUniqueID(MESH_CAPSULE, MESH_PATH_CAPSULE);
  self->context_->RegisterDefaultUniqueID(MESH_CUBE_SPHERE, MESH_PATH_CUBE_SPHERE);
  self->context_->RegisterDefaultUniqueID(MESH_UV_SPHERE, MESH_PATH_UV_SPHERE);

  self->context_->RegisterDefaultUniqueID(MATERIAL_WHITE, MATERIAL_PATH_WHITE);
  self->context_->RegisterDefaultUniqueID(MATERIAL_LAMBERT, MATERIAL_PATH_LAMBERT);
  self->context_->RegisterDefaultUniqueID(MATERIAL_UNLIT, MATERIAL_PATH_UNLIT);

  self->context_->RegisterDefaultUniqueID(TEXTURE_WHITE, TEXTURE_PATH_WHITE);
}

void AssetConverterDirector::Uninit()
{
  AssetConverterDirector* self = &Self();

  CerealIO::Json::Export(FileUtil::GetMidDataUniqueIdTablePath().c_str(), self->unique_id_table_);
  CerealIO::Json::Export(FileUtil::GetSettingPath().c_str(), self->setting_);

  delete self->context_;
  delete self->converter_manager_;
  delete self->setting_;
  //delete self->unique_id_table_;
}

void AssetConverterDirector::Fetch()
{

}

void AssetConverterDirector::Export()
{
  AssetConverterDirector* self = &Self();

  self->converter_manager_->VisitAll([&](IAssetConverter* converter)
  {
    converter->Export(self->context_);
  });

  CerealIO::Binary::Export(FileUtil::CreateOutputPath(FileUtil::GetArchiveUniqueIdTablePath()).c_str(), self->unique_id_table_);
}

void AssetConverterDirector::CreateProgram()
{
  AssetConverterDirector* self = &Self();

  //======================================
  //Asset.h
  //======================================
  std::string header;
  header.append("#pragma once\n");
  header.append("\n");
  header.append("namespace Asset\n");
  header.append("{\n");
  header.append("\n");

  self->converter_manager_->VisitAll([&](const IAssetConverter* converter)
  {
    converter->CreateHeaderProgram(&header);
  });

  header.append("} // namespace Asset\n");

  std::cout << "//======================================" << std::endl;
  std::cout << "//Asset.h" << std::endl;
  std::cout << "//======================================" << std::endl;
  std::cout << header << std::endl;

  const std::string header_path = FileUtil::CreateProjectFilePath("Asset.h");
  std::ofstream output_header(header_path);
  if (output_header)
  {
    output_header << header;
    output_header.close();
  }

  //======================================
  //Asset.cpp
  //======================================
  std::string cpp;

  cpp.append("#include \"Asset.h\"\n");
  cpp.append("\n");
  cpp.append("namespace Asset\n");
  cpp.append("{\n");
  cpp.append("\n");

  self->converter_manager_->VisitAll([&](const IAssetConverter* converter)
  {
    converter->CreateCppProgram(&cpp);
  });

  cpp.append("} // namespace Asset\n");

  std::cout << "//======================================" << std::endl;
  std::cout << "//Asset.cpp" << std::endl;
  std::cout << "//======================================" << std::endl;
  std::cout << cpp << std::endl;

  const std::string cpp_path = FileUtil::CreateProjectFilePath("Asset.cpp");
  std::ofstream output_cpp(cpp_path);
  if (output_cpp)
  {
    output_cpp << cpp;
    output_cpp.close();
  }
}
