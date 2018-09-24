#include <stdio.h>
#include <iostream>
#include <chrono>
#include <crtdbg.h> 
#include <cstddef>

#include <assimp\Importer.hpp>
#include <assimp\postprocess.h>
#include <assimp\scene.h>

#include "../Asset/CerealStaticModelIO.h"
#include "../Core/CerealIO.h"

#include "AssetConverterManager.h"
#include "AssetProgramGenerator.h"
#include "Director.h"

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

int main()
{
  _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

  Director* director = &Director::GetInstance();

  director->Init();

  //StaticModelConverter static_model_converter = StaticModelConverter();
  //NotConverter texture_converter = NotConverter({ "jpg", "png" }, "rcTexture", "rcTexture");
  //NotConverter sound_converter = NotConverter({ "wav", "mp3" }, "rcSound", "rcSound");
  //NotConverter shader_converter = NotConverter({ "cso" }, "rcShader", "rcShader");
  //NotConverter csv_converter = NotConverter({ "csv" }, "CSV", "rcCsvData");
  //NotConverter json_converter = NotConverter({ "json" }, "JSON", "rcJsonData");

  //RuntimeSetting::SetDebugFlag(RuntimeSetting::CONVERTER_TEST);

  //asset_manager->AddConverter(&static_model_converter);
  //asset_manager->AddConverter(&texture_converter);
  //asset_manager->AddConverter(&sound_converter);
  //asset_manager->AddConverter(&shader_converter);
  //asset_manager->AddConverter(&csv_converter);
  //asset_manager->AddConverter(&json_converter);

  director->Import();
  
  director->Export();
  director->CreateProgram();

  std::cout << "\n終了するには何かキーを押してください。" << std::endl;
  getchar();

  return 0;
}

#include "../Core/NativeProcess.h"

void NativeProcess::Graphics::PackColor4u8(T_PACKED_COLOR_UINT32* color, T_UINT8 r, T_UINT8 g, T_UINT8 b, T_UINT8 a)
{
}