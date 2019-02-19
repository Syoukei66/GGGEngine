#include "Director.h"

#include <Util/FileUtil.h>
#include <Entity/Default/DefaultAsset.h>

// Import Converter
#include <Entity/Default/DefaultAssetConverter.h>
#include <Entity/Raw/RawAssetConverter.h>

#include <Entity/File/Model/StaticModel/StaticModelConverter.h>
#include <Entity/File/Model/CharacterModel/CharacterModelConverter.h>

#include <Entity/File/Shader/ShaderAssetConverter.h>

#include <Entity/File/Texture/TextureAssetConverter.h>

#include <Entity/File/Material/MaterialAssetConverter.h>

#include <Entity/File/Mesh/MeshAssetConverter.h>

#include <Entity/Default/Material/DefaultMaterialAssetEntityFactory.h>

#include <Engine/Director.h>

// Import Viewer
//#include <Scene/AssetViewer/Text/TextViewerBehavior.h>

// =================================================================
// Methods
// =================================================================
void AssetConverterDirector::Init(IAssetConverterAddIn* addin)
{
  AssetConverterDirector* self = &Self();

  GG_ASSERT(!self->setting_ && !self->context_, "Init���Q��A���ŌĂяo����܂���");
 
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
    self->unique_id_table_ = new UniqueIdTable();
    self->unique_id_table_load_failed_ = true;
  }

  // (3)
  // Converter�̓o�^
  using namespace DefaultUniqueID;
  self->context_ = new AssetConverterContext(self->unique_id_table_);
  AssetManager::Init(self->unique_id_table_);

  // Raw
  self->context_->AddConverter(new RawAssetConverter<rcCsvData>("CSV", "rcCsvData", {"csv"}));
  self->context_->AddConverter(new RawAssetConverter<rcJsonData>("Json", "rcJsonData", { "json" }));
  self->context_->AddConverter(new RawAssetConverter<rcAudioClip>("Sound", "rcAudioClip", { "wav" }));

  // Texture
  self->context_->AddConverter(new TextureAssetConverter("Texture", "rcTexture", {"jpg", "png", "tga", "bmp"}, 1, 1));
  self->context_->AddDefaultAssetConverter(new TextureAssetConverter("DefaultTexture", "rcTexture", { "jpg", "png", "tga", "bmp" }, 2, 0));

  // Shader
  self->context_->AddConverter(new ShaderAssetConverter("Shader", "rcShader", {"shader"}, 1, 1));
  self->context_->AddDefaultAssetConverter(new ShaderAssetConverter("DefaultShader", "rcShader", { "shader" }, 2, 0));

  // Mesh
  self->context_->AddConverter(new MeshAssetConverter("Mesh", "rcMesh", {"mesh"}, 1, 1));
  AssetConverter* default_mesh_converter = self->context_->AddDefaultAssetConverter(new DefaultAssetConverter<rcMesh, StaticMeshData, StaticMeshViewerBehavior>("DefaultMesh", "rcMesh", {}));

  // Material
  self->context_->AddConverter(new MaterialAssetConverter("Material", "rcMaterial", {"mat"}, 1, 1));
  AssetConverter* default_material_converter = self->context_->AddDefaultAssetConverter(new DefaultAssetConverter<rcMaterial, MaterialData, MaterialViewerBehavior>("DefaultMaterial", "rcMaterial", {TEXTURE_WHITE}));

  // Model
  self->context_->AddConverter(new StaticModelAssetConverter("StaticModel", "rcStaticModel", {"fbx", "x", "blend", "obj"}, 1, 1));
  self->context_->AddConverter(new CharacterModelAssetConverter("CharacterModel", "rcCharacterModel", {"dae"}, 1, 1));

  if (addin)
  {
    addin->RegisterConverter(self->context_);
  }

  self->context_->CommitConvertes();

  // (4)
  // �f�t�H���g�A�Z�b�g�̓o�^ / ���[�h
  self->Fetch();

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

  self->context_->RegisterDefaultUniqueID(TEXTURE_WHITE, TEXTURE_PATH_WHITE);
  self->context_->RegisterDefaultUniqueID(TEXTURE_BLACK, TEXTURE_PATH_BLACK);
  self->context_->RegisterDefaultUniqueID(TEXTURE_GRAY, TEXTURE_PATH_GRAY);
  self->context_->RegisterDefaultUniqueID(TEXTURE_BUMP, TEXTURE_PATH_BUMP);

  self->context_->RegisterDefaultUniqueID(MESH_CUBE, MESH_PATH_CUBE);
  self->context_->RegisterDefaultUniqueID(MESH_PLANE, MESH_PATH_PLANE);
  self->context_->RegisterDefaultUniqueID(MESH_CAPSULE, MESH_PATH_CAPSULE);
  self->context_->RegisterDefaultUniqueID(MESH_CUBE_SPHERE, MESH_PATH_CUBE_SPHERE);
  self->context_->RegisterDefaultUniqueID(MESH_UV_SPHERE, MESH_PATH_UV_SPHERE);

  self->context_->RegisterDefaultUniqueID(MATERIAL_WHITE, MATERIAL_PATH_WHITE);
  self->context_->RegisterDefaultUniqueID(MATERIAL_LAMBERT, MATERIAL_PATH_LAMBERT);
  self->context_->RegisterDefaultUniqueID(MATERIAL_UNLIT, MATERIAL_PATH_UNLIT);

  self->setting_->default_mesh_asset_converter_factory.Create(default_mesh_converter, self->context_);
  DefaultMaterialAssetEntityFactory::Create(default_material_converter, self->context_);

  if (addin)
  {
    addin->RegisterDefaultAsset(self->context_);
  }

  self->Fetch();
  for (const auto& pair : self->unique_id_table_->GetDefaultAssetUniqueIdTable())
  {
    const SharedRef<AssetEntity>& entity = self->context_->GetEntity(pair.second);
    entity->Load(self->context_);
  }
}

