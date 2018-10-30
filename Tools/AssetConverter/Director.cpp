#include "Director.h"

#include "FileUtil.h"
#include "Extensions.h"
#include "DefaultAsset.h"

#include "CsvAssetConverterFactory.h"
#include "JsonAssetConverterFactory.h"
#include "ShaderAssetConverterFactory.h"
#include "SoundAssetConverterFactory.h"

#include "DefaultMaterialAssetConverterFactory.h"

// =================================================================
// Methods
// =================================================================
void AssetConverterDirector::Init()
{
  GG_ASSERT(!this->setting_ && !this->converter_manager_ && !this->context_, "Init���Q��A���ŌĂяo����܂���");
 
  FileUtil::PrepareDirectories();

  this->setting_ = CerealIO::Json::SafeImport<Setting>(FileUtil::GetSettingPath().c_str());
  if (!this->setting_)
  {
    this->setting_ = Setting::Create();
  }

  this->unique_id_table_ = CerealIO::Json::SafeImport<UniqueIdTable>(FileUtil::GetMidDataUniqueIdTablePath().c_str());
  if (!this->unique_id_table_)
  {
    this->unique_id_table_ = new UniqueIdTable();
  }

  this->converter_manager_ = new AssetConverterManager();
  this->context_ = new AssetConverterContext(this->unique_id_table_, this->converter_manager_);

  using namespace DefaultUniqueID;
  using namespace DefaultAsset;
  this->context_->RegisterDefaultUniqueID(SHADER_FLAT,          SHADER_PATH_WHITE);
  this->context_->RegisterDefaultUniqueID(SHADER_GOURAUD,       SHADER_PATH_LAMBERT);
  this->context_->RegisterDefaultUniqueID(SHADER_PHONG,         SHADER_PATH_PHONG);
  this->context_->RegisterDefaultUniqueID(SHADER_BLIN,          SHADER_PATH_WHITE);
  this->context_->RegisterDefaultUniqueID(SHADER_TOON,          SHADER_PATH_WHITE);
  this->context_->RegisterDefaultUniqueID(SHADER_OREN_NAYAR,    SHADER_PATH_WHITE);
  this->context_->RegisterDefaultUniqueID(SHADER_MINNAERT,      SHADER_PATH_WHITE);
  this->context_->RegisterDefaultUniqueID(SHADER_COOK_TORRANCE, SHADER_PATH_WHITE);
  this->context_->RegisterDefaultUniqueID(SHADER_NO_SHADING,    SHADER_PATH_WHITE);
  this->context_->RegisterDefaultUniqueID(SHADER_FRESNEL,       SHADER_PATH_WHITE);

  this->context_->RegisterDefaultUniqueID(SHADER_SPRITE, SHADER_PATH_SPRITE);

  this->context_->RegisterDefaultUniqueID(MESH_CUBE,    MESH_PATH_CUBE);
  this->context_->RegisterDefaultUniqueID(MESH_PLANE,   MESH_PATH_PLANE);

  this->context_->RegisterDefaultUniqueID(MATERIAL_WHITE,   MATERIAL_PATH_WHITE);
  this->context_->RegisterDefaultUniqueID(MATERIAL_LAMBERT, MATERIAL_PATH_LAMBERT);
  this->context_->RegisterDefaultUniqueID(MATERIAL_SPRITE,  MATERIAL_PATH_SPRITE);

  this->converter_manager_->AddConverter(this->setting_->default_mesh_asset_converter_factory.Create(this->context_));
  this->converter_manager_->AddConverter(DefaultMaterialAssetConverterFactory::Create(this->context_));

  this->converter_manager_->AddConverter(this->setting_->texture_asset_converter_factory.Create(this->context_));
  this->converter_manager_->AddConverter(this->setting_->model_asset_converter_factory.Create(this->context_));
  this->converter_manager_->AddConverter(this->setting_->model_mesh_asset_converter_factory.Create(this->context_));
  this->converter_manager_->AddConverter(this->setting_->model_material_asset_converter_factory.Create(this->context_));
  this->converter_manager_->AddConverter(CsvAssetEntity::CreateConverter());
  this->converter_manager_->AddConverter(JsonAssetEntity::CreateConverter());
  this->converter_manager_->AddConverter(ShaderAssetEntity::CreateConverter());
  this->converter_manager_->AddConverter(SoundAssetEntity::CreateConverter());
}

void AssetConverterDirector::Uninit()
{
  CerealIO::Json::Export(FileUtil::GetMidDataUniqueIdTablePath().c_str(), this->unique_id_table_);
  CerealIO::Json::Export(FileUtil::GetSettingPath().c_str(), this->setting_);

  delete this->context_;
  delete this->converter_manager_;
  delete this->setting_;
  delete this->unique_id_table_;
}

void AssetConverterDirector::Import()
{
  //Importer���Ή����Ă���t�@�C����AssetInfo���쐬
  //UniqueId�e�[�u���Ȃǂ̍쐬
  //Importer�ւ�AssetInfo�̃Z�b�g
  FileUtil::CrawlInputDirectory([&](const URI& uri)
  {
    //AssetInfo�����������Η\�񐬌�
    if (this->context_->Reserve(uri))
    {
      return;
    }
    //�\�񂪎��s���A�g���q�����^�f�[�^�ȊO�̏ꍇ�̓X�L�b�v�����������O�ɕ\��
    if (uri.GetExtension() != Extensions::META)
    {
      std::cout << "skip \"" << uri.GetFullPath() << "\" " << std::endl;
    }
  });

  //Converter�̃C���|�[�g�\�񂪖����Ȃ�܂�Converter�̃C���|�[�g����
  while (
    //�C�e���[�^�[�̃��[�h���P���s��
    //�P���s�����R�̓C���|�[�g�\��̃��[�v���ɃT�u�A�Z�b�g�̐����ɂ��
    //�C���|�[�g�\��̑}���̊댯������������
    this->converter_manager_->Fire([&](IAssetConverter* converter)
    {
      return converter->ImportOnce(this->context_);
    })
  );
}

void AssetConverterDirector::Export()
{
  this->converter_manager_->VisitAll([&](IAssetConverter* converter)
  {
    converter->Export(this->context_);
  });

  CerealIO::Binary::Export(FileUtil::GetArchiveUniqueIdTablePath().c_str(), this->unique_id_table_);
}

void AssetConverterDirector::CreateProgram()
{
  //======================================
  //Asset.h
  //======================================
  std::string header;
  header.append("#pragma once\n");
  header.append("\n");
  header.append("namespace Asset\n");
  header.append("{\n");
  header.append("\n");

  this->converter_manager_->VisitAll([&](const IAssetConverter* converter)
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

  this->converter_manager_->VisitAll([&](const IAssetConverter* converter)
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
