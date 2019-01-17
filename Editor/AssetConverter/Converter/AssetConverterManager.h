#pragma once

#include "AssetConverter.h"

class AssetEntity;

class AssetConverterManager
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  AssetConverterManager();
  ~AssetConverterManager();

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  inline void AddConverter(AssetConverter* converter)
  {
    this->converter_map_[converter->GetId()] =  converter;
  }

  inline AssetConverter* GetConverter(const std::string& id)
  {
    return this->converter_map_[id];
  }

  inline const AssetConverter* GetConverter(const std::string& id) const
  {
    return this->converter_map_.at(id);
  }

  // =================================================================
  // Data Members
  // =================================================================
private:
  std::unordered_map<std::string, AssetConverter*> converter_map_;

};
