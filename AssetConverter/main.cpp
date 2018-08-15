#include <stdio.h>
#include <iostream>
#include <chrono>
#include <crtdbg.h> 
#include <cstddef>

#include <assimp\Importer.hpp>
#include <assimp\postprocess.h>
#include <assimp\scene.h>

#include "../Asset/CerealStaticModelIO.h"
#include "../Asset/CerealIO.h"

#include "AssimpStaticModelImporter.h"
#include "AssetManager.h"

#include "StaticModelConverter.h"
#include "NotConverter.h"

#include "AssetProgramGenerator.h"

static const char* MODEL_PATH = "test.model";

void Test()
{
  //using namespace std;
  //using namespace chrono;

  //system_clock::time_point p0 = system_clock::now();

  //const aiScene* scene = Assimp::Importer().ReadFile(
  //  "xada-hgla2.blend",
  //  aiProcess_CalcTangentSpace |
  //  aiProcess_Triangulate |
  //  aiProcess_JoinIdenticalVertices |
  //  aiProcess_SortByPType |
  //  aiProcess_MakeLeftHanded |
  //  aiProcess_LimitBoneWeights |
  //  aiProcess_ImproveCacheLocality |
  //  aiProcess_SplitByBoneCount |
  //  aiProcess_PreTransformVertices
  //);

  ////FBX Import
  //StaticModelData* data = ModelImporter::Assimp::ImportStaticModel(scene);

  ////時間計測
  //system_clock::time_point p1 = system_clock::now();
  //cout << "FBX Import Time " << duration_cast<chrono::milliseconds>(p1 - p0).count() << "(ms)" << endl;

  ////Cereal Export
  //CerealIO::Binary::Export(MODEL_PATH, data);

  ////時間計測
  //system_clock::time_point p2 = system_clock::now();
  //cout << "Cereal Export Time " << duration_cast<chrono::milliseconds>(p2 - p1).count() << "(ms)" << endl;

  ////Cereal Import
  //StaticModelData* load_data = CerealIO::Binary::Import<StaticModelData>(MODEL_PATH);

  ////時間計測
  //system_clock::time_point p3 = system_clock::now();
  //cout << "Cereal Import Time " << duration_cast<chrono::milliseconds>(p3 - p2).count() << "(ms)" << endl;

  //cout << "\n終了するには何かキーを押してください。" << endl;
  //getchar();

  //delete data;
  //delete load_data;
}

static const char* SETTING_PATH = "./ConvertConfig.json";

int main()
{
  _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

  Setting* setting = CerealIO::Json::SafeImport<Setting>(SETTING_PATH);

  if (!setting)
  {
    setting = Setting::Create();
  }

  AssetManager* asset_manager = &AssetManager::GetInstance();

  asset_manager->Init(setting);
  
  StaticModelConverter static_model_converter = StaticModelConverter();
  NotConverter texture_converter = NotConverter({ "jpg", "png" }, "Texture", "Texture");
  NotConverter sound_converter = NotConverter({ "wav", "mp3" }, "Sound", "INativeSound");
  NotConverter shader_converter = NotConverter({ "cso" }, "Shader", "INativeShader");
  NotConverter csv_converter = NotConverter({ "csv" }, "CSV", "CsvData");
  NotConverter json_converter = NotConverter({ "json" }, "JSON", "JsonData");

  RuntimeSetting::SetDebugFlag(RuntimeSetting::CONVERTER_TEST);

  asset_manager->AddConverter(&static_model_converter);
  asset_manager->AddConverter(&texture_converter);
  asset_manager->AddConverter(&sound_converter);
  asset_manager->AddConverter(&shader_converter);
  asset_manager->AddConverter(&csv_converter);
  asset_manager->AddConverter(&json_converter);

  asset_manager->ScanAssetFolder();

  //asset_manager->ClearCaches();

  asset_manager->Convert();

  asset_manager->SaveMetadatas();

  CerealIO::Json::Export(SETTING_PATH, setting);

  AssetProgram::Generator generator;

  std::string header;
  std::string cpp;

  generator.Generate(*asset_manager, &header, &cpp);

  std::cout << "//======================================" << std::endl;
  std::cout << "//Asset.h" << std::endl;
  std::cout << "//======================================" << std::endl;
  std::cout << header << std::endl;

  std::cout << "//======================================" << std::endl;
  std::cout << "//Asset.cpp" << std::endl;
  std::cout << "//======================================" << std::endl;
  std::cout << cpp << std::endl;

  //write headder program
  const std::string header_path = setting->project_path + "/" + "Asset.h";
  std::ofstream output_header(header_path);
  if (output_header)
  {
    output_header << header;
    output_header.close();
  }

  //write headder program
  const std::string cpp_path = setting->project_path + "/" + "Asset.cpp";
  std::ofstream output_cpp(cpp_path);
  if (output_cpp)
  {
    output_cpp << cpp;
    output_cpp.close();
  }

  delete setting;

  std::cout << "\n終了するには何かキーを押してください。" << std::endl;
  getchar();

  return 0;
}

#include "../Core/NativeProcess.h"

void NativeProcess::Graphics::PackColor4u8(T_PACKED_COLOR_UINT32* color, T_UINT8 r, T_UINT8 g, T_UINT8 b, T_UINT8 a)
{
}