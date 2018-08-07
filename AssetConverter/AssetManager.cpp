#include "AssetManager.h"

#include "../Asset/CerealIO.h"

#define NOMINMAX
#include <Windows.h>
#include <regex>
#include <direct.h>
#include <set>

static const char* META_DATA_EXTENSION = "meta";

static AssetMetaData* LoadMetaData(const std::string& path)
{
  if (!std::ifstream(path).is_open())
  {
    return new AssetMetaData();
  }
  AssetMetaData* ret = CerealIO::Json::SafeImport<AssetMetaData>(path.c_str());
  if (!ret)
  {
    ret = new AssetMetaData();
  }
  return ret;
}

AssetManager::~AssetManager()
{
  for (BaseConverter* converter : this->converters_)
  {
    delete converter;
  }
  for (auto& pair : this->informations_)
  {
    delete pair.second->meta_data;
    delete pair.second;
  }
}

void AssetManager::Init(Setting* setting)
{
  this->setting_ = setting;
}

void AssetManager::AddConverter(BaseConverter* converter)
{
  this->converters_.push_back(converter);
}

void AssetManager::ScanAssetFolder()
{
  this->informations_.clear();

  //AssetInfoの作成
  this->Crawl(this->setting_->input_path + "/", [&](const std::string& directory_path, const std::string& file_name)
  {
    std::regex re("(.*[^\\.]+)\\.([^\\.]+$)");
    std::smatch result;
    if (!std::regex_match(file_name, result, re))
    {
      return;
    }
    std::string extension = result[2];

    bool is_target = false;
    for (BaseConverter* converter : this->converters_)
    {
      is_target |= converter->IsTarget(extension);
    }

    if (!is_target)
    {
      return;
    }

    AssetInfo* info = new AssetInfo();
    info->full_path = directory_path + file_name;
    info->directory_path = directory_path;
    info->file_name = file_name;
    info->extension = extension;
    const T_UINT32 unique_id = Util::Hash::GetHash(info->full_path);
    info->output_path = this->setting_->output_path + "/" + std::to_string(unique_id) + "." + info->extension;

    const T_UINT32 input_path_length = this->setting_->input_path.length();
    std::string local_fullpath = info->full_path.substr(input_path_length + 1, info->full_path.length() - input_path_length - 1);

    //ファイル名がキャメル方式だった場合スネーク方式に変更
    std::string snake_filename = local_fullpath;
    snake_filename = std::regex_replace(snake_filename, std::regex("([a-z])([A-Z])"), "$1_$2");

    //ファイル名を大文字に変換
    std::string upper_filename = snake_filename;
    std::transform(upper_filename.begin(), upper_filename.end(), upper_filename.begin(), ::toupper);

    //ファイル名から拡張子を取り除く
    std::string::size_type pos;
    pos = upper_filename.find_last_of(".");
    upper_filename = upper_filename.substr(0, pos);

    //プログラム生成時の名前(ID)の作成
    //(.*[^\\.] + )\\.([^\\.] + $)
    info->program_id = std::regex_replace(upper_filename, std::regex("[\\\\,/]"), "_");

    info->meta_data = LoadMetaData(info->full_path + "." + META_DATA_EXTENSION);
    if (info->meta_data->unique_id != unique_id)
    {
      std::cout << "unique id update \"" << info->full_path << "\" " << info->meta_data->unique_id << " ⇒ " << unique_id << std::endl;
      info->meta_data->unique_id = unique_id;
    }
    if (this->informations_.find(unique_id) != this->informations_.end())
    {
      std::cout << "unique id conflicted!!!!!!!!!!" << std::endl;
      getchar();
      return;
    }
    for (const std::string& reference : info->meta_data->references)
    {
      if (std::ifstream(reference).is_open())
      {
        break;
      }
      std::cout << "reference file not found!!!!!!!!!!!!!!" << std::endl;
      getchar();
    }
    this->informations_.emplace(unique_id, info);
    for (BaseConverter* converter : this->converters_)
    {
      converter->AddTargetAsset(info);
    }

  });

  _mkdir(this->setting_->output_path.c_str());

  std::vector<std::string> delete_map = std::vector<std::string>();
  //出力先ディレクトリから必要無いデータの削除
  this->Crawl(this->setting_->output_path + "/", [&](const std::string& directory_path, const std::string& file_name)
  {
    if (this->informations_.find(std::stoll(file_name)) != this->informations_.end())
    {
      return;
    }
    delete_map.push_back(file_name);
  });
  if (delete_map.size() == 0)
  {
    return;
  }
  std::cout << "unused file found" << std::endl;
  for (std::string& str : delete_map)
  {
    std::cout << str << std::endl;
  }
}

static void SaveMetaData(const std::string& path, AssetMetaData* meta_data)
{
  CerealIO::Json::Export(path.c_str(), meta_data);
}

void AssetManager::Crawl(const std::string& directory_path, std::function<void(const std::string& directory_path, const std::string& file_name)> process)
{
  HANDLE handle;
  WIN32_FIND_DATA data;

  std::string find_file = directory_path + "*";
  handle = FindFirstFile(find_file.c_str(), &data);
  if (handle == INVALID_HANDLE_VALUE)
  {
    std::cout << "error Asset File not found" << std::endl;
    getchar();
    return;
  }

  //directory_pathで指定されたディレクトリ内のすべてのファイル/ディレクトリに対し処理を行う
  do
  {
    //親ディレクトリを無視
    if (
      (data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) &&
      (strcmp(data.cFileName, "..") == 0 || strcmp(data.cFileName, ".") == 0)
      )
    {
      continue;
    }

    std::string file_name = data.cFileName;

    //ディレクトリだった場合はそのディレクトリに対しても処理を行う
    if (data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
    {
      Crawl(directory_path + file_name + "/", process);
      continue;
    }

    process(directory_path, file_name);
  } while (FindNextFile(handle, &data));

  FindClose(handle);
}

void AssetManager::SaveMetadatas()
{
  for (auto& pair : this->informations_)
  {
    SaveMetaData(pair.second->full_path + "." + META_DATA_EXTENSION, pair.second->meta_data);
  }
}

void AssetManager::ClearCaches()
{
  for (auto& pair : this->informations_)
  {
    pair.second->meta_data->time_stamp = "";
  }
}

void AssetManager::Convert()
{
  for (BaseConverter* converter : this->converters_)
  {
    converter->Convert();
  }
}

void AssetManager::CreateProgram(std::string* header, std::string* cpp)
{

}

void AssetManager::VisitAssetInfo(const std::function<void(AssetInfo*)>& func)
{
  for (auto& pair : this->informations_)
  {
    func(pair.second);
  }
}

void AssetManager::VisitAssetInfo(const std::function<void(const AssetInfo*)>& func) const
{
  for (const auto& pair : this->informations_)
  {
    func(pair.second);
  }
}

void AssetManager::VisitConverter(const std::function<void(BaseConverter*)>& func)
{
  for (BaseConverter* converter : this->converters_)
  {
    func(converter);
  }
}

void AssetManager::VisitConverter(const std::function<void(const BaseConverter*)>& func) const
{
  for (const BaseConverter* converter : this->converters_)
  {
    func(converter);
  }
}