void AssetConverterDirector::Uninit()
{
  AssetConverterDirector* self = &Self();

  CerealIO::Json::Export(FileUtil::GetMidDataUniqueIdTablePath().c_str(), self->unique_id_table_);
  CerealIO::Json::Export(FileUtil::GetSettingPath().c_str(), self->setting_);

  delete self->context_;
  delete self->setting_;
  //delete self->unique_id_table_;
}

void AssetConverterDirector::Fetch()
{
  AssetConverterDirector* self = &Self();

  self->context_->Fetch();
}

void AssetConverterDirector::Export()
{
  AssetConverterDirector* self = &Self();

  self->context_->VisitAllEntity([&](const SharedRef<AssetEntity>& entity)
  {
    entity->Export(self->context_);
  });

  CerealIO::Binary::Export(FileUtil::CreateOutputPath(FileUtil::GetArchiveUniqueIdTablePath()).c_str(), self->unique_id_table_);
}

void AssetConverterDirector::CreateProgram()
{
  AssetConverterDirector* self = &Self();

  std::unordered_map<AssetConverter*, std::vector<SharedRef<AssetEntity>>> entity_map = std::unordered_map<AssetConverter*, std::vector<SharedRef<AssetEntity>>>();
  self->context_->VisitAllEntity([&](const SharedRef<AssetEntity>& entity)
  {
    AssetConverter* converter = entity->GetConverter(self->context_);
    const auto& itr = entity_map.find(converter);
    if (itr == entity_map.end())
    {
      entity_map[converter] = std::vector<SharedRef<AssetEntity>>();
    }
    entity_map[converter].emplace_back(entity);
  });

  //======================================
  //Asset.h
  //======================================
  std::string header;
  header.append("#pragma once\n");
  header.append("\n");
  header.append("namespace Asset\n");
  header.append("{\n");
  header.append("\n");

  for (const auto& pair : entity_map)
  {
    pair.first->CreateHeaderProgram(pair.second, &header);
  }

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

  for (const auto& pair : entity_map)
  {
    pair.first->CreateCppProgram(pair.second, &cpp);
  }

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

void AssetConverterDirector::Measurement()
{
  AssetConverterDirector* self = &Self();

  Director::SetIgnoreLog(true);

  std::cout << "�L���b�V���f�[�^������..." << std::endl;
  self->context_->VisitAllEntity([&](const SharedRef<AssetEntity>& entity)
  {
    entity->ClearCache();
  }); 
  AssetManager::UnloadCaches();

  std::cout << "�L���b�V���t�@�C��������..." << std::endl;
  const std::string& cache_path = FileUtil::GetCachePath();

  FileUtil::CrawlInputDirectory([](const URI& uri) {
    std::remove(FileUtil::CreateCachePath(uri).c_str());
  });

  std::cout << "//======================================" << std::endl;
  std::cout << "//���A�Z�b�g���[�h���Ԍv���J�n" << std::endl;
  std::cout << "//======================================" << std::endl;

  auto start_raw_asset_load_time = std::chrono::system_clock::now();

  self->context_->VisitAllEntity([&](const SharedRef<AssetEntity>& entity)
  {
    entity->Load(self->context_);
  });

  auto end_raw_asset_load_time = std::chrono::system_clock::now();
  
  std::cout << "//======================================" << std::endl;
  std::cout << "//���A�Z�b�g���[�h���Ԍv���I��" << std::endl;
  std::cout << "//======================================" << std::endl;

  std::cout << "�L���b�V���f�[�^������..." << std::endl;
  self->context_->VisitAllEntity([&](const SharedRef<AssetEntity>& entity)
  {
    entity->ClearCache();
  });
  AssetManager::UnloadCaches();

  std::cout << "//======================================" << std::endl;
  std::cout << "//�œK���A�Z�b�g���[�h���Ԍv���J�n" << std::endl;
  std::cout << "//======================================" << std::endl;

  auto start_converted_asset_load_time = std::chrono::system_clock::now();

  self->context_->VisitAllEntity([&](const SharedRef<AssetEntity>& entity)
  {
    entity->Load(self->context_);
  });

  auto end_converted_asset_load_time = std::chrono::system_clock::now();

  std::cout << "//======================================" << std::endl;
  std::cout << "//�œK���A�Z�b�g���[�h���Ԍv���I��" << std::endl;
  std::cout << "//======================================" << std::endl;

  T_FLOAT raw_asset_load_time = std::chrono::duration_cast<std::chrono::microseconds>(end_raw_asset_load_time - start_raw_asset_load_time).count() * 0.001f * 0.001f;
  T_FLOAT converted_asset_load_time = std::chrono::duration_cast<std::chrono::microseconds>(end_converted_asset_load_time - start_converted_asset_load_time).count() * 0.001f * 0.001f;

  std::cout << "���A�Z�b�g���[�h���ԁ@�@ : " << raw_asset_load_time << "�b" << std::endl;
  std::cout << "�œK���A�Z�b�g���[�h���� : " << converted_asset_load_time << "�b" << std::endl;
  std::cout << "���[�h���� " << raw_asset_load_time / converted_asset_load_time << "�{�������I" << std::endl;

  Director::SetIgnoreLog(false);
}
