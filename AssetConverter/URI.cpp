#include "URI.h"
#include "FileUtil.h"
#include <regex>
#include <fstream>

// =================================================================
// Constructor / Destructor
// =================================================================
URI::URI(const std::string& full_path)
  : full_path_(full_path)
{
}

static std::string CreateFullPath(const std::string& directory_path, const std::string& file_name)
{
  //TODO:Crawlで作成されるfull_pathと同等になるようにfull_pathの作成をする
  //     (file_nameがディレクトリを上に移動する指定でも対応できるように)
  return directory_path + "/" + file_name;
}

URI::URI(const std::string& directory_path, const std::string& file_name)
  : URI(CreateFullPath(directory_path, file_name))
{
  this->directory_path_ = directory_path;
  this->file_name_ = file_name;
}

URI::URI(const std::string& directory_path, const std::string& prefix, const std::string& extension)
  : URI(directory_path, prefix + "." + extension)
{
  this->prefix_ = prefix;
  this->extension_ = extension;
}

// =================================================================
// Setter / Getter
// =================================================================
const std::string& URI::GetProgramID() const
{
  if (this->program_id_.length() == 0)
  {
    //ファイル名がキャメル方式だった場合スネーク方式に変更
    std::string snake_filename = this->full_path_;
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
    const_cast<URI*>(this)->program_id_ = std::regex_replace(upper_filename, std::regex("[^a-zA-Z0-9]+"), "_");
  }
  return this->program_id_;
}

static void GetDirectoryPathAndFileName(const std::string& full_path, std::string* directory, std::string* file_name)
{
  //TODO:書く
}

const std::string& URI::GetDirectoryPath() const
{
  if (this->directory_path_.length() == 0)
  {
    GetDirectoryPathAndFileName(this->full_path_, &const_cast<URI*>(this)->directory_path_, &const_cast<URI*>(this)->file_name_);
  }
  return this->directory_path_;
}

const std::string& URI::GetFileName() const
{
  if (this->file_name_.length() == 0)
  {
    GetDirectoryPathAndFileName(this->full_path_, &const_cast<URI*>(this)->directory_path_, &const_cast<URI*>(this)->file_name_);
  }
  return this->file_name_;
}

static void GetPrefixSuffix(const std::string& file_name, std::string* prefix, std::string* suffix)
{
  std::regex re("(.*[^\\.]+)\\.([^\\.]+$)");
  std::smatch result;
  if (!std::regex_match(file_name, result, re))
  {
    return;
  }
  (*prefix) = result[1];
  (*suffix) = result[2];
}

const std::string& URI::GetPrefix() const
{
  if (this->prefix_.length() == 0)
  {
    GetPrefixSuffix(this->GetFileName(), &const_cast<URI*>(this)->prefix_, &const_cast<URI*>(this)->extension_);
  }
  return this->prefix_;
}

const std::string& URI::GetExtension() const
{
  if (this->extension_.length() == 0)
  {
    GetPrefixSuffix(this->GetFileName(), &const_cast<URI*>(this)->prefix_, &const_cast<URI*>(this)->extension_);
  }
  return this->extension_;
}
