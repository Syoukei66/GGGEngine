#include "Director.h"

#include <Core/CerealIO.h>
#include "FileUtil.h"
#include "Extensions.h"

// =================================================================
// Methods
// =================================================================
void Director::Init()
{
  NATIVE_ASSERT(!this->setting_ && !this->converter_manager_ && !this->context_, "Initが２回連続で呼び出されました");
 
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
    using namespace DefaultUniqueID;
    this->unique_id_table_->RegisterDefaultAssetUniqueID(SHADER_FLAT,         "Asset/shader/default/White.cso");
    this->unique_id_table_->RegisterDefaultAssetUniqueID(SHADER_GOURAUD,      "Asset/shader/default/Lambert.cso");
    this->unique_id_table_->RegisterDefaultAssetUniqueID(SHADER_PHONG,        "Asset/shader/default/Phong.cso");
    this->unique_id_table_->RegisterDefaultAssetUniqueID(SHADER_BLIN,         "Asset/shader/default/White.cso");
    this->unique_id_table_->RegisterDefaultAssetUniqueID(SHADER_TOON,         "Asset/shader/default/White.cso");
    this->unique_id_table_->RegisterDefaultAssetUniqueID(SHADER_OREN_NAYAR,   "Asset/shader/default/White.cso");
    this->unique_id_table_->RegisterDefaultAssetUniqueID(SHADER_MINNAERT,     "Asset/shader/default/White.cso");
    this->unique_id_table_->RegisterDefaultAssetUniqueID(SHADER_COOK_TORRANCE,"Asset/shader/default/White.cso");
    this->unique_id_table_->RegisterDefaultAssetUniqueID(SHADER_NO_SHADING,   "Asset/shader/default/White.cso");
    this->unique_id_table_->RegisterDefaultAssetUniqueID(SHADER_FRESNEL,      "Asset/shader/default/White.cso");
    this->unique_id_table_->RegisterDefaultAssetUniqueID(MESH_CUBE,         "");
    this->unique_id_table_->RegisterDefaultAssetUniqueID(MESH_PLANE,        "");
    this->unique_id_table_->RegisterDefaultAssetUniqueID(MESH_SPRITE,       "");
    this->unique_id_table_->RegisterDefaultAssetUniqueID(MATERIAL_WHITE,    "");
    this->unique_id_table_->RegisterDefaultAssetUniqueID(MATERIAL_LAMBERT,  "");
    this->unique_id_table_->RegisterDefaultAssetUniqueID(MATERIAL_SPRITE,   "");
  }

  this->converter_manager_ = new AssetConverterManager(this->setting_);
  this->context_ = new AssetConverterContext(this->unique_id_table_, this->converter_manager_);
}

void Director::Uninit()
{
  CerealIO::Json::Export(FileUtil::GetMidDataUniqueIdTablePath().c_str(), this->unique_id_table_);
  CerealIO::Json::Export(FileUtil::GetSettingPath().c_str(), this->setting_);

  delete this->context_;
  delete this->converter_manager_;
  delete this->setting_;
  delete this->unique_id_table_;
}

void Director::Import()
{
  //Importerが対応しているファイルのAssetInfoを作成
  //UniqueIdテーブルなどの作成
  //ImporterへのAssetInfoのセット
  FileUtil::CrawlInputDirectory([&](const URI& uri)
  {
    //AssetInfoが生成されれば予約成功
    if (this->context_->Reserve(uri))
    {
      return;
    }
    //予約が失敗し、拡張子がメタデータ以外の場合はスキップした事をログに表示
    if (uri.GetExtension() != Extensions::META)
    {
      std::cout << "skip \"" << uri.GetFullPath() << "\" " << std::endl;
    }
  });

  //Converterのインポート予約が無くなるまでConverterのインポート処理
  while (
    //イテレーターのロードを１つずつ行う
    //１つずつ行う理由はインポート予約のループ中にサブアセットの生成による
    //インポート予約の挿入の危険性を回避する為
    this->converter_manager_->Fire([&](IAssetConverter* converter)
    {
      return converter->ImportOnce(this->context_);
    })
  );
}

void Director::Export()
{
  this->converter_manager_->VisitAll([&](IAssetConverter* converter)
  {
    converter->Export(this->context_);
  });

  CerealIO::Binary::Export(FileUtil::GetArchiveUniqueIdTablePath().c_str(), this->unique_id_table_);
}

void Director::CreateProgram()
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
