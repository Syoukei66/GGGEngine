#include "AssetInfo.h"
#include <regex>
#include <fstream>
#include "FileUtil.h"
#include "AssetConverter.h"
#include "AssetConverterContext.h"

// =================================================================
// Factory Method
// =================================================================
AssetInfo* AssetInfo::Create(const std::string& directory_path, const std::string& file_name, const std::string& extension, AssetConverterContext* context)
{
  const Setting* setting = context->GetSetting();

  AssetInfo* info = new AssetInfo();
  info->full_path_ = directory_path + file_name;
  info->directory_path_ = directory_path;
  info->file_name_ = file_name;
  info->extension_ = extension;

  const T_UINT32 input_path_length = setting->input_path.length();
  info->local_full_path_ = info->full_path_.substr(input_path_length + 1, info->full_path_.length() - input_path_length - 1);

  //ファイル名がキャメル方式だった場合スネーク方式に変更
  std::string snake_filename = info->local_full_path_;
  snake_filename = std::regex_replace(snake_filename, std::regex("([a-z])([A-Z])"), "$1_$2");

  //ファイル名を大文字に変換
  std::string upper_filename = snake_filename;
  std::transform(upper_filename.begin(), upper_filename.end(), upper_filename.begin(), ::toupper);

  //ファイル名から拡張子を取り除く
  std::string::size_type pos;
  pos = upper_filename.find_last_of(".");
  upper_filename = upper_filename.substr(0, pos);

  //プログラム生成時の名前(ID)の作成
  //プログラムで使用できない文字を変換
  info->program_id_ = std::regex_replace(upper_filename, std::regex("[^a-zA-Z0-9]+"), "_");

  info->meta_data_ = AssetMetaData::Create(info->full_path_, context);

  return info;
}

