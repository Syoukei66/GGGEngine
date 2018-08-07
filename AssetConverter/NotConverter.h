#pragma once

#include <vector>
#include <string>
#include "BaseConverter.h"

class NotConverter : public BaseConverter
{
public:
  NotConverter(const std::initializer_list<std::string>& extensions, const std::string& asset_name, const std::string& class_name);

public:
  void GetIncludePaths(std::set<std::string>* dest) const override;
  bool IsTarget(const std::string& extension) const override;

protected:
  void ConvertProcess(AssetInfo* info) const override;

private:
  std::vector<std::string> extensions_;
  std::string asset_name_;
  std::string class_name_;
};