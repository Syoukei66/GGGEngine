#pragma once

#include <set>

#include "AssetMetaData.h"
#include "AssetInfo.h"

#include "RuntimeSetting.h"

#include "AssetProgramGenerator_namespace.h"

class BaseConverter
{
public:
  BaseConverter();
  virtual ~BaseConverter();

public:
  void Convert() const;
  std::string CreateHeaderProgram() const;
  std::string CreateCppProgram() const;

  virtual void GetIncludePaths(std::set<std::string>* dest) const = 0;

public:
  void AddTargetAsset(AssetInfo* info);
  void RemoveTargetAsset(AssetInfo* info);
  void ClearTargetAsset();

  virtual bool IsTarget(const std::string& extension) const = 0;

  inline void Visit(std::function<void(AssetInfo* info)> func)
  {
    for (AssetInfo* info : this->target_infomations_)
    {
      func(info);
    }
  }
  inline void Visit(std::function<void(const AssetInfo* info)> func) const
  {
    for (const AssetInfo* info : this->target_infomations_)
    {
      func(info);
    }
  }

protected:
  virtual void ConvertProcess(AssetInfo* info) const = 0;

  template <typename Data_, typename Test_>
  void ExportProcess(AssetInfo* info, Data_* data, std::function<Data_*(const std::string&)> importer, std::function<void(const std::string&, Data_*)> exporter) const
  {
    if (!data)
    {
      std::cout << info->full_path << " is not found or can't convert" << std::endl;
      return;
    }
    exporter(info->output_path, data);
    this->ExportTest<Data_, Test_>(info, data, importer);
  }

  template <typename Data_, typename Test_>
  void ExportTest(AssetInfo* info, Data_* data, std::function<Data_*(const std::string&)> importer) const
  {
    if (!RuntimeSetting::CheckDebugFlag(RuntimeSetting::CONVERTER_TEST))
    {
      return;
    }
    Test_ test;
    Data_* converted_data = importer(info->output_path);
    test.Compare(data, converted_data);
    delete converted_data;
    if (test.HasMessage())
    {
      test.PrintMessages();
    }
  }

public:
  inline AssetProgram::NamespaceGenerator& GetNamespaceGenerator()
  {
    return this->program_generator_;
  }
  inline const AssetProgram::NamespaceGenerator& GetNamespaceGenerator() const
  {
    return this->program_generator_;
  }

private:
  AssetProgram::NamespaceGenerator program_generator_;
  std::vector<AssetInfo*> target_infomations_;

};
