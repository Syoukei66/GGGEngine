#include "Director.h"

#include <regex>
#include <direct.h>
#include "../Core/CerealIO.h"
#include "../Core/Asset.h"
#include "FileUtil.h"

// =================================================================
// Methods
// =================================================================
void Director::Init()
{
  NATIVE_ASSERT(!this->setting_ && !this->converter_manager_ && !this->context_, "Initが２回連続で呼び出されました");
 
  this->setting_ = CerealIO::Json::SafeImport<Setting>("ConvertConfig.json");
  if (!this->setting_)
  {
    this->setting_ = Setting::Create();
  }

  this->converter_manager_ = new AssetConverterManager(this->setting_);
  this->context_ = new AssetConverterContext(this->setting_, this->converter_manager_);
}

void Director::Uninit()
{
  delete this->context_;
  delete this->converter_manager_;
  delete this->setting_;
}

void Director::Import()
{
  //Importerが対応しているファイルのAssetInfoを作成
  //UniqueIdテーブルなどの作成
  //ImporterへのAssetInfoのセット
  Util::File::Crawl(this->setting_->input_path + "/", [&](const std::string& directory_path, const std::string& file_name)
  {
    //対応する拡張子のRawデータを検索
    std::regex re("(.*[^\\.]+)\\.([^\\.]+$)");
    std::smatch result;
    if (!std::regex_match(file_name, result, re))
    {
      return;
    }
    std::string extension = result[2];

    //拡張子に対応したconverterの取得
    this->context_->Reserve(directory_path, file_name, extension);
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
  //出力先ディレクトリの作成
  _mkdir(this->setting_->output_path.c_str());

  this->converter_manager_->VisitAll([&](IAssetConverter* converter)
  {
    converter->Export(this->context_);
  });
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

  const std::string header_path = this->setting_->project_path + "/" + "Asset.h";
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

  const std::string cpp_path = this->setting_->project_path + "/" + "Asset.cpp";
  std::ofstream output_cpp(cpp_path);
  if (output_cpp)
  {
    output_cpp << cpp;
    output_cpp.close();
  }
}
