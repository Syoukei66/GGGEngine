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

// Import Viewer
//#include <Scene/AssetViewer/Text/TextViewerBehavior.h>

// =================================================================
// Methods
// =================================================================
void AssetConverterDirector::Init()
{
  AssetConverterDirector* self = &Self();

  GG_ASSERT(!self->setting_ && !self->context_, "Initが２回連続で呼び出されました");
 
  FileUtil::PrepareDefaultDirectories();

  // (1)
  // 設定のロード
  self->setting_ = CerealIO::Json::SafeImport<Setting>(FileUtil::GetSettingPath().c_str());
  if (!self->setting_)
  {
    self->setting_ = Setting::Create();
  }

  // (2)
  // UniqueIdテーブルのロード
  self->unique_id_table_ = CerealIO::Json::SafeImport<UniqueIdTable>(FileUtil::GetMidDataUniqueIdTablePath().c_str());
  if (!self->unique_id_table_)
  {
    self->unique_id_table_ = new UniqueIdTable();
    self->unique_id_table_load_failed_ = true;
  }

  // (3)
  // Converterの登録
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
  self->context_->AddConverter(new StaticModelAssetConverter("StaticModel", "rcStaticModel", {"fbx", "x", "blend"}, 1, 1));
  self->context_->AddConverter(new CharacterModelAssetConverter("CharacterModel", "rcCharacterModel", {"dae"}, 1, 1));

  // (4)
  // デフォルトアセットの登録
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

  self->setting_->default_mesh_asset_converter_factory.Create(default_mesh_converter, self->context_);
  DefaultMaterialAssetEntityFactory::Create(default_material_converter, self->context_);

  // (5)
  // デフォルトアセットのロード
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
