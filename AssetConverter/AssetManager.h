#pragma once

#include <unordered_map>
#include <vector>
#include <functional>
#include <iostream>

#include "../Core/HashUtil.h"
#include "BaseConverter.h"
#include "AssetInfo.h"
#include "Setting.h"

class OldAssetManager
{
public:
  static OldAssetManager& GetInstance()
  {
    static OldAssetManager self;
    return self;
  }

private:
  OldAssetManager() = default;
  ~OldAssetManager();

public:
  OldAssetManager(const OldAssetManager&) = delete;
  OldAssetManager& operator=(const OldAssetManager&) = delete;
  OldAssetManager(OldAssetManager&&) = delete;
  OldAssetManager& operator=(OldAssetManager&&) = delete;

public:
  void Init(Setting* setting);
  void AddConverter(BaseConverter* converter);

  void ScanAssetFolder();
  void SaveMetadatas();
  void ClearCaches();

  void Convert();

  void CreateProgram(std::string* header, std::string* cpp);

  void VisitAssetInfo(const std::function<void(AssetInfo*)>& func);
  void VisitAssetInfo(const std::function<void(const AssetInfo*)>& func) const;
  void VisitConverter(const std::function<void(BaseConverter*)>& func);
  void VisitConverter(const std::function<void(const BaseConverter*)>& func) const;

private:
  void Crawl(const std::string& directory_path, std::function<void(const std::string& directory_path, const std::string& file_name)> process);
  
public:
  inline const Setting* GetSetting() const
  {
    return this->setting_;
  }

  inline const AssetInfo* GetInfomation(std::string path) const
  {
    const T_UINT32 hash = Util::Hash::GetHash(path);
    if (this->informations_.find(hash) == this->informations_.end())
    {
      std::cout << "referenced file \"" << path << "\" is not found" << std::endl;
      getchar();
      return nullptr;
    }
    return this->informations_.at(hash);
  }

private:
  Setting* setting_;
  std::unordered_map<T_UINT32, AssetInfo*> informations_;
  std::vector<BaseConverter*> converters_;

};