#include "Director.h"

#include <Util/FileUtil.h>
#include <Constants/Extensions.h>
#include <Entity/Default/DefaultAsset.h>

#include <Entity/File/Raw/CSV/CsvAssetEntity.h>
#include <Entity/File/Raw/Json/JsonAssetEntity.h>
#include <Entity/File/Raw/Shader/ShaderAssetEntity.h>
#include <Entity/File/Raw/Sound/SoundAssetEntity.h>

#include <Entity/Default/Material/DefaultMaterialAssetConverterFactory.h>

// =================================================================
// Methods
// =================================================================
void AssetConverterDirector::Init()
{
  AssetConverterDirector* self = &Self();

  GG_ASSERT(!self->setting_ && !self->converter_manager_ && !self->context_, "Init���Q��A���ŌĂяo����܂���");
 
  FileUtil::PrepareDirectories();

  self->setting_ = CerealIO::Json::SafeImport<Setting>(FileUtil::GetSettingPath().c_str());
  if (!self->setting_)
  {
    self->setting_ = Setting::Create();
  }

  self->unique_id_table_ = CerealIO::Json::SafeImport<UniqueIdTable>(FileUtil::GetMidDataUniqueIdTablePath().c_str());
  if (!self->unique_id_table_)
  {
    self->unique_id_table_ = new UniqueIdTable();
  }

  self->converter_manager_ = new AssetConverterManager();
  self->context_ = new AssetConverterContext(self->unique_id_table_, self->converter_manager_);
  AssetManager::Init(self->unique_id_table_);

  using namespace DefaultUniqueID;
  using namespace DefaultAsset;
  self->context_->RegisterDefaultUniqueID(SHADER_FLAT,          SHADER_PATH_WHITE);
  self->context_->RegisterDefaultUniqueID(SHADER_GOURAUD,       SHADER_PATH_LAMBERT);
  self->context_->RegisterDefaultUniqueID(SHADER_PHONG,         SHADER_PATH_PHONG);
  self->context_->RegisterDefaultUniqueID(SHADER_BLIN,          SHADER_PATH_WHITE);
  self->context_->RegisterDefaultUniqueID(SHADER_TOON,          SHADER_PATH_WHITE);
  self->context_->RegisterDefaultUniqueID(SHADER_OREN_NAYAR,    SHADER_PATH_WHITE);
  self->context_->RegisterDefaultUniqueID(SHADER_MINNAERT,      SHADER_PATH_WHITE);
  self->context_->RegisterDefaultUniqueID(SHADER_COOK_TORRANCE, SHADER_PATH_WHITE);
  self->context_->RegisterDefaultUniqueID(SHADER_NO_SHADING,    SHADER_PATH_WHITE);
  self->context_->RegisterDefaultUniqueID(SHADER_FRESNEL,       SHADER_PATH_WHITE);

  self->context_->RegisterDefaultUniqueID(SHADER_SPRITE, SHADER_PATH_SPRITE);
  self->context_->RegisterDefaultUniqueID(SHADER_STENCIL_SHADOW, SHADER_PATH_STENCIL_SHADOW);

  self->context_->RegisterDefaultUniqueID(MESH_CUBE,    MESH_PATH_CUBE);
  self->context_->RegisterDefaultUniqueID(MESH_PLANE,   MESH_PATH_PLANE);

  self->context_->RegisterDefaultUniqueID(MATERIAL_WHITE,   MATERIAL_PATH_WHITE);
  self->context_->RegisterDefaultUniqueID(MATERIAL_LAMBERT, MATERIAL_PATH_LAMBERT);
  self->context_->RegisterDefaultUniqueID(MATERIAL_SPRITE,  MATERIAL_PATH_SPRITE);
  self->context_->RegisterDefaultUniqueID(MATERIAL_STENCIL_SHADOW, MATERIAL_PATH_STENCIL_SHADOW);


  // �ˑ��֌W�𐳂��������ł��鏇�Ԃ�AssetConverter��o�^����K�v������

  // Raw
  self->converter_manager_->AddConverter(CsvAssetEntity::CreateConverter());
  self->converter_manager_->AddConverter(JsonAssetEntity::CreateConverter());
  self->converter_manager_->AddConverter(ShaderAssetEntity::CreateConverter());
  self->converter_manager_->AddConverter(SoundAssetEntity::CreateConverter());

  // Texture
  self->converter_manager_->AddConverter(self->setting_->texture_asset_converter_factory.Create(self->context_));

  // Mesh
  self->converter_manager_->AddConverter(self->setting_->default_mesh_asset_converter_factory.Create(self->context_));
  self->converter_manager_->AddConverter(self->setting_->model_mesh_asset_converter_factory.Create(self->context_));

  // Material
  self->converter_manager_->AddConverter(self->setting_->model_material_asset_converter_factory.Create(self->context_));
  self->converter_manager_->AddConverter(DefaultMaterialAssetConverterFactory::Create(self->context_));

  // Model
  self->converter_manager_->AddConverter(self->setting_->model_asset_converter_factory.Create(self->context_));
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

void AssetConverterDirector::Import()
{
  AssetConverterDirector* self = &Self();

  //Importer���Ή����Ă���t�@�C����AssetInfo���쐬
  //UniqueId�e�[�u���Ȃǂ̍쐬
  //Importer�ւ�AssetInfo�̃Z�b�g
  FileUtil::CrawlInputDirectory([&](const URI& uri)
  {
    //AssetInfo�����������Η\�񐬌�
    if (self->context_->Reserve(uri, uri))
    {
      return;
    }
    //�\�񂪎��s���A�g���q�����^�f�[�^�ȊO�̏ꍇ�̓X�L�b�v�����������O�ɕ\��
    if (uri.GetExtension() != Extensions::META)
    {
      Logger::ImportSkipAssetLog(uri);
    }
  });

  //Converter�̃C���|�[�g�\�񂪖����Ȃ�܂�Converter�̃C���|�[�g����
  while (
    //�C�e���[�^�[�̃��[�h���P���s��
    //�P���s�����R�̓C���|�[�g�\��̃��[�v���ɃT�u�A�Z�b�g�̐����ɂ��
    //�C���|�[�g�\��̑}���̊댯������������
    self->converter_manager_->Fire([&](IAssetConverter* converter)
    {
      return converter->ImportOnce(self->context_);
    })
  );

  self->converter_manager_->VisitAllEntity([&](AssetEntity* entity)
  {
    entity->CommitChanges();
  });
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