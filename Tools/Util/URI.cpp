#include "URI.h"
#include <regex>

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
